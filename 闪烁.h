#ifndef  _��˸_H
#define _��˸_H
#include "TeXiao.h"
#include "Player.h"
#define _SS_LAST 1
#define _SS_ONCE 2
class CPlayer;
class CTX_SS:public CTeXiao
{
private:
	int m_Len;
	int m_CurF;
	CPlayer * m_Player;
	int m_pM;
	int m_CF;//��˸����
	bool m_Add;
	int m_Type;
	float m_Gray;
public:
	CTX_SS(int len,CPlayer* player,int type=_SS_ONCE,float gray=0.3);
	//��Ч������Ϻ󷵻�false����֪����ɾ������Ч
	bool Run(float vir_x,float *py);
};

#endif