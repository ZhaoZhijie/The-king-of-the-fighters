#ifndef  _����ȭ_H
#define _����ȭ_H
#include "Skill.h"
class CS_DQQ:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ�����ĳ�������
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//���������ж�
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif