#include "Skill.h"

 void CSkill::TriggerControl(CPlayer * actPlayer, CPlayer *defPlayer)
 {
 
 }

//技能命中条件判定（是矩形碰撞后的双方状态判断）
bool CSkill::HitJudge(CPlayer * actPlayer, CPlayer *defPlayer)
{
	return false;
}

//技能命中后双方该怎么做
void CSkill::HitControl(CPlayer * actPlayer, CPlayer *defPlayer)
{}