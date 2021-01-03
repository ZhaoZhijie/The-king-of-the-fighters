#include "投技.h"
#include "图片帧.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_TJ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if((actsite==10||actsite==12)
		&&(defsite/10==1||defsite/10==2)
		&&(abs(actPlayer->m_x-defPlayer->m_x)<70)
		&&actPlayer->GetKeyState('F')==_KS_DH)//技能触发,与敌人贴身时才可触发，触发即命中
	{//20
		actPlayer->m_CurMove=20;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		defPlayer->m_CurMove=75;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_HurtS=this;
		defPlayer->m_CurS=NULL;
		defPlayer->m_CurHCF=0;
		defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30);
		defPlayer->m_vx=0;
		defPlayer->m_vy=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("投技");
		actPlayer->m_TX.push_back(new CTX_TPZ(113,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?25:-25),actPlayer->m_y-55,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return true;
	}
	return false;
}

void CS_TJ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurSCF==32)
		actPlayer->m_TX.push_back(new CTX_TPZ(112,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?50:-50),actPlayer->m_y-75,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	actPlayer->m_CurSCF++;
}
//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CS_TJ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	//该技能没有矩形，在触发时直接命中
	return false;
}

//技能命中后双方该怎么做
void CS_TJ::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int c=defPlayer->m_CurHCF;
	if(c<32&&c>8)
	{//前15帧固定弯腰姿势
		defPlayer->m_CurCF--;
	}else if(c>=32)
	{
		defPlayer->m_HurtS=NULL;
		actPlayer->m_CurS=NULL;
		defPlayer->m_CurMove=39;
		defPlayer->m_vy=-6;
		defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?5:-5;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("爪击");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("呀");
	}
	defPlayer->m_CurHCF++;
	return;
}