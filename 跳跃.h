#ifndef  _跳跃_H
#define _跳跃_H
#include "Skill.h"
class CS_TY:public CSkill
{
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif