#ifndef _ROLE_H
#define _ROLE_H
#include "Skill.h"
#include "Player.h"
class CSkill;
class CPlayer;
struct SkillCode{
	char _Key[20];
	char _SkillName[20];
};
class CRole
{
protected:
	int m_HP;//初始血量
	int m_Speed;//行走速度
	int m_RunSpeed;//跑动速度
	int m_vy;//跳跃初速度
	SkillCode m_Code[50];//出招按键
	int m_Len;//招式长度
public:
	virtual void Init()=0;
	//技能判定 匹配成功返回技能的地址
	CSkill * SearchSkill(CPlayer* actp, CPlayer* defp);

};
#endif