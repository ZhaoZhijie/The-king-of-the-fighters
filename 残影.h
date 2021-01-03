#ifndef  _残影_H
#define _残影_H
#include "TeXiao.h"
#include "Player.h"
class CPlayer;
class CTX_CY:public CTeXiao
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
	PreData *m_PreF;
	int m_Max;
	int m_Move;
	int m_Last;//最后一个位置
	int m_Size;//已经保存的个数
public:
	CTX_CY(CPlayer* player,int max);
	bool Run(float vir_x,float *py);
	~CTX_CY();
};

#endif