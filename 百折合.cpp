#include "百折合.h"

//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_BZH::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==30&&actPlayer->m_y<320
		&&((actPlayer->m_Face==_FACE_RIGHT&&actPlayer->m_x>defPlayer->m_x)||(actPlayer->m_Face==_FACE_LEFT&&actPlayer->m_x<defPlayer->m_x)))//技能触发
	{
		actPlayer->m_CurMove=51;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("哈");
		return true;
	}
	return false;
}

//技能触发后的持续控制
void CS_BZH::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurMove==51&&CGameEngine::GetGE()->GetMoves()->GetContinueFrame(actPlayer->m_CurMove,actPlayer->m_CurF)==-1)
	{
		//actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurMove=5;
		actPlayer->m_CurF=7;
		actPlayer->m_CurCF=0;
	}
	else if(actPlayer->m_CurMove==5&&CGameEngine::GetGE()->GetMoves()->GetContinueFrame(actPlayer->m_CurMove,actPlayer->m_CurF)==-1)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
	}
	actPlayer->m_CurSCF++;
}

//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CS_BZH::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite==12||defsite==22||defsite==14)//14是在地上滚动
		return false;
	if(defsite/10==2)
	{
		defPlayer->m_CurMove=33;
	}
	else if(defsite/10==1)
	{
		defPlayer->m_CurMove=75;
	}
	defPlayer->m_CurCF=0;
	defPlayer->m_CurF=0;
	defPlayer->m_CurS=NULL;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("绊脚");
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("轻拳");
	return true;
}

//技能命中后双方该怎么做
void CS_BZH::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	return;
}