#include "����.h"
#include "ͼƬ֡.h"
#include "��Ӱ.h"
#include "��˸.h"
#include "��֡��.h"
#include "����.h"
//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_AX::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if(actPlayer->m_CurMove!=89&&actPlayer->m_Tag==69&&actPlayer->m_LF<480&&(actsite%10==0||actsite%10==2||actPlayer->m_CurMove==69))//���ܴ���
	{
		actPlayer->m_CurMove=89;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		//����Ч
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		actPlayer->m_TX.push_back(new CTX_TPZ(88,actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?60:-60),actPlayer->m_y-60,m));	
		actPlayer->m_TX.push_back(new CTX_HY(actPlayer,10));	
		actPlayer->m_TX.push_back(new CTX_BZL(10,5));	
		actPlayer->EmptyKeyIn();
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");	
		return true;
	}
	return false;
}

//���ܴ�����ĳ�������
void CS_AX::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(	actPlayer->m_CurSCF==106)
	{//��ˮ��
		Bullet b={actPlayer->m_x+(actPlayer->m_Face==_FACE_RIGHT?70:-70), 400, 0, 0, 90, 0, 0,_ZD_ONCE,(actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR), this};
		actPlayer->m_Bullet.push_back(b);
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("ը��4");
		actPlayer->m_TX.push_back(new CTX_ZP(20));
	}else if(actPlayer->m_CurSCF==46&&defPlayer->m_HurtS!=this)
	{//û�д��н�������
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=NULL;
	}
	actPlayer->m_CurSCF++;
}

//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
bool CS_AX::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int defsite=CGameEngine::GetGE()->GetMoves()->GetSite(defPlayer->m_CurMove,actPlayer->m_CurF);
	if(defsite==10||defsite==12||defsite==20||defsite==22||defsite==0)//14���ڵ��Ϲ���
		return false;

	if(defPlayer->m_HurtS!=this)
	{//��צ�Ӵ���
		char buff[50];
		sprintf(buff,"��ǰ����%d\n",defPlayer->m_CurMove);
		OutputDebugStringA(buff);
		defPlayer->m_CurS=NULL;
		defPlayer->m_HurtS=this;
		defPlayer->m_CurHCF=0;
		defPlayer->m_vx=0;
		defPlayer->m_vy=0;
	}else if(actPlayer->m_CurSCF>=96&&defPlayer->m_vx==0)
	{//��ˮ��������
		OutputDebugStringA("��ˮ������\n");
		defPlayer->m_CurMove=91;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		defPlayer->m_TX.push_back(new CTX_SS(18,defPlayer));
		defPlayer->m_vx=(actPlayer->m_Face==defPlayer->m_Face?3:-3);
		defPlayer->m_vy=-14;		
	}
	return true;
}

//�������к�ԶԷ��Ķ�������
void CS_AX::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int c=defPlayer->m_CurHCF;
	if(c<60)
	{//��צ����������ʱ���ֵ�ǰ֡����
		defPlayer->m_CurCF--;
		if(defPlayer->m_CurCF<0)
			defPlayer->m_CurCF=0;
		defPlayer->m_vy=0-_G;
	}
	if(c>0&&c<10)
	{
		actPlayer->m_CurCF--;
		if(actPlayer->m_CurCF<0)
			actPlayer->m_CurCF=0;
	}
	if((c>10&&c<30)||(c>40&&c<60))
	{//����������ʱ�����Ϸ��ƶ�����
		defPlayer->m_x+=(actPlayer->m_Face==_FACE_RIGHT?4:-4);
		defPlayer->m_y-=4;
	}
	if(c==10||c==40)
	{//��Ч
		int m=actPlayer->m_Face==_FACE_RIGHT?_MIRROR_NONE:_MIRROR_LR;
		defPlayer->m_TX.push_back(new CTX_TPZ(98,defPlayer->m_x,defPlayer->m_y-70,m));	
		defPlayer->m_TX.push_back(new CTX_SS(18,defPlayer));
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("צ��");	
	}
	if(defPlayer->m_CurHCF==60)
	{//�������ι��������Ϸ��׳�
		OutputDebugStringA("�׳�ȥ\n");
		defPlayer->m_vy=-13;
		defPlayer->m_CurMove=41;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurCF=0;
	}
	//if(defPlayer->m_CurMove==91&&defPlayer->m_CurF==1&&defPlayer->m_y<=380)
	//{
	//	//���vx==5˵����ˮ������
	//	defPlayer->m_CurCF--;
	//	if(defPlayer->m_CurCF<0)
	//		defPlayer->m_CurCF=0;
	//}
	if(defPlayer->m_y==400&&defPlayer->m_vy==0&&defPlayer->m_CurHCF>60)
	{
		OutputDebugStringA("���\n");
		defPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(defPlayer->m_CurMove);
		defPlayer->m_vy=-5;
		defPlayer->m_CurCF=0;
		defPlayer->m_CurF=0;
		actPlayer->m_TX.push_back(new CTX_ZP(20));
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("����");	
		defPlayer->m_HurtS=NULL;
	}
	defPlayer->m_CurHCF++;
	return;
}