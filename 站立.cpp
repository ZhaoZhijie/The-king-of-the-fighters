#include "վ��.h"

//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
bool CS_ZL::TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	int actsite=CGameEngine::GetGE()->GetMoves()->GetSite(actPlayer->m_CurMove,actPlayer->m_CurF);
	
	if((actsite==10||actsite==12||actsite==20||actsite==22)&&actPlayer->m_CurMove!=1&&actPlayer->m_CurMove!=79)//���ܴ���
	{
		actPlayer->m_CurMove=1;
		actPlayer->m_CurCF=0;
		actPlayer->m_CurF=0;
		return true;
	}
	return false;
}