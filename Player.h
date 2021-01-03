#ifndef _PLAYER_H
#define _PLAYER_H
#define _FACE_RIGHT 1
#define _FACE_LEFT 2
#define _ZD_LAST 1  //ѭ�����Ŵ���Ŀ�����ʧ
#define _ZD_ONCE 2  //ֻ����һ�� ����Ŀ�����ʧ
#include "Skill.h"
#include "GameEngine.h"
#include "Role.h"
#include "��˸.h"
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
	int _type;//�ӵ�����
	int _mirror;//��������
	CSkill * _Sk;//ָ��ļ��� Ҳ���Է������к��øü������д���������

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
	CRole * m_Role;			//��ѡ��Ľ�ɫ�ĵ�ַ
	int m_HP;			//��ǰѪ��
	float m_x;				//��ǰ����
	float m_y;
	float m_vx;
	int m_Cor;
	float m_vy;
	//��ǰ����
	int m_Face;			
	char m_KeyHold[8];
	//�������
	int m_CurMove;
	int m_CurF;
	int m_CurCF;
	std::list<Bullet> m_Bullet;
	std::list<CTeXiao*> m_TX;
	//����
	Keys m_Keys;	//��Ұ����涨  �������� ȭ��	
	unsigned char m_Keyin[7];//��ǰ��������
	char m_Kstr[7];//��ǰ�ķ�λ��ȭ������
	int m_KCF;//��ǰ����������
	int m_Knum;//��ǰ�����������
	//��ǰ��ʽ
	CSkill * m_CurS;
	//�����еĶԷ���ʽ
	CSkill * m_HurtS;
	int m_CurSCF;//��ǰ��ʽ����֡��
	int m_CurHCF;//����������֡��
	//�������
	int m_Tag;	//0 ��ʾ������״̬ ����ֵ��ʾ������״̬ ֵΪ��һ�еĶ���
	int m_LF;		//����״̬��ʼ�����֡����ÿ��ѭ�����1

	CPlayer(Keys ks, int x, int face, int cor);
	//���밴��
	void Push(unsigned char k);
	//��ȡ��������
	void GetKeyIn();
	//��հ�������
	void EmptyKeyIn();
	//������İ���ת��Ϊ��λ��ȭ����Ϣ���ַ�������
	char* GetKeyStr();//��ȡ�����ַ���
	//ѡ���ɫ
	bool SelectRole(char * name);
	//��ȡ�������µİ���
	char* GetHoldKey();
	//��ȡĳ��������״̬
	int GetKeyState(char key);

};
#endif