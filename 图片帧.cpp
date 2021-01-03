#include "TeXiao.h"
#include "Player.h"
#include "ͼƬ֡.h"
CTX_TPZ::CTX_TPZ(int a, float x, float y, int m, float vx, float vy,float alpha)
{
	m_Move=a;
	m_CurF=0;
	m_CF=0;
	m_x=x;
	m_y=y;
	m_mirror=m;
	m_vx=vx;
	m_vy=vy;
	m_Alpha=alpha;
	type=0;
}
CTX_TPZ::CTX_TPZ(int a, float x, float y,CPlayer *p)
{
	type=1;
	m_Move=a;
	m_CurF=0;
	m_CF=0;
	m_x=x;
	m_y=y;
	m_Player=p;
	m_preM=p->m_CurMove;
	m_preF=p->m_CurF;
	m_Alpha=1;
}
bool CTX_TPZ::Run(float vir_x,float *py)
{
	if(type==0)
	{
		int dx=m_x -vir_x - CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Move, m_CurF);
		int dy=m_y- CGameEngine::GetGE()->GetMoves()->GetMoveY(m_Move, m_CurF);	
		int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_Move, m_CurF);	
		if(m_mirror==_MIRROR_LR)
		{
			dx=m_x - vir_x +CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Move, m_CurF)-sw;
		}
		CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_Move,m_CurF), 
				dx,dy,m_mirror,_COR_RED,m_Alpha);
		m_CF++;
	
		m_x+=(m_mirror==_MIRROR_NONE?m_vx:-m_vx);
		m_y+=m_vy;
		if(CGameEngine::GetGE()->GetMoves()->GetContinueFrame(m_Move, m_CurF)<=m_CF)
		{
			m_CurF++;
			m_CF=0;
			if(m_CurF>=CGameEngine::GetGE()->GetMoves()->GetFrameLen(m_Move))
				return false;
		}
		return true;	
	}
	
	//type==1;
	if(m_Player->m_CurMove!=m_preM)
		return false;
	if(m_Player->m_CurF!=m_preF)
		return false;
	int dx=m_Player->m_x+m_x -vir_x - CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Move, m_CurF);
	int dy=m_Player->m_y+m_y- CGameEngine::GetGE()->GetMoves()->GetMoveY(m_Move, m_CurF);	
	int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_Move, m_CurF);	
	if(m_Player->m_Face==_FACE_LEFT)
	{
		dx=m_Player->m_x-m_x - vir_x +CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Move, m_CurF)-sw;
	}
	CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_Move,m_CurF), 
			dx,dy,m_Player->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR,_COR_RED,m_Alpha);
	m_CF++;
	if(CGameEngine::GetGE()->GetMoves()->GetContinueFrame(m_Move, m_CurF)<=m_CF)
	{
		m_CurF++;
		m_CF=0;
		if(m_CurF>=CGameEngine::GetGE()->GetMoves()->GetFrameLen(m_Move))
			m_CurF=0;
	}
	return true;
}