#include "鬼烧.h"
#include "图片帧.h"
#include "变帧率.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_GS::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)//技能触发
	{
		actPlayer->m_CurMove=56;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("鬼烧");
		return true;
	}
	return false;
}

//技能触发后的持续控制 主要用于调节自身的动作
void CS_GS::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurSCF==14)
	{
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		actPlayer->m_TX.push_back(new CTX_TPZ(85,actPlayer->m_x,actPlayer->m_y,m));
	}
	if(actPlayer->m_CurSCF==15)
	{
		actPlayer->m_vy=-5;
	}

	if(actPlayer->m_y==400&&actPlayer->m_vy==0&&actPlayer->m_CurSCF>15)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=NULL;
	}
	actPlayer->m_CurSCF++;
}

//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CS_GS::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite==12||defsite==14||defsite==22)
		return false;
	int t=0;
	defPlayer->m_CurMove=39;
	t=19;
	defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?5:-5;
	defPlayer->m_vy=-4;
	defPlayer->m_TX.push_back(new CTX_SS(t,defPlayer));
	actPlayer->m_TX.push_back(new CTX_BZL(6,2));	
	defPlayer->m_CurCF=0;
	defPlayer->m_CurF=0;
	defPlayer->m_CurS=NULL;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("嗡嗡");	
	return true;
}

//技能命中后双方该怎么做
void CS_GS::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	return;
}