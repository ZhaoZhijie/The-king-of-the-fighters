#ifndef  _图片帧_H
#define _图片帧_H
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
	//type不等于0 表示特效会持续播放 直至type表示的按键弹起 否则只播放一次
	CTX_TPZ(int a, float x, float y,int m=_MIRROR_NONE, float vx=0, float vy=0,float alpha=1);
	CTX_TPZ(int a, float x, float y,CPlayer *p);
	//特效播放完毕后返回false，告知场景删除此特效
	bool Run(float vir_x,float *py);
};

#endif