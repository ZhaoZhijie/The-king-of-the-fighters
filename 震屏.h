#ifndef _震屏_H
#define _震屏_H
#include "TeXiao.h"

class CTX_ZP:public CTeXiao
{
private:
	int m_CurF;//当前帧数
	int m_Len;
public:
	//接收场景的视口左上角坐标地址
	CTX_ZP(int len);
	//特效播放完毕后返回false，告知场景删除此特效
	bool Run(float vir_x,float *py);
};

#endif