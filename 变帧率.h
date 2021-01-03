#ifndef  _变帧率_H
#define _变帧率_H
#include "TeXiao.h"
#include "Player.h"
/*
	暂时测试用 多个此特效同时存在会出问题
*/

class CPlayer;
class CTX_BZL:public CTeXiao
{
private:
	int m_CF;//效果持续时间
	float m_R;//改变幅度   
public:
	CTX_BZL(int cf, float fd);
	bool Run(float vir_x,float *py);
};

#endif