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
	//�ӿ����Ͻ�����
	float virX;
	float virY;
	int cf;
	bool Fast;
public:
	void Init();
	void OutputRun();		//����
	void LogicInputRun();	//������߼�
	void Enter();			//��Ч��
	void Quit();			//��Ч��
};


#endif