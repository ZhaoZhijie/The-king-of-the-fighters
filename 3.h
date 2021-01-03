#ifndef _3_H_
#define _3_H_
#include "Scene.h"
#include <list>
#include "GameEngine.h"
#include "TeXiao.h"
class C3 : public CScene
{
friend class TeXiao;
private:
	CPlayer *m_Player[2];
	std::list<TeXiao*> m_TX;
	char dbug[100];
	unsigned int m_BackNo;
	//视口左上角坐标
	float virX;
	float virY;
	int cf;
	bool Fast;
public:
	void Init();
	void OutputRun();		//绘制
	void LogicInputRun();	//输入和逻辑
	void Enter();			//入效果
	void Quit();			//出效果
};


#endif