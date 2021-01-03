#include "������.h"
#include "��˸.h"
#include "TeXiao.h"
#include <list>
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_AGS::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)//���ܴ���
	{
		actPlayer->m_CurMove=67;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");
		return true;
	}
	return false;
}

void CS_AGS::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurSCF==13)
	{
		Bullet b={actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?50:-50), 400, 15, 0, 68, 0, 0, _ZD_LAST,(actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR), this};
		actPlayer->m_Bullet.push_back(b);
	}
	actPlayer->m_CurSCF++;
}

//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
bool CS_AGS::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==22||defsite==14)//14���ڵ��Ϲ���
		return false;
	if(defsite/10==2)
	{
		defPlayer->m_CurMove=33;
		defPlayer->m_TX.push_back(new CTX_SS(18,defPlayer));
	}
	else if(defsite/10==1)
	{
		defPlayer->m_CurMove=75;
		defPlayer->m_TX.push_back(new CTX_SS(15,defPlayer));
	}
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");	
	defPlayer->m_CurCF=0;
	defPlayer->m_CurF=0;
	defPlayer->m_CurS=NULL;
	return false;
}

//�������к�ĳ�������
void CS_AGS::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	return;
}