#ifndef  _���ؽ�_H
#define _���ؽ�_H
#include "Skill.h"
class CS_TZJ:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ�����ĳ�������
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//���������ж�
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif