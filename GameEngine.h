#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <windows.h>
#include <string>
#include <map>
#include "GameInput.h"
#include "GameOutput.h"
#include "SceneChange.h"
#include "MakeMove.h"
#include "Skill.h"
#include "Role.h"
#include "TeXiao.h"
#include "AudioManager.h"
#define _G 0.7
#define _F 0.5
class CScene;
class CSkill;
class CRole;
class CTeXiao;

class CGameEngine
{
	int m_RunState;				//运行状态

	//窗口相关数据
	WNDCLASSA m_WndClass;		//窗口
	char m_WndClassName[32];	//窗口名
	HWND m_hWnd;				//窗口句柄
	int m_ClientW, m_ClientH;	//客户区宽高
	BOOL m_Act;					//窗口激活标志
	int m_SleepTime;			//休息时间
	int m_StrandTime;			//初始休息时间

	//场景切换相关
	CSceneChange* m_EnterChange;
	CSceneChange* m_QuitChange;
	//场景切换管理
	std::map<std::string, CSceneChange*> m_SceneChange;

	//动作管理
	CMoves m_Moves;
	//角色管理
	std::map<std::string, CRole *> m_Role;
	//技能管理
	std::map<std::string, CSkill *> m_Skill;
	//特效管理
	std::map<std::string, CTeXiao *> m_TX;

	//工具相关
	CGameOutput* m_GO;
	CGameInput* m_GI;
	CAudioManager m_AM;		//音频工具

	//场景相关
	std::map<std::string, CScene*> m_Scene;	//场景
	CScene* m_CurScene;						//当前运行的场景
	CScene* m_NextScene;					//下一个场景

	//消息处理函数
	static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	CGameEngine();
	~CGameEngine();

	//游戏引擎
	static CGameEngine* m_pGameEngine;
public:
	//得到游戏引擎
	static CGameEngine* GetGE();
	
	//初始化
	bool Init(int ClientW, int ClientH);

	//运行  游戏循环
	void Run();

	//改变游戏帧率
	void SetSleepTime(float r);

	//恢复游戏帧率
	void ResetSleepTime();

	//加载技能
	bool LoadSkill(const char* id, CSkill* pSkill);
	//获取技能
	CSkill* GetSkill(const char* id);
	//加载角色
	bool LoadRole(const char* id, CRole* pRole);
	//获取角色
	CRole* GetRole(const char* id);
	//加载场景
	bool LoadScene(const char* id, CScene* pScene);
	//加载场景切换效果
	bool LoadSceneChange(const char* id, CSceneChange* p);
	//剔除场景
	bool ReleaseScene(const char* id);
	//设置最初场景
	bool SetInitScene(const char* id);
	//设置当前场景
	bool SetCurScene(const char* id);
	//获取场景
	CScene* GetScene(const char* id);

	//设置进入效果
	bool SetEnterChange(const char* id);
	//设置退出效果
	bool SetQuitChange(const char* id);
	
	//获取绘制工具
	CGameOutput* GetGO();
	//获取输入工具
	CGameInput* GetGI();
	//获取音频工具
	CAudioManager* GetAM();

	//退出游戏
	void ExitGame();

	//获取客户区宽
	int GetClientW();
	//获取客户区高
	int GetClientH();
	HWND GetWnd();
	//获取动作管理
	CMoves* GetMoves();
};

#endif