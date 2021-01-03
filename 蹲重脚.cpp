#include "蹲重脚.h"
#include "图片帧.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_DZJ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==20||actsite==22)//蹲重脚
	{
		actPlayer->m_CurMove=15;
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

void CS_DZJ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{

}

bool CS_DZJ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==22||defsite%10==9)
	{
		if(defsite==22)
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),actPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return false;
	}
	defPlayer->m_CurMove=39;
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_vx=(defPlayer->m_Face==actPlayer->m_Face?5:-5);
	defPlayer->m_vy=-4;
	defPlayer->m_CurS=NULL;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("绊脚");
	actPlayer->m_TX.push_back(new CTX_TPZ(112,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30),actPlayer->m_y-50,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return true;
}