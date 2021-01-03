#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>

class CScene
{
	friend class CGameEngine;
	std::string m_QuitChange;
	std::string m_EnterChange;
public:
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();	//���볡��
	virtual void OutputRun();		//����
	virtual void LogicInputRun();	//������߼�
	virtual void Quit();	//�����˳�
	virtual void End();		//����
	
	void SetQuitChange(std::string QuitChange);
	void SetEnterChange(std::string EnterChange);
};

#endif