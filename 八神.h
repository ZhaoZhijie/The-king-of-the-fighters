#ifndef _����_H
#define _����_H
#include "Role.h"
class CR_Iori:public CRole
{
private:
	int Pic[1128][6];
	//��ʼ��Ѫ�����ٶȣ������ȳ�ʼ��Ϣ
	void InitBasic();
	//��ʼ������ ���ý�ɫ��صĶ������ص�����
	void InitMoves();
	//��ʼ�����ܣ������ܼ��ص�����  Ҳ�����ѡ����ĳ����ɫ�󽫸ý�ɫ�ļ��ܼ��ص�����
	void InitSkill();
	//��ʼ������
	void InitSound();
	int FindPic(int zno, int pno);
public:
	//��ʼ��
	void Init();
};

#endif