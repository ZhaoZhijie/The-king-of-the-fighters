#include "���ؽ�.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_TZJ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==30&&actPlayer->m_vy<350
		&&((actPlayer->m_Face==_FACE_RIGHT&&actPlayer->m_x<defPlayer->m_x)||(actPlayer->m_Face==_FACE_LEFT&&actPlayer->m_x>defPlayer->m_x)))
	{
		actPlayer->m_CurMove=19;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ȭ");
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��");
		return true;
	}
	return false;
}

void CS_TZJ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_y==400&&actPlayer->m_vy==0)
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
}

bool CS_TZJ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite==12||defsite==14||defsite%10==9)
	{
		if(defsite==12)
			actPlayer->m_TX.push_back(new CTX_TPZ(109,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-10:10),defPlayer->m_y-90,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
		return false;
	}
	if(defsite/10==1)//�Է�վ��������
		defPlayer->m_CurMove=75;
	else if(defsite/10==2)//�Է��¶ױ�����
		defPlayer->m_CurMove=33;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("���");
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_CurS=NULL;
	//defPlayer->m_HurtS=this;
	//defPlayer->m_CurHCF=0;
	actPlayer->m_TX.push_back(new CTX_TPZ(112,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-70,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return true;
}

//�������к�ԶԷ��ĳ������� ����׼ȷ���ƶԷ��Ķ���
//void CS_TZJ::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
//{
//	if(defPlayer->m_CurHCF>6)
//		defPlayer->m_HurtS=NULL;
//	defPlayer->m_CurHCF++;
//}