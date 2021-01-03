#include "����.h"
#include "Skill.h"
#include "����.h"
#include "������ʽ.h"   
#include "������.h"
#include "ǰ��.h"
#include "����.h"
#include "վ��.h"
#include "�¶�.h"
#include "��Ծ.h"
#include "����.h"
#include "վ��ȭ.h"
#include "����ȭ.h"
#include "����ȭ.h"
#include "վ�ؽ�.h"
#include "���ؽ�.h"
#include "���ؽ�.h"
#include "վ���.h"
#include "�����.h"
#include "�����.h"
#include "վ��ȭ.h"
#include "����ȭ.h"
#include "����ȭ.h"
#include "��.h"
#include "��С��.h"
#include "����Ů.h"
#include "����.h"
#include "�˾Ʊ�.h"
#include "��.h"
#include "���ۺ�.h"
#include "Ͷ��.h"
#include "м��.h"
void CR_Iori::Init()
{
	InitBasic();
	InitMoves();
	InitSkill();
	InitSound();
}
//��ʼ��Ѫ�����ٶȣ������ȳ�ʼ��Ϣ
void CR_Iori::InitBasic()
{
	m_HP=1000;
	m_Speed=4;
	m_RunSpeed=7;
	m_vy=-12;
	SkillCode code[29]={
		{"DFBx","����Ů"},
		{"DBFx","м��"},
		{"DFDFx","�˾Ʊ�"},
		{"DFDFx","����"},
		{"DFBa","��"},
		{"BDFx","������"},
		{"DFx","����"},
		{"DBx","������ʽ"},
		{"FF","����"},
		{"BB","��С��"},
		{"x","Ͷ��"},
		{"x","վ��ȭ"},
		{"x","����ȭ"},
		{"x","����ȭ"},
		{"y","վ��ȭ"},
		{"y","����ȭ"},
		{"y","����ȭ"},
		{"a","վ�ؽ�"},
		{"a","���ؽ�"},
		{"a","���ؽ�"},
		{"b","վ���"},
		{"b","�����"},
		{"b","���ۺ�"},
		{"b","�����"},
		{"","��"},
		{"","ǰ��"},
		{"","����"},
		{"","�¶�"},
		{"","��Ծ"}
	};
	for(int i=0;i<29;i++)
	{
		m_Code[i]=code[i];
	}
	m_Len=29;
}
//��ʼ������ ���ý�ɫ��صĶ������ص�����
void CR_Iori::InitMoves()
{
	//����ê����Ϣ
	FILE * fp=fopen("pic//IORI//iori.txt","r");
	int zno, pno, px, py;
	int size=1128;
	char buff[100];
	char picpath[30];
	char picno[30];
	wchar_t wpath[30];
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<4;j++)
			fgets(buff,50,fp);
		fgets(buff,50,fp);
		Pic[i][0]=atoi(buff);
		fgets(buff,50,fp);
		Pic[i][1]=atoi(buff);
		fgets(buff,50,fp);
		Pic[i][2]=atoi(buff);
		fgets(buff,50,fp);
		Pic[i][3]=atoi(buff);
		sprintf(picpath,"pic//IORI//iori-%04d.bmp",i);
		sprintf(picno,"%04d",i);
		wsprintfW(wpath,L"pic//IORI//iori-%04d.bmp",i);
		Image img(wpath);
		Pic[i][4]=img.GetWidth();
		Pic[i][5]=img.GetHeight();
		CGameEngine::GetGE()->GetGO()->LoadImg(picno, wpath);
	}
	fclose(fp);
	char dbug[50];
	//���ض���֡�;���
	FILE * fpair=fopen("pic//IORI//iori.rect","r");
	CGameEngine::GetGE()->GetMoves()->AddFrame(0,"0001",0,0,10,10,1,0,0);
	int k=1;//���صڼ�������
	int f=-1;
	char dem[]=",";
	int cno=0;
	bool tag=false;
	while(!feof(fpair))
	{
		fgets(buff,100,fpair);
		switch(buff[0])
		{
		case 'P':
			{
				int z=atoi(strtok(&buff[2],dem));
				int p=atoi(strtok(NULL,dem));
				int pos=FindPic(z,p);
				int mx=atoi(strtok(NULL,dem));
				int my=atoi(strtok(NULL,dem));
				int c=atoi(strtok(NULL,dem));
				int site=atoi(strtok(NULL,dem));
				char *pname=new char[40];
				sprintf(pname,"%04d",pos);
				CGameEngine::GetGE()->GetMoves()->AddFrame(k,pname,0,0,Pic[pos][4],Pic[pos][5],c,Pic[pos][2],Pic[pos][3],mx,my,site);
				f++;
				break;
			}
		case 'R':
			{
				int left=atoi(strtok(&buff[3],dem));
				int top=atoi(strtok(NULL,dem));
				int right=atoi(strtok(NULL,dem));
				int bottom=atoi(strtok(NULL,dem));
				if(buff[1]=='A')
					CGameEngine::GetGE()->GetMoves()->AddActRect(k,f,left,top,right,bottom);
				else
					CGameEngine::GetGE()->GetMoves()->AddDefRect(k,f,left,top,right,bottom);
				break;
			}
		case 'O':
			{
				k++;
				f=-1;
				break;
			}
		}
	}

	for(int v=0;v<k;v++)
		CGameEngine::GetGE()->GetMoves()->SetNextMove(v, v);

	CGameEngine::GetGE()->GetMoves()->SetNextMove(26, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(27, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(29, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(30, 1);

	for(int p=6;p<20;p++)
	{
		CGameEngine::GetGE()->GetMoves()->SetNextMove(p, 1);
	}
	for(int q=12;q<16;q++)
	{
		CGameEngine::GetGE()->GetMoves()->SetNextMove(q, 4);
	}
	sprintf(dbug,"ͼƬ˳���%d\n",FindPic(2200,1));
	OutputDebugStringA(dbug);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(74, 77);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(77, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(75, 78);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(78, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(76, 39);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(39, 43);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(43, 45);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(57, 4);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(5, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(67, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(58, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(59, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(52, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(53, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(54, 55);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(55, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(56, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(7, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(61, 62);	
	CGameEngine::GetGE()->GetMoves()->SetNextMove(62, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(80, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(32, 35);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(33, 35);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(35, 4);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(28, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(75, 78);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(77, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(81, 43);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(45, 82);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(82, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(83, 84);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(84, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(86, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(87, 65);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(65, 1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(69,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(89,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(91,92);//��շ�
	CGameEngine::GetGE()->GetMoves()->SetNextMove(92,93);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(93,94);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(94,84);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(101,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(41,91);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(103,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(104,84);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(51,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(24,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(25,4);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(20,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(114,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(115,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(116,1);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(117,43);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(118,82);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(119,82);
	CGameEngine::GetGE()->GetMoves()->SetNextMove(120,39);
	//CGameEngine::GetGE()->GetMoves()->SetNextMove(94,1);
	//CGameEngine::GetGE()->GetMoves()->SetNextMove(70,1);
	fclose(fpair);
}
//��ʼ�����ܣ������ܼ��ص�����  Ҳ�����ѡ����ĳ����ɫ�󽫸ý�ɫ�ļ��ܼ��ص�����
void CR_Iori::InitSkill()
{
	CGameEngine::GetGE()->LoadSkill("����",new CS_GS);
	CGameEngine::GetGE()->LoadSkill("������ʽ",new CS_KH);
	CGameEngine::GetGE()->LoadSkill("������",new CS_AGS);
	CGameEngine::GetGE()->LoadSkill("ǰ��",new CS_QX);
	CGameEngine::GetGE()->LoadSkill("����",new CS_HT);
	CGameEngine::GetGE()->LoadSkill("�¶�",new CS_XD);
	CGameEngine::GetGE()->LoadSkill("��Ծ",new CS_TY);
	CGameEngine::GetGE()->LoadSkill("����",new CS_BP);
	CGameEngine::GetGE()->LoadSkill("վ��ȭ",new CS_ZZQ);
	CGameEngine::GetGE()->LoadSkill("����ȭ",new CS_DZQ);
	CGameEngine::GetGE()->LoadSkill("����ȭ",new CS_TZQ);
	CGameEngine::GetGE()->LoadSkill("վ�ؽ�",new CS_ZZJ);
	CGameEngine::GetGE()->LoadSkill("���ؽ�",new CS_DZJ);
	CGameEngine::GetGE()->LoadSkill("���ؽ�",new CS_TZJ);
	CGameEngine::GetGE()->LoadSkill("վ���",new CS_ZQJ);
	CGameEngine::GetGE()->LoadSkill("�����",new CS_DQJ);
	CGameEngine::GetGE()->LoadSkill("�����",new CS_TQJ);
	CGameEngine::GetGE()->LoadSkill("վ��ȭ",new CS_ZQQ);
	CGameEngine::GetGE()->LoadSkill("����ȭ",new CS_DQQ);
	CGameEngine::GetGE()->LoadSkill("����ȭ",new CS_TQQ);
	CGameEngine::GetGE()->LoadSkill("��",new CS_GD);
	CGameEngine::GetGE()->LoadSkill("��С��",new CS_HXT);
	CGameEngine::GetGE()->LoadSkill("����Ů",new CS_BZN);
	CGameEngine::GetGE()->LoadSkill("����",new CS_AX);
	CGameEngine::GetGE()->LoadSkill("�˾Ʊ�",new CS_BJB);
	CGameEngine::GetGE()->LoadSkill("��",new CS_SJ);
	CGameEngine::GetGE()->LoadSkill("���ۺ�",new CS_BZH);
	CGameEngine::GetGE()->LoadSkill("Ͷ��",new CS_TJ);
	CGameEngine::GetGE()->LoadSkill("м��",new CS_XF);
}

void CR_Iori::InitSound()
{
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("Ͷ��","��������//iroi-0000.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("���","��������//iroi-0002.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�ػ�","��������//iroi-0003.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("צ��","��������//iroi-0004.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��ȭ","��������//iroi-0014.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�ܲ�","��������//iroi-0020.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0031.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��","��������//iroi-0032.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��","��������//iroi-0036.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ѽ","��������//iroi-0037.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�����","��������//iroi-0038.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0044.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��1","��������//iroi-0047.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��2","��������//iroi-0048.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��3","��������//iroi-0049.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ϵ��","��������//iroi-0055.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0059.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����2","��������//iroi-0064.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0076.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0078.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ը��","��������//iroi-0080.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ը��2","��������//iroi-0092.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ը��3","��������//iroi-0092.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("����","��������//iroi-0105.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("ը��4","��������//iroi-0142.wav");
}

int CR_Iori::FindPic(int zno, int pno)
{
	for(int i=0;i<1128;i++)
	{
		if(Pic[i][0]==zno&&Pic[i][1]==pno)
		{
			return i;
		}
	}
	return -1;
}