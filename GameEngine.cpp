#include "GameEngine.h"
#include <iostream>
#include <time.h>
#include "Scene.h"

#define _SC_NONE 0		//û���л�
#define _SC_QUIT 1		//ִ���˳�Ч��
#define _SC_CHANGE 2	//׼�������л�
#define _SC_ENTER 3		//ִ�н���Ч��

CGameEngine* CGameEngine::m_pGameEngine = 0;

//��Ϣ������
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

//�õ���Ϸ����
CGameEngine* CGameEngine::GetGE()
{
	if(0 == m_pGameEngine)
	{
		m_pGameEngine = new CGameEngine;
	}
	return m_pGameEngine;
}

//��ʼ��
bool CGameEngine::Init(int ClientW, int ClientH)
{
	//�����Ϸ����
	if(ClientW < 1 || ClientH < 1)
		return false;

	//�õ����
	m_ClientW = ClientW;
	m_ClientH = ClientH;

	//��䴰�����Ľṹ��
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = _WindowProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = "10��";

	//ע�ᴰ��
	RegisterClass(&m_WndClass);

	//�õ����ھ���
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
	
	//��������   WS_POPUP
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

//�ı���Ϸ֡��
void CGameEngine::SetSleepTime(float r)
{
	if(r>5)
		r=5;
	else if(r<0)
		r=0;
	m_SleepTime=(int)r*m_StrandTime;
}

//�ָ���Ϸ֡��
void CGameEngine::ResetSleepTime()
{
	m_SleepTime=m_StrandTime;
}

//������غ���
bool CGameEngine::LoadScene(const char* id, CScene* pScene)
{
	//ID�ظ� ���������
	std::string s = id;
	if(m_Scene.find(s) != m_Scene.end())
		return false;

	m_Scene.insert(std::pair<std::string, CScene*>(s, pScene));
	return true;
}



bool CGameEngine::ReleaseScene(const char* id)
{
	//ͨ��keyֵ �ҵ���Ӧ������
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//���û�ҵ� ����
	if(i == m_Scene.end())
		return false;

	i->second->End(); //ʹ�ö�̬ ��ճ�����Ӧ���ٵ��ڴ棨����У�
	delete i->second;
	m_Scene.erase(i);
	return true;
}
bool CGameEngine::SetInitScene(const char* id)
{
	//ͨ��keyֵ �ҵ���Ӧ������
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//���û�ҵ� ����
	if(i == m_Scene.end())
		return false;

	m_CurScene = i->second;
	return true;
}
bool CGameEngine::SetCurScene(const char* id)
{
	//ͨ��keyֵ �ҵ���Ӧ������
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//���û�ҵ� ����
	if(i == m_Scene.end())
		return false;

	m_NextScene = i->second;
	//�õ���ǰ�������˳��л�Ч�� ��һ�������Ľ����л�Ч��
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

	//�޸�����״̬Ϊ �˳��л�Ч��
	m_RunState = _SC_QUIT;

	return true;
}
CScene* CGameEngine::GetScene(const char* id)
{
	//ͨ��keyֵ �ҵ���Ӧ������
	std::string s = id;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	//���û�ҵ� ����
	if(i == m_Scene.end())
		return 0;

	return i->second;
}

//����  ��Ϸѭ��
void CGameEngine::Run()
{
	std::map<std::string, CScene*>::iterator i;

	//������ʼ��
	//for(i = m_Scene.begin(); i != m_Scene.end(); ++i)
	//	i->second->Init();//��̬

	//�����������
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
			
			//���
			m_GO->Begin();

			//���°���״̬
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
			//�߼� �� ����

			//���°���״̬
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

		//��������״̬������

		//�л����������뱣֤һ����Ϸѭ������Ժ� ��ִ�У�
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

	//��ǰ�����˳�
	if(m_CurScene)
		m_CurScene->Quit();

	//�������г���
	for(i = m_Scene.begin(); i != m_Scene.end(); ++i)
	{
		i->second->End();
		delete i->second;
	}
	
	//ɾ�����г����л�Ч��
	std::map<std::string, CSceneChange*>::iterator j;
	for(j = m_SceneChange.begin(); j != m_SceneChange.end(); ++j)
		delete j->second;

	delete m_GO;
	delete m_GI;
	delete m_pGameEngine;
}

//��ȡ���ƹ���
CGameOutput* CGameEngine::GetGO()
{
	return m_GO;
}
	//��ȡ���빤��
CGameInput* CGameEngine::GetGI()
{
	return m_GI;
}

//��ȡ��Ƶ����
CAudioManager* CGameEngine::GetAM()
{
	return &m_AM;
}

//�˳���Ϸ
void CGameEngine::ExitGame()
{
	PostQuitMessage(0);
}

//��ȡ�ͻ�����
int CGameEngine::GetClientW()
{
	return m_ClientW;
}
//��ȡ�ͻ�����
int CGameEngine::GetClientH()
{
	return m_ClientH;
}
//���ؼ���
bool CGameEngine::LoadSkill(const char* id, CSkill* pSkill)
{
	std::string s = id;
	if(m_Skill.find(s) != m_Skill.end())
		return false;
	m_Skill.insert(std::pair<std::string, CSkill*>(s, pSkill));
	return true;
}
//��ȡ����
CSkill* CGameEngine::GetSkill(const char* id)
{
	std::string s=id;
	std::map<std::string, CSkill*>::iterator i=m_Skill.find(s);
	if(i==m_Skill.end())
		return NULL;
	return i->second;
}

//���ؽ�ɫ
bool CGameEngine::LoadRole(const char* id, CRole* pRole)
{
	std::string s = id;
	if(m_Role.find(s) != m_Role.end())
		return false;
	m_Role.insert(std::pair<std::string, CRole*>(s, pRole));
	return true;
}
//��ȡ��ɫ
CRole* CGameEngine::GetRole(const char* id)
{
	std::string s=id;
	std::map<std::string, CRole*>::iterator i=m_Role.find(s);
	if(i==m_Role.end())
		return NULL;
	return i->second;
}
//���س����л�Ч��
bool CGameEngine::LoadSceneChange(const char* id, CSceneChange* p)
{
	//ͨ��id��Ҳ����key�� ������ӳ�����Ƿ����ͬ����id
	//�����ͬ���� ��ô ����ʧ�ܣ�key ��Ψһ�ģ�
	std::string s = id;
	if(m_SceneChange.find(s) != m_SceneChange.end())
		return false;

	m_SceneChange.insert(std::pair<std::string, CSceneChange*>(s, p));
	return true;
}

//���ý���Ч��
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
//�����˳�Ч��
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

//��ȡ��������
CMoves* CGameEngine::GetMoves()
{
	return &m_Moves;
}

//��ȡ���ھ��
HWND CGameEngine::GetWnd()
{
	return m_hWnd;
}


