#include "м��.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_XF::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)
	{
		actPlayer->m_CurMove=114;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		return true;
	}
	return false;
}

void CS_XF::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	actPlayer->m_CurSCF++;
}
//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
bool CS_XF::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite/10==3&&defPlayer->m_HurtS!=this)//14���ڵ��Ϲ���
		return false;
	actPlayer->m_CurMove=115;
	actPlayer->m_CurCF=0;
	actPlayer->m_CurF=0;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("Ͷ��");
	actPlayer->m_TX.push_back(new CTX_TPZ(113,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30),actPlayer->m_y-75,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	defPlayer->m_CurMove=116;
	defPlayer->m_Face=actPlayer->m_Face==_FACE_RIGHT?_FACE_LEFT:_FACE_RIGHT;
	defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30);
	defPlayer->m_CurCF=0;
	defPlayer->m_CurF=0;
	defPlayer->m_HurtS=this;
	defPlayer->m_CurHCF=0;
	defPlayer->m_CurS=NULL;
	defPlayer->m_vx=0;
	defPlayer->m_vy=0;
	return false;
}

//�������к�˫������ô��
void CS_XF::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(defPlayer->m_CurHCF>=30&&defPlayer->m_CurHCF<=34)
		defPlayer->m_vx+=3;
	else if(defPlayer->m_CurHCF==35)
	{
		defPlayer->m_Face=actPlayer->m_Face;
		defPlayer->m_vx=-13;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��");
	}
	else if(defPlayer->m_CurHCF>35&&defPlayer->m_vx<0)
	{
		defPlayer->m_vx+=0.8;
		if(defPlayer->m_vx>=0)
			defPlayer->m_vx=0;
	}
	if(defPlayer->m_CurHCF>61)
		defPlayer->m_HurtS=NULL;	
	defPlayer->m_CurHCF++;
	return;
}