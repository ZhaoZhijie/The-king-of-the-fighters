#include "վ��ȭ.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_ZQQ::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);

	if(actsite==10||actsite==12)//վ����ȭ
	{
		actPlayer->m_CurMove=80;
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

void CS_ZQQ::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{}

bool CS_ZQQ::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==22||defsite==12||defsite==14||defsite%10==9)
		return false;
	if(defsite/10==1)//�Է�վ��������
		defPlayer->m_CurMove=74;
	else if(defsite/10==2)//�Է��¶ױ�����
		defPlayer->m_CurMove=32;
	defPlayer->m_CurF=0;
	defPlayer->m_CurCF=0;
	defPlayer->m_CurS=NULL;
	defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?3:-3;
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("���");	
	actPlayer->m_TX.push_back(new CTX_TPZ(111,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-65,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return true;
}