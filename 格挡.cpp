#include "格挡.h"

//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_GD::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if((actsite==10||actsite==20||actsite==12||actsite==22)&&(defPlayer->m_Bullet.size()!=0||(defsite%10!=0&&defsite%10!=1&&defsite%10!=2&&defsite%10!=4&&defsite%10!=9))&&(actPlayer->GetKeyState('B')==_KS_DC||actPlayer->GetKeyState('B')==_KS_DH))//触发格挡
	{
		if(actPlayer->GetKeyState('D')==_KS_DC||actPlayer->GetKeyState('D')==_KS_DH)
			actPlayer->m_CurMove=25;
		else
			actPlayer->m_CurMove=24;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=NULL;
		return true;
	}
	return false;
}
