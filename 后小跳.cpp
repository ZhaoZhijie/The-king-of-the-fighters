#include "后小跳.h"
#include "幻影.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_HXT::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10)
	{
		actPlayer->m_CurMove=86;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->m_vx=-7  ;
		actPlayer->m_vy=-5;
		actPlayer->m_TX.push_back(new CTX_HY(actPlayer,10));
		actPlayer->EmptyKeyIn();
		return true;
	}

	return false;
}

void CS_HXT::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_y==400&&actPlayer->m_vy==0)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_vx=0;
	}
	actPlayer->m_CurSCF++;
}