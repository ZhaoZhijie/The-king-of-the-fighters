#ifndef  _��֡��_H
#define _��֡��_H
#include "TeXiao.h"
#include "Player.h"
/*
	��ʱ������ �������Чͬʱ���ڻ������
*/

class CPlayer;
class CTX_BZL:public CTeXiao
{
private:
	int m_CF;//Ч������ʱ��
	float m_R;//�ı����   
public:
	CTX_BZL(int cf, float fd);
	bool Run(float vir_x,float *py);
};

#endif