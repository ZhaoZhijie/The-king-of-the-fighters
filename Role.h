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
	int m_HP;//��ʼѪ��
	int m_Speed;//�����ٶ�
	int m_RunSpeed;//�ܶ��ٶ�
	int m_vy;//��Ծ���ٶ�
	SkillCode m_Code[50];//���а���
	int m_Len;//��ʽ����
public:
	virtual void Init()=0;
	//�����ж� ƥ��ɹ����ؼ��ܵĵ�ַ
	CSkill * SearchSkill(CPlayer* actp, CPlayer* defp);

};
#endif