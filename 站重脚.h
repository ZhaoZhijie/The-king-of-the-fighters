#ifndef  _站重脚_H
#define _站重脚_H
#include "Skill.h"
class CS_ZZJ:public CSkill
{
	//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//技能触发后的持续控制
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//技能命中判定
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif