#ifndef  _վ���_H
#define _վ���_H
#include "Skill.h"
class CS_ZQJ:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//���ܴ�����ĳ�������
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//���������ж�
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif