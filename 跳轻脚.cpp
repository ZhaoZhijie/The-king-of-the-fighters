#include "�����.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_TQJ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==30&&actPlayer->m_vy<350
		&&((actPlayer->m_Face==_FACE_RIGHT&&actPlayer->m_x<defPlayer->m_x)||(actPlayer->m_Face==_FACE_LEFT&&actPlayer->m_x>defPlayer->m_x)))
	{
		actPlayer->m_CurMove=18;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ȭ");
		return true;
	}
	return false;
}

void CS_TQJ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_y==400&&actPlayer->m_vy==0)
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
}

bool CS_TQJ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==14||defsite%10==9)
		return false;
	if(defsite/10==1)//�Է�վ��������
		defPlayer->m_CurMove=74;
	else if(defsite/10==2)//�Է��¶ױ�����
		defPlayer->m_CurMove=32;
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("���");
	actPlayer->m_TX.push_back(new CTX_TPZ(111,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-70,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return true;
}