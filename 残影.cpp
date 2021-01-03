#include "残影.h"

CTX_CY::CTX_CY(CPlayer* player,int max)
{
	if(max<0)
		m_Max=0;
	else if(max>200)
		m_Max=200;
	else
		m_Max=max;
	m_PreF=new PreData[max];
	m_Player=player;
	m_Move=player->m_CurMove;
	m_Size=0;
	m_Last=0;
}

bool CTX_CY::Run(float vir_x,float *py)
{
	if(m_Player->m_CurMove!=m_Move)
		return false;
	PreData pd={m_Player->m_CurMove,m_Player->m_CurF,m_Player->m_x,m_Player->m_y,m_Player->m_Face};
	m_PreF[m_Last]=pd;
	m_Last=(m_Last+1)%m_Max;
	if(m_Size<m_Max)
		m_Size++;
	//第一个残影的下标
	int startpos=(m_Last-m_Size+m_Max)%m_Max;
	for(int i=0;i<m_Size;i++)
	{
		int n=(startpos+i)%m_Max;
		int dx=m_PreF[n].x-vir_x- CGameEngine::GetGE()->GetMoves()->GetMoveX(m_PreF[n].m, m_PreF[n].f);
		int dy=m_PreF[n].y  - CGameEngine::GetGE()->GetMoves()->GetMoveY(m_PreF[n].m, m_PreF[n].f);	
		int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_PreF[n].m, m_PreF[n].f);	
		int mirror=_MIRROR_NONE;
		float alpha=i*1.0/m_Size;
		if(alpha<0)
			alpha=0;
		if(m_PreF[n].face==_FACE_LEFT)
		{
			dx=m_PreF[n].x -vir_x- sw+CGameEngine::GetGE()->GetMoves()->GetMoveX(m_PreF[n].m, m_PreF[n].f);
			mirror=_MIRROR_LR;
		}
		CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_PreF[n].m, m_PreF[n].f), 
			dx,dy,mirror,m_Player->m_Cor,alpha);	
	}
	return true;
}

CTX_CY::~CTX_CY()
{
	delete []m_PreF;
}