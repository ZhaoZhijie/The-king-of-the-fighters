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
	int m_RunState;				//����״̬

	//�����������
	WNDCLASSA m_WndClass;		//����
	char m_WndClassName[32];	//������
	HWND m_hWnd;				//���ھ��
	int m_ClientW, m_ClientH;	//�ͻ������
	BOOL m_Act;					//���ڼ����־
	int m_SleepTime;			//��Ϣʱ��
	int m_StrandTime;			//��ʼ��Ϣʱ��

	//�����л����
	CSceneChange* m_EnterChange;
	CSceneChange* m_QuitChange;
	//�����л�����
	std::map<std::string, CSceneChange*> m_SceneChange;

	//��������
	CMoves m_Moves;
	//��ɫ����
	std::map<std::string, CRole *> m_Role;
	//���ܹ���
	std::map<std::string, CSkill *> m_Skill;
	//��Ч����
	std::map<std::string, CTeXiao *> m_TX;

	//�������
	CGameOutput* m_GO;
	CGameInput* m_GI;
	CAudioManager m_AM;		//��Ƶ����

	//�������
	std::map<std::string, CScene*> m_Scene;	//����
	CScene* m_CurScene;						//��ǰ���еĳ���
	CScene* m_NextScene;					//��һ������

	//��Ϣ������
	static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	CGameEngine();
	~CGameEngine();

	//��Ϸ����
	static CGameEngine* m_pGameEngine;
public:
	//�õ���Ϸ����
	static CGameEngine* GetGE();
	
	//��ʼ��
	bool Init(int ClientW, int ClientH);

	//����  ��Ϸѭ��
	void Run();

	//�ı���Ϸ֡��
	void SetSleepTime(float r);

	//�ָ���Ϸ֡��
	void ResetSleepTime();

	//���ؼ���
	bool LoadSkill(const char* id, CSkill* pSkill);
	//��ȡ����
	CSkill* GetSkill(const char* id);
	//���ؽ�ɫ
	bool LoadRole(const char* id, CRole* pRole);
	//��ȡ��ɫ
	CRole* GetRole(const char* id);
	//���س���
	bool LoadScene(const char* id, CScene* pScene);
	//���س����л�Ч��
	bool LoadSceneChange(const char* id, CSceneChange* p);
	//�޳�����
	bool ReleaseScene(const char* id);
	//�����������
	bool SetInitScene(const char* id);
	//���õ�ǰ����
	bool SetCurScene(const char* id);
	//��ȡ����
	CScene* GetScene(const char* id);

	//���ý���Ч��
	bool SetEnterChange(const char* id);
	//�����˳�Ч��
	bool SetQuitChange(const char* id);
	
	//��ȡ���ƹ���
	CGameOutput* GetGO();
	//��ȡ���빤��
	CGameInput* GetGI();
	//��ȡ��Ƶ����
	CAudioManager* GetAM();

	//�˳���Ϸ
	void ExitGame();

	//��ȡ�ͻ�����
	int GetClientW();
	//��ȡ�ͻ�����
	int GetClientH();
	HWND GetWnd();
	//��ȡ��������
	CMoves* GetMoves();
};

#endif