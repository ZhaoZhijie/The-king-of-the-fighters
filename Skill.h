#ifndef _SKILL_H
#define _SKILL_H
#include "Player.h"
#include  "GameEngine.h"
/*
	���༼�����ڹ����ͼ���
*/

class CPlayer;

class CSkill
{
public:
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	virtual bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)=0;
	//���������
	virtual void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
	virtual bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//�������к�Ա������ߵĳ�������
	virtual void HitControl(CPlayer * actPlayer, CPlayer *defPlayer);
};

#endif