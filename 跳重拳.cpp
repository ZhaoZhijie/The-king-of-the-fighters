#include "����ȭ.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_TZQ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==30&&actPlayer->m_vy<350
		&&((actPlayer->m_Face==_FACE_RIGHT&&actPlayer->m_x<defPlayer->m_x)||(actPlayer->m_Face==_FACE_LEFT&&actPlayer->m_x>defPlayer->m_x)))
	{
		actPlayer->m_CurMove=17;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ȭ");
		return true;
	}
	return false;
}

void CS_TZQ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_y==400&&actPlayer->m_vy==0)
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
}

bool CS_TZQ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite==12||defsite==14||defsite%10==9)//14���ڵ��Ϲ���  �����ϸ�
	{
		if(defsite==12)
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),defPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return false;
	}
	if(defsite/10==1)
		defPlayer->m_CurMove=75;
	else if(defsite/10==2)
	{
		defPlayer->m_CurMove=33;
	}
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("���");
	return true;
}