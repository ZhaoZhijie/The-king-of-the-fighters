#ifndef  _վ��_H
#define _վ��_H
#include "Skill.h"
class CS_ZL:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif