#include "ǰ��.h"

//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_QX::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	
	if((actsite==10||actsite==12)
		&&actPlayer->m_CurMove!=2&&(actPlayer->GetKeyState('F')==_KS_DC||(actPlayer->GetKeyState('F')==_KS_DH))
		&&actPlayer->GetKeyState('D')!=_KS_DH
		&&actPlayer->GetKeyState('D')!=_KS_DC
		&&actPlayer->GetKeyState('B')!=_KS_DH
		&&actPlayer->GetKeyState('B')!=_KS_DC
		&&actPlayer->m_CurMove!=79)//���ܴ���
	{
		actPlayer->m_CurMove=2;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		return true;
	}
	return false;
}

void CS_QX::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	if(actPlayer->GetKeyState('F')==_KS_DH&&actPlayer->m_CurSCF>1)
	{
		actPlayer->m_vx=3;
	}else if(actPlayer->m_CurSCF>1)
	{
		actPlayer->m_CurMove=1;
		actPlayer->m_CurF=0;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurS=NULL;
	}
	actPlayer->m_CurSCF++;
}