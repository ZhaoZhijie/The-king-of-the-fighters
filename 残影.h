#ifndef  _��Ӱ_H
#define _��Ӱ_H
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
	int m_Last;//���һ��λ��
	int m_Size;//�Ѿ�����ĸ���
public:
	CTX_CY(CPlayer* player,int max);
	bool Run(float vir_x,float *py);
	~CTX_CY();
};

#endif