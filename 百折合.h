#ifndef  _百折合_H
#define _百折合_H
#include "Skill.h"
class CS_BZH:public CSkill
{
	//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
	bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer);

	//技能触发后的持续控制
	void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);

	//技能命中条件判定（是矩形碰撞后的双方状态判断）
	bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);

	//技能命中后双方该怎么做
	void HitControl(CPlayer * actPlayer, CPlayer *defPlayer);
};
#endif