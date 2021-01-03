#include "������ʽ.h"
#include "ͼƬ֡.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_KH::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove, actPlayer->m_CurF);
	bool trigger=true;
	if(actsite==10||actsite==12||actsite==20||actsite==22)//���ܴ��� ��һʽ
	{
		actPlayer->m_CurMove=52;
		actPlayer->m_vx=6;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��1");
	}
	else if(actPlayer->m_Tag==52&&actPlayer->m_LF<180&&(actsite%10==0||actsite%10==2||(actsite%10==3&&actPlayer->m_CurMove==52)))//�����ڶ�ʽ
	{
		actPlayer->m_CurMove=53;
		actPlayer->m_vx=6;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��2");
	}
	else if(actPlayer->m_Tag==53&&actPlayer->m_LF<180&&(actsite%10==0||actsite%10==2||(actsite%10==3&&actPlayer->m_CurMove==53)))//��������ʽ
	{
		actPlayer->m_CurMove=54;
		actPlayer->m_vx=6;
		actPlayer->m_vy=-8;
		actPlayer->m_Tag=0;
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��3");
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
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��ȭ");
	}
	return trigger;
}

//���ܴ�����ĳ������� ��Ҫ���ڵ�������Ķ���
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

//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
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
	if(actPlayer->m_CurMove==52&&defsite/10==1)//����һʽ��
	{
		defPlayer->m_CurMove=27;
		defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?2:-2;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_CurHCF=1000;
	}
	if(actPlayer->m_CurMove==53&&defsite/10==1)//���ڶ�ʽ��
	{
		defPlayer->m_CurMove=117;
		//defPlayer->m_vx=actPlayer->m_Face==defPlayer->m_Face?2:-2;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_CurHCF=2000;
	}
	if(actPlayer->m_CurMove==54)//������ʽ��Ҫ����
	{
		OutputDebugStringA("�ﵽ��\n");
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
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("���");
	actPlayer->m_TX.push_back(new CTX_TPZ(111,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?50:-50),actPlayer->m_y-80,actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR));
	return false;
}

//�������к�ԶԷ��ĳ������� ����׼ȷ���ƶԷ��Ķ���
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