#ifndef _SKILL_H
#define _SKILL_H
#include "Player.h"
#include  "GameEngine.h"
/*
	此类技能属于攻击型技能
*/

class CPlayer;

class CSkill
{
public:
	//技能触发条件判定（是匹配到按键后的判定，距离，双方状态等）
	virtual bool TriggerJudge(CPlayer * actPlayer, CPlayer *defPlayer)=0;
	//触发后控制
	virtual void TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer);
	//技能命中条件判定（是矩形碰撞后的双方状态判断）
	virtual bool HitJudge(CPlayer * actPlayer, CPlayer *defPlayer);
	//技能命中后对被攻击者的持续控制
	virtual void HitControl(CPlayer * actPlayer, CPlayer *defPlayer);
};

#endif