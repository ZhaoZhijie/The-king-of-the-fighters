#ifndef  _������ʽ_H
#define _������ʽ_H
#include "Skill.h"
class CS_KH:public CSkill
{
	//���ܴ��������ж�����ƥ�䵽��������ж������룬˫��״̬�ȣ�
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);

	//���ܴ�����ĳ�������
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);

	//�������������ж����Ǿ�����ײ���˫��״̬�жϣ�
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);

	//�������к�˫������ô��
	void HitControl(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif