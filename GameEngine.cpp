#include "GameEngine.h"
#include <iostream>
#include <time.h>
#include "Scene.h"

#define _SC_NONE 0		//没有切换
#define _SC_QUIT 1		//执行退出效果
#define _SC_CHANGE 2	//准备场景切换
#define _SC_ENTER 3		//执行进入效果

CGameEngine* CGameEngine::m_pGameEngine = 0;

//消息处理函数
LRESULT CALLBACK CGameEngine::_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_ACTIVATEAPP:
		{
			GetGE()->m_Act = (BOOL)wParam;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

CGameEngine::CGameEngine()
:
m_hWnd(0),
m_ClientW(0),
m_ClientH(0),
m_Act(TRUE),
m_SleepTime(16),
m_StrandTime(16),
m_GI(0),
m_GO(0),
m_CurScene(0),
m_NextScene(0),
m_RunState(_SC_NONE),
m_EnterChange(0),
m_QuitChange(0)
{
	srand((unsigned int)time(0));
}

CGameEngine::~CGameEngine()
{}

//得到游戏引擎
CGameEngine* CGameEngine::GetGE()
{
	if(0 == m_pGameEngine)
	{
		m_pGameEngine = new CGameEngine;
	}
	return m_pGameEngine;
}

//初始化
bool CGameEngine::Init(int ClientW, int ClientH)
{
	//参数合法检查
	if(ClientW < 1 || ClientH < 1)
		return false;

	//得到宽高
	m_ClientW = ClientW;
	m_ClientH = ClientH;

	//填充窗口类别的结构体
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = _WindowProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = "10班";

	//注册窗口
	RegisterClass(&m_WndClass);

	//得到窗口矩形
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	
	RECT r = 
	{
		(sw - m_ClientW) / 2, 
		(sh - m_ClientH) / 2,
		r.left + m_ClientW,
		r.top + m_ClientH
	};

	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);//| WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
	
	//创建窗口   WS_POPUP
	m_hWnd = CreateWindowA(
		m_WndClass.lpszClassName,
		0,
		 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
		 r.left,
		 r.top,
		 r.right - r.left,
		 r.bottom - r.top,
		 HWND_DESKTOP,
		 0,
		 m_WndClass.hInstance,
		 0);
	
	m_GI = new CGameInput(m_hWnd);
	m_GO = new CGameOutput(m_hWnd);
	return true;
}

//改变游戏帧率
void CGameEngine::SetSleepTime(float r)
{
	if(r>5)
		r=5;
	else if(r<0)
		r=0;
	m_SleepTime=(int)r*m_StrandTime;
}

//恢复游戏帧率
void CGameEngine::ResetSleepTime()
{
	m_SleepTime=m_StrandTime;
}

//场景相关函数
bool CGameEngine::LoadScene(const char* id, CScene* pScene)
{
	//ID重复 不允许加载
	std::string s = id;
	if(m_Scene.find(s) != m_Scene.end())
		return false;

	m_Scene.insert(std::pair<std::string, CScene*>(s, pScene));
	return true;
}



bool CGameEngine::ReleaseScene(const char* id)
{
	//通过key值 找到对应的数据
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//如果没找到 返回
	if(i == m_Scene.end())
		return false;

	i->second->End(); //使用多态 清空场景对应开辟的内存（如果有）
	delete i->second;
	m_Scene.erase(i);
	return true;
}
bool CGameEngine::SetInitScene(const char* id)
{
	//通过key值 找到对应的数据
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//如果没找到 返回
	if(i == m_Scene.end())
		return false;

	m_CurScene = i->second;
	return true;
}
bool CGameEngine::SetCurScene(const char* id)
{
	//通过key值 找到对应的数据
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//如果没找到 返回
	if(i == m_Scene.end())
		return false;

	m_NextScene = i->second;
	//得到当前场景的退出切换效果 下一个场景的进入切换效果
	std::map<std::string, CSceneChange*>::iterator j;
	j = m_SceneChange.find(m_CurScene->m_QuitChange);
	if(j == m_SceneChange.end())
		m_QuitChange = 0;
	else
	{
		m_QuitChange = j->second;
		m_QuitChange->SetBegin();
	}
	j = m_SceneChange.find(m_NextScene->m_EnterChange);
	if(j == m_SceneChange.end())
		m_EnterChange = 0;
	else
	{
		m_EnterChange = j->second;
		m_EnterChange->SetBegin();
	}

	//修改运行状态为 退出切换效果
	m_RunState = _SC_QUIT;

	return true;
}
CScene* CGameEngine::GetScene(const char* id)
{
	//通过key值 找到对应的数据
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//如果没找到 返回
	if(i == m_Scene.end())
		return 0;

	return i->second;
}

//运行  游戏循环
void CGameEngine::Run()
{
	std::map<std::string, CScene*>::iterator i;

	//场景初始化
	//for(i = m_Scene.begin(); i != m_Scene.end(); ++i)
	//	i->second->Init();//多态

	//最初场景进入
	if(m_CurScene)
	{
		m_CurScene->Init();
		m_CurScene->Enter();
	}

	m_RunState = _SC_ENTER;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(m_Act)
		{
			int tc = GetTickCount();
			
			//输出
			m_GO->Begin();

			//更新按键状态
			/*m_GI->Run();*/
			
			if(m_CurScene)
			{
				m_CurScene->OutputRun();
				//m_CurScene->Run();

				switch(m_RunState)
				{
				case _SC_QUIT:
					{
						if(m_QuitChange)
						{
							m_QuitChange->Render(m_QuitChange->m_CurFrame += 1);
							if(m_QuitChange->m_CurFrame >= m_QuitChange->m_AllFrame)
								m_RunState = _SC_CHANGE;
						}
						else
							m_RunState = _SC_CHANGE;
						break;
					}
				case _SC_ENTER:
					{
						if(m_EnterChange)
						{
							m_EnterChange->Render(m_EnterChange->m_CurFrame += 1);
							if(m_EnterChange->m_CurFrame >= m_EnterChange->m_AllFrame)
								m_RunState = _SC_NONE;
						}
						else
							m_RunState = _SC_NONE;
						break;
					}
				}
			}
			
			m_GO->End();
			//逻辑 和 输入

			//更新按键状态
			m_GI->Run();
			
			if(m_CurScene && m_RunState == _SC_NONE)
			{
				m_CurScene->LogicInputRun();
			}

			tc = GetTickCount() - tc;
			Sleep(m_SleepTime > tc ? m_SleepTime - tc : 1);
		}
		else
			WaitMessage();

		//根据运行状态来处理

		//切换场景（必须保证一次游戏循环完毕以后 才执行）
		if(m_RunState == _SC_CHANGE && m_NextScene)
		{
			m_CurScene->Quit();
			m_CurScene = m_NextScene;
			m_CurScene->Init();
			m_CurScene->Enter();
			m_NextScene = 0;
			m_RunState = _SC_ENTER;
		}

		/*if(m_NextScene)
		{
			m_CurScene->Quit();
			m_CurScene = m_NextScene;
			m_CurScene->Enter();
			m_NextScene = 0;
		}*/
	}

	//当前场景退出
	if(m_CurScene)
		m_CurScene->Quit();

	//结束所有场景
	for(i = m_Scene.begin(); i != m_Scene.end(); ++i)
	{
		i->second->End();
		delete i->second;
	}
	
	//删除所有场景切换效果
	std::map<std::string, CSceneChange*>::iterator j;
	for(j = m_SceneChange.begin(); j != m_SceneChange.end(); ++j)
		delete j->second;

	delete m_GO;
	delete m_GI;
	delete m_pGameEngine;
}

//获取绘制工具
CGameOutput* CGameEngine::GetGO()
{
	return m_GO;
}
	//获取输入工具
CGameInput* CGameEngine::GetGI()
{
	return m_GI;
}

//获取音频工具
CAudioManager* CGameEngine::GetAM()
{
	return &m_AM;
}

//退出游戏
void CGameEngine::ExitGame()
{
	PostQuitMessage(0);
}

//获取客户区宽
int CGameEngine::GetClientW()
{
	return m_ClientW;
}
//获取客户区高
int CGameEngine::GetClientH()
{
	return m_ClientH;
}
//加载技能
bool CGameEngine::LoadSkill(const char* id, CSkill* pSkill)
{
	std::string s = id;
	if(m_Skill.find(s) != m_Skill.end())
		return false;
	m_Skill.insert(std::pair<std::string, CSkill*>(s, pSkill));
	return true;
}
//获取技能
CSkill* CGameEngine::GetSkill(const char* id)
{
	std::string s=id;
	std::map<std::string, CSkill*>::iterator i=m_Skill.find(s);
	if(i==m_Skill.end())
		return NULL;
	return i->second;
}

//加载角色
bool CGameEngine::LoadRole(const char* id, CRole* pRole)
{
	std::string s = id;
	if(m_Role.find(s) != m_Role.end())
		return false;
	m_Role.insert(std::pair<std::string, CRole*>(s, pRole));
	return true;
}
//获取角色
CRole* CGameEngine::GetRole(const char* id)
{
	std::string s=id;
	std::map<std::string, CRole*>::iterator i=m_Role.find(s);
	if(i==m_Role.end())
		return NULL;
	return i->second;
}
//加载场景切换效果
bool CGameEngine::LoadSceneChange(const char* id, CSceneChange* p)
{
	//通过id（也就是key） 来查找映射里是否存在同样的id
	//如果有同样的 那么 加载失败（key 是唯一的）
	std::string s = id;
	if(m_SceneChange.find(s) != m_SceneChange.end())
		return false;

	m_SceneChange.insert(std::pair<std::string, CSceneChange*>(s, p));
	return true;
}

//设置进入效果
bool CGameEngine::SetEnterChange(const char* id)
{
	std::string s = id;
	std::map<std::string, CSceneChange*>::iterator i = m_SceneChange.find(s);
	if(i != m_SceneChange.end())
	{
		m_EnterChange = i->second;
		return true;
	}
	return false;
}
//设置退出效果
bool CGameEngine::SetQuitChange(const char* id)
{
	std::string s = id;
	std::map<std::string, CSceneChange*>::iterator i = m_SceneChange.find(s);
	if(i != m_SceneChange.end())
	{
		m_QuitChange = i->second;
		return true;
	}
	return false;
}

//获取动作管理
CMoves* CGameEngine::GetMoves()
{
	return &m_Moves;
}

//获取窗口句柄
HWND CGameEngine::GetWnd()
{
	return m_hWnd;
}


