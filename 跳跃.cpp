#include "��Ծ.h"

//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_TY::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	if((actsite==10||actsite==12)&&actPlayer->GetKeyState('U')==_KS_DC)//���ܴ���
	{
		actPlayer->m_CurMove=5;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		actPlayer->m_CurS=this;
		actPlayer->m_CurSCF=0;
		actPlayer->m_vy=-11;
		return true;
	}
	return false;
}

void CS_TY::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
{
	actPlayer->m_CurSCF++;
	OutputDebugStringA("������\n");
	if(actPlayer->m_y==400&&actPlayer->m_vy==0)
	{
		actPlayer->m_CurMove=CGameEngine::GetGE()->GetMoves()->GetNextMove(actPlayer->m_CurMove);
		actPlayer->m_CurS=NULL;
	}
}