#include "站轻拳.h"
#include "图片帧.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_ZQQ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==10||actsite==12)//站立轻拳
	{
		actPlayer->m_CurMove=80;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("轻拳");	
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("哼");	
		return true;
	}
	return false;
}

void CS_ZQQ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{}

bool CS_ZQQ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==22||defsite==12||defsite==14||defsite%10==9)
		return false;
	if(defsite/10==1)//对方站立被击中
		defPlayer->m_CurMove=74;
	else if(defsite/10==2)//对方下蹲被击中
		defPlayer->m_CurMove=32;
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_CurS=NULL;
	defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?3:-3;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("绊脚");	
	actPlayer->m_TX.push_back(new CTX_TPZ(111,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-65,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return true;
}