#ifndef  _ª√”∞_H
#define _ª√”∞_H
#include "TeXiao.h"
#include "Player.h"
#include <list>
class CPlayer;
class CTX_HY:public CTeXiao
{
struct PreData
{
	int m;
	int f;
	float x;
	float y;
	int face;
};
private:
	CPlayer * m_Player;
	std::list<PreData> m_PreF;
	int m_Max;
	int m_Move;
public:
	CTX_HY(CPlayer* player,int max);
	bool Run(float vir_x,float *py);
};

#endif