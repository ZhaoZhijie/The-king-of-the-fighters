#include "八酒杯.h"
#include "图片帧.h"
#include "闪烁.h"
#include "震屏.h"
//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
bool CS_BJB::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)//技能触发
	{
		actPlayer->m_CurMove=101;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=1000;
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		actPlayer->m_TX.push_back(new CTX_TPZ(88,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-30:30),actPlayer->m_y-90,m));	
		//Bullet b={actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-40:40), actPlayer->m_y, 0, 0, 73, 0, 0, _ZD_LAST,(actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR), this};
		//actPlayer->m_Bullet.push_back(b);
		actPlayer->m_TX.push_back(new CTX_TPZ(73,-40,0,actPlayer));	
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("绝招");	
		return true;
	}
	return false;
}

//技能触发后的持续控制 主要用于调节自身的动作
void CS_BJB::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->GetKeyState('x')==_KS_DH&&actPlayer->m_CurF==0&&actPlayer->m_CurCF==1&&actPlayer->m_CurSCF<1150000&&actPlayer->m_CurSCF>=1000)
	{
		actPlayer->m_CurCF--;
		if(actPlayer->m_CurCF<0)
			actPlayer->m_CurCF=0;
	}else if((actPlayer->GetKeyState('x')==_KS_UC||actPlayer->m_CurSCF>=1150)&&actPlayer->m_CurF==0&&actPlayer->m_CurCF==1)
	{
		//actPlayer->m_Bullet.pop_back();//结束苍焰
		actPlayer->m_CurSCF=0;
	}else if(actPlayer->m_CurSCF==18)
	{//102 72
		Bullet b={actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?70:-70), actPlayer->m_y, 15, 0, 72, 0, 0, _ZD_LAST,(actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR), this};
		actPlayer->m_Bullet.push_back(b);	
		//actPlayer->m_TX.push_back(new CTX_TPZ(102,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?100:-100),actPlayer->m_y, (actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR),4,0));
		actPlayer->m_CurS=NULL;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("炸裂");	
		actPlayer->m_TX.push_back(new CTX_ZP(30));
	}
	actPlayer->m_CurSCF++;
}

//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CS_BJB::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==14||defsite==22||defsite%10==9||defPlayer->m_HurtS==this)
		return false;
	if(defsite/10==1)
	{
		defPlayer->m_CurMove=27;
	}else if(defsite/10==2)
	{
		defPlayer->m_CurMove=33;
	}if(defsite/10==3)
	{
		defPlayer->m_CurMove=27;
		defPlayer->m_vy=0;
	}
	defPlayer->m_TX.push_back(new CTX_SS(100,defPlayer,_SS_LAST,-0.2));
	defPlayer->m_vx=0;
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_CurS=NULL;
	defPlayer->m_HurtS=this;
	defPlayer->m_CurHCF=0;
	return true;
}

//技能命中后双方该怎么做
void CS_BJB::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defPlayer->m_CurMove==27||defPlayer->m_CurMove==33)
	{
		defPlayer->m_CurCF--;
		if(defPlayer->m_CurCF<0)
			defPlayer->m_CurCF=0;
		if(defPlayer->m_y<400)
		{
			defPlayer->m_vx=0;
			defPlayer->m_vy=0;	
		}
	}
	if(defPlayer->m_CurHCF>200)
	{
		defPlayer->m_HurtS=NULL;
	}
	defPlayer->m_CurHCF++;
	return;
}