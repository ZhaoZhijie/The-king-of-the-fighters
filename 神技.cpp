#include "��.h"
#include "ͼƬ֡.h"
#include "��Ӱ.h"
#include "��Ӱ.h"
#include "��֡��.h"
#include "����.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_SJ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)//���ܴ���
	{
		actPlayer->m_CurMove=61;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->m_TX.push_back(new CTX_TPZ(88,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30),actPlayer->m_y-45,(actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR)));	
		actPlayer->m_TX.push_back(new CTX_CY(actPlayer,8));	
		actPlayer->m_TX.push_back(new CTX_BZL(10,3));	
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");	
		return true;
	}
	return false;
}

void CS_SJ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurSCF<5)
	{
		actPlayer->m_CurCF--;
	}
	if(actPlayer->m_CurSCF==12)
	{//-7 12
		actPlayer->m_vy=-8;
		actPlayer->m_vx=20;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");
	}
	if(actPlayer->m_y==400&&CGameEngine::GetGE()->GetMoves()->GetContinueFrame(actPlayer->m_CurMove,actPlayer->m_CurF)==-1)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
	}
	actPlayer->m_CurSCF++;
}

//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
bool CS_SJ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite%10==9)
		return false;
	actPlayer->m_CurMove=103;
	actPlayer->m_CurF=0;
	actPlayer->m_CurCF=0;
	actPlayer->m_TX.push_back(new CTX_HY(actPlayer,8));	
	defPlayer->m_CurS=NULL;
	defPlayer->m_HurtS=this;
	defPlayer->m_CurHCF=0;
	defPlayer->m_CurMove=104;	
	defPlayer->m_CurCF=0;	
	defPlayer->m_CurF=0;	
	defPlayer->m_TX.push_back(new CTX_HY(defPlayer,8));
	defPlayer->m_Face=actPlayer->m_Face==_FACE_RIGHT?_FACE_LEFT:_FACE_RIGHT;
	return true;
}

//�������к�˫������ô��
void CS_SJ::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int c=defPlayer->m_CurHCF;
	if(c<173)
	{
		defPlayer->m_vx=0;
		defPlayer->m_vy=0;	
	}
	if(c==15)
		actPlayer->m_TX.push_back(new CTX_TPZ(102,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?100:-100),actPlayer->m_y, (actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR)));
	else if(c==43)
	{
		defPlayer->m_TX.push_back(new CTX_TPZ(106,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?70:-70),actPlayer->m_y, (actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR),0,0,0.4));
	}
	else if(c==53)
	{
		defPlayer->m_TX.push_back(new CTX_TPZ(107,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?70:-70),actPlayer->m_y, (actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR),0,0,0.4));		
	}
	else if(c==25)
	{
		defPlayer->m_CurMove=105;
		defPlayer->m_CurF=0;
		defPlayer->m_CurCF=0;
		//��Ч
		defPlayer->m_TX.push_front(new CTX_HY(defPlayer,10));
		//actPlayer->m_TX.push_back(new CTX_BZL(150,2));	
	}
	else if(c==36)
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����2");
	if(c>=0&&c<25)
	{//���Է����ڵ���
		defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?50:-50);
		defPlayer->m_y=actPlayer->m_y;

	}

	if(c>=25&&c<173)
	{
		//���Է�������	
		defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?80:-80);
		defPlayer->m_y=actPlayer->m_y-150;
		if(c>=36)
			defPlayer->m_y=actPlayer->m_y-50;
		defPlayer->m_vx=0;
		defPlayer->m_vy=0;
	}else if(c==173)
	{
		//���Է��׳�
		defPlayer->m_CurMove=39;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?6:-6;
		defPlayer->m_vy=-7;
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		actPlayer->m_TX.push_back(new CTX_TPZ(97,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?80:-80),actPlayer->m_y-100,m,0,0,0.7));
		defPlayer->m_TX.push_back(new CTX_SS(18,defPlayer));
		//actPlayer->m_TX.push_back(new CTX_BZL(5,3));	
		actPlayer->m_CurS=NULL;
		defPlayer->m_HurtS=NULL;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("ը��4");	
		actPlayer->m_TX.push_back(new CTX_ZP(20));
	}
	defPlayer->m_CurHCF++;
	return;
}