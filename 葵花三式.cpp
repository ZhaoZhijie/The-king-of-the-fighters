#include "葵花三式.h"
#include "图片帧.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_KH::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove, actPlayer->m_CurF);
	bool trigger=true;
	if(actsite==10||actsite==12||actsite==20||actsite==22)//技能触发 第一式
	{
		actPlayer->m_CurMove=52;
		actPlayer->m_vx=6;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("葵1");
	}
	else if(actPlayer->m_Tag==52&&actPlayer->m_LF<180&&(actsite%10==0||actsite%10==2||(actsite%10==3&&actPlayer->m_CurMove==52)))//触发第二式
	{
		actPlayer->m_CurMove=53;
		actPlayer->m_vx=6;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("葵2");
	}
	else if(actPlayer->m_Tag==53&&actPlayer->m_LF<180&&(actsite%10==0||actsite%10==2||(actsite%10==3&&actPlayer->m_CurMove==53)))//触发第三式
	{
		actPlayer->m_CurMove=54;
		actPlayer->m_vx=6;
		actPlayer->m_vy=-8;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("葵3");
	}
	else
		trigger=false;
	if(trigger)
	{
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;	
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("轻拳");
	}
	return trigger;
}

//技能触发后的持续控制 主要用于调节自身的动作
void CS_KH::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurMove==54&&actPlayer->m_y==400&&actPlayer->m_vy==0)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_vx=0;
	}
	actPlayer->m_CurSCF++;
}

//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CS_KH::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==14||(defPlayer->m_HurtS==this&&defPlayer->m_CurHCF%1000!=0&&actPlayer->m_CurMove!=54)||(actPlayer->m_CurMove==54&&defPlayer->m_CurHCF/1000==3&&defPlayer->m_CurHCF%1000!=0))
	{
		if(defsite==12)
		{
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),defPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		}
		return false;
	}
	defPlayer->m_CurHCF=0;
	if(defsite/10==2)
	{
		defPlayer->m_CurMove=33;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
	}
	defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?5:-5;
	if(actPlayer->m_CurMove==52&&defsite/10==1)//被第一式打到
	{
		defPlayer->m_CurMove=27;
		defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?2:-2;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_CurHCF=1000;
	}
	if(actPlayer->m_CurMove==53&&defsite/10==1)//被第二式打到
	{
		defPlayer->m_CurMove=117;
		//defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?2:-2;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_CurHCF=2000;
	}
	if(actPlayer->m_CurMove==54)//被第三式打到要跌倒
	{
		OutputDebugStringA("达到了\n");
		defPlayer->m_vy+=6;
		defPlayer->m_vx+=(defPlayer->m_Face==actPlayer->m_Face?4:-4);
		defPlayer->m_CurHCF=3000;
	}
	if(actPlayer->m_CurMove==54&&defsite/10==2)
	{
		defPlayer->m_CurMove=83;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
	}
	defPlayer->m_CurS=NULL;
	defPlayer->m_HurtS=this;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("绊脚");
	actPlayer->m_TX.push_back(new CTX_TPZ(111,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?50:-50),actPlayer->m_y-80,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return false;
}

//技能命中后对对方的持续控制 用于准确控制对方的动作
void CS_KH::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(defPlayer->m_CurHCF>20&&defPlayer->m_CurHCF<1000)
		defPlayer->m_HurtS=NULL;
	if(defPlayer->m_CurHCF==2010)
	{
		defPlayer->m_vy=-13;
		defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?3:-3;
	}
	 if(defPlayer->m_CurHCF>=2022)
			defPlayer->m_HurtS=NULL;
	if((defPlayer->m_CurHCF>1010&&actPlayer->m_CurMove==52)||defPlayer->m_CurMove==55)
		defPlayer->m_HurtS=NULL;
	defPlayer->m_CurHCF++;
}