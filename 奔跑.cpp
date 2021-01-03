#include "奔跑.h"

//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_BP::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12)
	{
		actPlayer->m_CurMove=79;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->m_vx=5;
		actPlayer->EmptyKeyIn();
		return true;
	}
	return false;
}

void CS_BP::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	actPlayer->m_vx=5;
	if(actPlayer->m_CurSCF%10==0)
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("跑步");
	actPlayer->m_CurSCF++;
}