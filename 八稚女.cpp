#include "����Ů.h"
#include "ͼƬ֡.h"
#include "��֡��.h"
#include "��Ӱ.h"
#include "��Ӱ.h"
#include "����.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_BZN::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actsite==10||actsite==12||actsite==20||actsite==22)//���ܴ���
	{
		actPlayer->m_CurMove=87;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->EmptyKeyIn();
		actPlayer->m_TX.push_back(new CTX_TPZ(88,actPlayer->m_x,actPlayer->m_y-127));
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");	
		return true;
	}
	return false;
}

//���ܴ�����ĳ�������
void CS_BZN::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->m_CurSCF==10)
		actPlayer->m_TX.push_back(new CTX_BZL(10,3));	
	if(actPlayer->m_CurMove==87||actPlayer->m_CurMove==65)
	{
		if(actPlayer->m_CurSCF>47&&actPlayer->m_CurSCF<52)
		{
			actPlayer->m_vx+=(5.5+_F);
		}
		if(actPlayer->m_CurMove==41)
		{
			actPlayer->m_TX.push_back(new CTX_HY(actPlayer,50));		
		}
		if(actPlayer->m_CurSCF>=52&&actPlayer->m_CurSCF<74)
		{
			actPlayer->m_vx=22;
		}
		if(actPlayer->m_CurSCF==52)
		{
			actPlayer->m_TX.push_back(new CTX_HY(actPlayer,50));	
		}
		if(actPlayer->m_CurSCF>=74&&actPlayer->m_vx>0)
		{
			actPlayer->m_vx+=(_F-0.5);
			if(actPlayer->m_vx<0)
				actPlayer->m_vx=0;
		}
	}else
		actPlayer->m_vx=0;
	actPlayer->m_CurSCF++;
}

//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
bool CS_BZN::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,defPlayer->m_CurF);
	if(defsite==12||defsite==22||defsite==14||defsite%10==9)//14���ڵ��Ϲ���
		return false;
	//��Ч
	int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
	defPlayer->m_TX.push_back(new CTX_TPZ(99,defPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?-30:30),defPlayer->m_y-50,m));
	//��Ч
	CGameEngine::GetGE()->GetAM()->PlayOnceAudio("צ��");	
	if(actPlayer->m_CurMove==87)
	{
		actPlayer->m_CurMove=69;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_vx=0;
		defPlayer->m_CurMove=75;
		defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?45:-45);
		defPlayer->m_y=actPlayer->m_y;
		defPlayer->m_vx=0;
		defPlayer->m_vy=0;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_CurS=NULL;
		defPlayer->m_HurtS=this;
		defPlayer->m_CurHCF=0;
	}else
	{
			char buff[50];
			sprintf(buff,"��%d֡�Ĺ���\n",defPlayer->m_CurHCF);
			//OutputDebugStringA(buff);
		defPlayer->m_CurMove=75;
		defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?45:-45);
		if(defPlayer->m_CurHCF==60)
		{
			defPlayer->m_CurMove=74;
			defPlayer->m_x=actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?30:-30);
		}
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
	}
	return true;
}

//�������к�˫������ô��
void CS_BZN::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(defPlayer->m_CurHCF==163)
	{//����Ч
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		actPlayer->m_TX.push_back(new CTX_TPZ(97,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-50,m));	
		defPlayer->m_TX.push_back(new CTX_SS(18,defPlayer));
		actPlayer->m_TX.push_back(new CTX_ZP(18));
	}
	if(defPlayer->m_CurHCF>=163&&actPlayer->m_CurS==this)
	{
		defPlayer->m_vx=defPlayer->m_Face==actPlayer->m_Face?7:-7;
		defPlayer->m_vy=-8;
		defPlayer->m_CurMove=39;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;	
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("ը��4");	
		actPlayer->m_CurS=NULL;
		defPlayer->m_HurtS=NULL;	
	}
	else
	{
		if(defPlayer->m_CurF+1==CGameEngine::GetGE()->GetMoves()->GetFrameLen(defPlayer->m_CurMove)
			&&defPlayer->m_CurCF+1==CGameEngine::GetGE()->GetMoves()->GetContinueFrame(defPlayer->m_CurMove,defPlayer->m_CurF))
			defPlayer->m_CurCF--;
	}
	defPlayer->m_CurHCF++;
	return;
}