#ifndef _����_H
#define _����_H
#include "TeXiao.h"

class CTX_ZP:public CTeXiao
{
private:
	int m_CurF;//��ǰ֡��
	int m_Len;
public:
	//���ճ������ӿ����Ͻ������ַ
	CTX_ZP(int len);
	//��Ч������Ϻ󷵻�false����֪����ɾ������Ч
	bool Run(float vir_x,float *py);
};

#endif