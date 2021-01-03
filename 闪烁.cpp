#include "иак╦.h"
#include "GameEngine.h"
CTX_SS::CTX_SS(int len,CPlayer* player, int type, float gray)
{
	m_Len=len;
	m_CurF=0;
	m_Player=player;
	m_pM=m_Player->m_CurMove;
	m_CF=0;
	m_Add=true;
	m_Type=type;
	m_Gray=gray;
}

bool CTX_SS::Run(float vir_x,float *py)
{
	if(m_CurF>=m_Len)
	{
		if(m_Type==_SS_ONCE)
			return false;
		else
			m_CurF=0;
	}
	if(m_Type==_SS_LAST)
	{
		if(m_Player->m_CurMove!=m_pM)
			return false;
	}
	int dx=m_Player->m_x -vir_x - CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player->m_CurMove, m_Player->m_CurF);
	int dy=m_Player->m_y  - CGameEngine::GetGE()->GetMoves()->GetMoveY(m_Player->m_CurMove, m_Player->m_CurF);	
	int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_Player->m_CurMove, m_Player->m_CurF);	
	int m=_MIRROR_NONE;
	float alpha=abs(m_CurF-m_Len/2)*2.0/m_Len+m_Gray;
	if(m_Player->m_Face==_FACE_LEFT)
	{
		dx=m_Player->m_x -vir_x  - sw+CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player->m_CurMove, m_Player->m_CurF);
		m=_MIRROR_LR;
	}
	CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_Player->m_CurMove,m_Player->m_CurF), 
			dx,dy,m,_COR_BLUE,alpha);
	m_CurF++;
	return true;
}