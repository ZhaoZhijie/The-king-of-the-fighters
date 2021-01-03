#include "后退.h"

//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_HT::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if((actsite==10||actsite==12)&&(defsite%10==0||defsite%10==1||defsite%10==2||defsite%10==4||defsite%10==9)
		&&actPlayer->m_CurMove!=3&&(actPlayer->GetKeyState('B')==_KS_DC||actPlayer->GetKeyState('B')==_KS_DH)
		&&actPlayer->GetKeyState('D')!=_KS_DH
		&&actPlayer->GetKeyState('D')!=_KS_DC
		&&actPlayer->GetKeyState('F')!=_KS_DH
		&&actPlayer->GetKeyState('F')!=_KS_DC)//技能触发
	{
		actPlayer->m_CurMove=3;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		return true;
	}
	return false;
}

void CS_HT::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->GetKeyState('B')==_KS_DH&&actPlayer->m_CurSCF>1)
	{
		actPlayer->m_vx=-3;
	}else if(actPlayer->m_CurSCF>1)
	{
		actPlayer->m_CurMove=1;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=NULL;
	}
	actPlayer->m_CurSCF++;
}