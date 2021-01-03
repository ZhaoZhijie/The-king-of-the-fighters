#include "下蹲.h"

//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_XD::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	bool tag=true;
	if((actsite==10||actsite==12)&&(actPlayer->GetKeyState('D')==_KS_DC||actPlayer->GetKeyState('D')==_KS_DH))//技能触发
	{
		actPlayer->m_CurMove=4;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
	}else if((actsite==20||actsite==22)&&actPlayer->m_CurS!=this)
	{
			actPlayer->m_CurS=this;
			actPlayer->m_CurSCF=0;
	}else
		tag=false;
	return tag;
}

void CS_XD::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==20&&(actPlayer->GetKeyState('D')==_KS_UC||actPlayer->GetKeyState('D')==_KS_UH))
	{
		actPlayer->m_CurMove=1;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=NULL;
	}
	actPlayer->m_CurSCF++;
}