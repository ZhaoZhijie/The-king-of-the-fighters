#ifndef  _��С��_H
#define _��С��_H
#include "Skill.h"
class CS_HXT:public CSkill
{
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif