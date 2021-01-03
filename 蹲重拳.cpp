#include "¶×ÖØÈ­.h"
#include "Í¼Æ¬Ö¡.h"
//¼¼ÄÜ´¥·¢Ìõ¼şÅĞ¶¨£¨ÊÇÆ¥Åäµ½°´¼üºóµÄÅĞ¶¨£¬¾àÀë£¬Ë«·½×´Ì¬µÈ£©
bool CS_DZQ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==20||actsite==22)//¶×ÖØÈ­ 
	{
		actPlayer->m_CurMove=13;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("¹ş");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("ÇáÈ­");
		return true;
	}
	return false;
}

void CS_DZQ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{}

bool CS_DZQ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==22||defsite==14||defsite%10==9)
	{
		if(defsite==12)
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),defPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return false;
	}
	if(defsite/10==1)
		defPlayer->m_CurMove=75;
	else if(defsite/10==2)
		defPlayer->m_CurMove=33;
	actPlayer->m_TX.push_back(new CTX_TPZ(100,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?40:-40),actPlayer->m_y-80,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("×¦»÷");	
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	return true;
}