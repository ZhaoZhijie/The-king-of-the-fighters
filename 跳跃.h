#ifndef  _��Ծ_H
#define _��Ծ_H
#include "Skill.h"
class CS_TY:public CSkill
{
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif