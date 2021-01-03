#include "»ÃÓ°.h"

CTX_HY::CTX_HY(CPlayer* player,int max)
{
	m_Player=player;
	m_Max=max;
	m_Move=player->m_CurMove;
}

bool CTX_HY::Run(float vir_x,float *py)
{
	if(m_Player->m_CurMove!=m_Move)
		return false;
	int n=1;
	for(std::list<PreData>::iterator i=m_PreF.begin();i!=m_PreF.end();i++)
	{
		int dx=i->x-vir_x- CGameEngine::GetGE()->GetMoves()->GetMoveX(i->m, i->f);
		int dy=i->y  - CGameEngine::GetGE()->GetMoves()->GetMoveY(i->m, i->f);	
		int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(i->m, i->f);	
		int mirror=_MIRROR_NONE;
		float alpha=n++*1.0/m_PreF.size();
		if(alpha<0)
			alpha=0;
		if(i->face==_FACE_LEFT)
		{
			dx=i->x -vir_x- sw+CGameEngine::GetGE()->GetMoves()->GetMoveX(i->m, i->f);
			mirror=_MIRROR_LR;
		}
		CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(i->m, i->f), 
			dx,dy,mirror,m_Player->m_Cor,alpha);
	}

	int dx=m_Player->m_x -vir_x - CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player->m_CurMove, m_Player->m_CurF);
	int dy=m_Player->m_y  - CGameEngine::GetGE()->GetMoves()->GetMoveY(m_Player->m_CurMove, m_Player->m_CurF);	
	int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_Player->m_CurMove, m_Player->m_CurF);	
	int mirror=_MIRROR_NONE;
	if(m_Player->m_Face==_FACE_LEFT)
	{
		dx=m_Player->m_x -vir_x - sw+CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player->m_CurMove, m_Player->m_CurF);
		mirror=_MIRROR_LR;
	}
	CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_Player->m_CurMove,m_Player->m_CurF), 
		dx,dy,mirror,m_Player->m_Cor);

	PreData pd={m_Player->m_CurMove,m_Player->m_CurF,m_Player->m_x,m_Player->m_y,m_Player->m_Face};
	m_PreF.push_back(pd);
	if(m_PreF.size()==m_Max)
		m_PreF.pop_front();
	return true;
}