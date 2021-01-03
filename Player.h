#ifndef _PLAYER_H
#define _PLAYER_H
#define _FACE_RIGHT 1
#define _FACE_LEFT 2
#define _ZD_LAST 1  //循环播放打中目标后消失
#define _ZD_ONCE 2  //只播放一次 打中目标后不消失
#include "Skill.h"
#include "GameEngine.h"
#include "Role.h"
#include "闪烁.h"
#include "TeXiao.h"
#include <list>
class CSkill;
class CRole;
class CTX_SS;
class CTeXiao;
struct Bullet
{
	float _x;
	float _y;
	float _vx;
	float _vy;
	int _CurM;
	int _CurF;
	int _CF;
	int _type;//子弹类型
	int _mirror;//镜像类型
	CSkill * _Sk;//指向的技能 也即对方被打中后用该技能命中处理函数处理

};
struct Keys
{
	unsigned char _U;
	unsigned char _D;
	unsigned char _L;
	unsigned char _R;
	unsigned char _a;
	unsigned char _b;
	unsigned char _x;
	unsigned char _y;
};
class CPlayer
{
public:
	CRole * m_Role;			//所选择的角色的地址
	int m_HP;			//当前血量
	float m_x;				//当前坐标
	float m_y;
	float m_vx;
	int m_Cor;
	float m_vy;
	//当前朝向
	int m_Face;			
	char m_KeyHold[8];
	//动作相关
	int m_CurMove;
	int m_CurF;
	int m_CurCF;
	std::list<Bullet> m_Bullet;
	std::list<CTeXiao*> m_TX;
	//按键
	Keys m_Keys;	//玩家按键规定  上下左右 拳脚	
	unsigned char m_Keyin[7];//当前按键输入
	char m_Kstr[7];//当前的方位和拳脚输入
	int m_KCF;//当前按键输入间隔
	int m_Knum;//当前按键输入个数
	//当前招式
	CSkill * m_CurS;
	//被打中的对方招式
	CSkill * m_HurtS;
	int m_CurSCF;//当前招式持续帧数
	int m_CurHCF;//被攻击持续帧数
	//连招相关
	int m_Tag;	//0 表示非连招状态 其它值表示可连招状态 值为上一招的动作
	int m_LF;		//连招状态开始后持续帧数，每次循环会加1

	CPlayer(Keys ks, int x, int face, int cor);
	//存入按键
	void Push(unsigned char k);
	//获取按键输入
	void GetKeyIn();
	//清空按键输入
	void EmptyKeyIn();
	//将存入的按键转换为方位和拳脚信息的字符串返回
	char* GetKeyStr();//获取输入字符串
	//选择角色
	bool SelectRole(char * name);
	//获取持续按下的按键
	char* GetHoldKey();
	//获取某个按键的状态
	int GetKeyState(char key);

};
#endif