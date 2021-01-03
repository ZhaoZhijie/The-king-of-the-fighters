#ifndef _八神_H
#define _八神_H
#include "Role.h"
class CR_Iori:public CRole
{
private:
	int Pic[1128][6];
	//初始化血量，速度，按键等初始信息
	void InitBasic();
	//初始化动作 将该角色相关的动作加载到引擎
	void InitMoves();
	//初始化技能，将技能加载到场景  也即玩家选择了某个角色后将该角色的技能加载到引擎
	void InitSkill();
	//初始化声音
	void InitSound();
	int FindPic(int zno, int pno);
public:
	//初始化
	void Init();
};

#endif