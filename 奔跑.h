#ifndef  _����_H
#define _����_H
#include "Skill.h"
class CS_BP:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ�����ĳ�������
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif