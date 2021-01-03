#ifndef  _站立_H
#define _站立_H
#include "Skill.h"
class CS_ZL:public CSkill
{
	//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif