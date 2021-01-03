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
	virtual void Enter();	//进入场景
	virtual void OutputRun();		//绘制
	virtual void LogicInputRun();	//输入和逻辑
	virtual void Quit();	//场景退出
	virtual void End();		//结束
	
	void SetQuitChange(std::string QuitChange);
	void SetEnterChange(std::string EnterChange);
};

#endif