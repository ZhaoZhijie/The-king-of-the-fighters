#ifndef  _ͼƬ֡_H
#define _ͼƬ֡_H
#include "TeXiao.h"
#include "Player.h"
#include "GameEngine.h"
class CPlayer;
class CTX_TPZ:public CTeXiao
{
private:
	int m_preM;
	int m_preF;
	int m_Move;
	int m_CurF;
	int m_CF;
	float m_x;
	float m_y;
	int m_mirror;
	float m_vx;
	float m_vy;
	float m_Alpha;
	CPlayer * m_Player;
	int type;
public:
	//type������0 ��ʾ��Ч��������� ֱ��type��ʾ�İ������� ����ֻ����һ��
	CTX_TPZ(int a, float x, float y,int m=_MIRROR_NONE, float vx=0, float vy=0,float alpha=1);
	CTX_TPZ(int a, float x, float y,CPlayer *p);
	//��Ч������Ϻ󷵻�false����֪����ɾ������Ч
	bool Run(float vir_x,float *py);
};

#endif