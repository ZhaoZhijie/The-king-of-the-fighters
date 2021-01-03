#include "站重拳.h"
#include "图片帧.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_ZZQ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==10||actsite==12)//站立重拳
	{
		actPlayer->m_CurMove=6;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("哈");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("轻拳");
		return true;
	}
	return false;
}

void CS_ZZQ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{}

bool CS_ZZQ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==22||defsite==14||defsite%10==9)//14是在地上滚动
	{
		if(defsite==12||defsite==22)
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),actPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return false;
	}
	if(defsite/10==1)
		defPlayer->m_CurMove=27;
	else if(defsite/10==2)
		defPlayer->m_CurMove=33;
	actPlayer->m_TX.push_back(new CTX_TPZ(98,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?75:-75),actPlayer->m_y-50,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("爪击");
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_HurtS=NULL;
	defPlayer->m_CurS=NULL;
	return true;
}