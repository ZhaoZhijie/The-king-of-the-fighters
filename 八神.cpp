#include "八神.h"
#include "Skill.h"
#include "鬼烧.h"
#include "葵花三式.h"   
#include "暗勾手.h"
#include "前行.h"
#include "后退.h"
#include "站立.h"
#include "下蹲.h"
#include "跳跃.h"
#include "奔跑.h"
#include "站重拳.h"
#include "蹲重拳.h"
#include "跳重拳.h"
#include "站重脚.h"
#include "蹲重脚.h"
#include "跳重脚.h"
#include "站轻脚.h"
#include "蹲轻脚.h"
#include "跳轻脚.h"
#include "站轻拳.h"
#include "蹲轻拳.h"
#include "跳轻拳.h"
#include "格挡.h"
#include "后小跳.h"
#include "八稚女.h"
#include "暗削.h"
#include "八酒杯.h"
#include "神技.h"
#include "百折合.h"
#include "投技.h"
#include "屑风.h"
void CR_Iori::Init()
{
	InitBasic();
	InitMoves();
	InitSkill();
	InitSound();
}
//初始化血量，速度，按键等初始信息
void CR_Iori::InitBasic()
{
	m_HP=1000;
	m_Speed=4;
	m_RunSpeed=7;
	m_vy=-12;
	SkillCode code[29]={
		{"DFBx","八稚女"},
		{"DBFx","屑风"},
		{"DFDFx","八酒杯"},
		{"DFDFx","暗削"},
		{"DFBa","神技"},
		{"BDFx","暗勾手"},
		{"DFx","鬼烧"},
		{"DBx","葵花三式"},
		{"FF","奔跑"},
		{"BB","后小跳"},
		{"x","投技"},
		{"x","站重拳"},
		{"x","蹲重拳"},
		{"x","跳重拳"},
		{"y","站轻拳"},
		{"y","蹲轻拳"},
		{"y","跳轻拳"},
		{"a","站重脚"},
		{"a","蹲重脚"},
		{"a","跳重脚"},
		{"b","站轻脚"},
		{"b","蹲轻脚"},
		{"b","百折合"},
		{"b","跳轻脚"},
		{"","格挡"},
		{"","前行"},
		{"","后退"},
		{"","下蹲"},
		{"","跳跃"}
	};
	for(int i=0;i<29;i++)
	{
		m_Code[i]=code[i];
	}
	m_Len=29;
}
//初始化动作 将该角色相关的动作加载到引擎
void CR_Iori::InitMoves()
{
	//加载锚点信息
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
	//加载动作帧和矩形
	FILE * fpair=fopen("pic//IORI//iori.rect","r");
	CGameEngine::GetGE()->GetMoves()->AddFrame(0,"0001",0,0,10,10,1,0,0);
	int k=1;//加载第几个动作
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
	sprintf(dbug,"图片顺序号%d\n",FindPic(2200,1));
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
	CGameEngine::GetGE()->GetMoves()->SetNextMove(91,92);//后空翻
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
//初始化技能，将技能加载到场景  也即玩家选择了某个角色后将该角色的技能加载到引擎
void CR_Iori::InitSkill()
{
	CGameEngine::GetGE()->LoadSkill("鬼烧",new CS_GS);
	CGameEngine::GetGE()->LoadSkill("葵花三式",new CS_KH);
	CGameEngine::GetGE()->LoadSkill("暗勾手",new CS_AGS);
	CGameEngine::GetGE()->LoadSkill("前行",new CS_QX);
	CGameEngine::GetGE()->LoadSkill("后退",new CS_HT);
	CGameEngine::GetGE()->LoadSkill("下蹲",new CS_XD);
	CGameEngine::GetGE()->LoadSkill("跳跃",new CS_TY);
	CGameEngine::GetGE()->LoadSkill("奔跑",new CS_BP);
	CGameEngine::GetGE()->LoadSkill("站重拳",new CS_ZZQ);
	CGameEngine::GetGE()->LoadSkill("蹲重拳",new CS_DZQ);
	CGameEngine::GetGE()->LoadSkill("跳重拳",new CS_TZQ);
	CGameEngine::GetGE()->LoadSkill("站重脚",new CS_ZZJ);
	CGameEngine::GetGE()->LoadSkill("蹲重脚",new CS_DZJ);
	CGameEngine::GetGE()->LoadSkill("跳重脚",new CS_TZJ);
	CGameEngine::GetGE()->LoadSkill("站轻脚",new CS_ZQJ);
	CGameEngine::GetGE()->LoadSkill("蹲轻脚",new CS_DQJ);
	CGameEngine::GetGE()->LoadSkill("跳轻脚",new CS_TQJ);
	CGameEngine::GetGE()->LoadSkill("站轻拳",new CS_ZQQ);
	CGameEngine::GetGE()->LoadSkill("蹲轻拳",new CS_DQQ);
	CGameEngine::GetGE()->LoadSkill("跳轻拳",new CS_TQQ);
	CGameEngine::GetGE()->LoadSkill("格挡",new CS_GD);
	CGameEngine::GetGE()->LoadSkill("后小跳",new CS_HXT);
	CGameEngine::GetGE()->LoadSkill("八稚女",new CS_BZN);
	CGameEngine::GetGE()->LoadSkill("暗削",new CS_AX);
	CGameEngine::GetGE()->LoadSkill("八酒杯",new CS_BJB);
	CGameEngine::GetGE()->LoadSkill("神技",new CS_SJ);
	CGameEngine::GetGE()->LoadSkill("百折合",new CS_BZH);
	CGameEngine::GetGE()->LoadSkill("投技",new CS_TJ);
	CGameEngine::GetGE()->LoadSkill("屑风",new CS_XF);
}

void CR_Iori::InitSound()
{
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("投技","八神声音//iroi-0000.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("绊脚","八神声音//iroi-0002.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("重击","八神声音//iroi-0003.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("爪击","八神声音//iroi-0004.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("轻拳","八神声音//iroi-0014.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("跑步","八神声音//iroi-0020.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("风声","八神声音//iroi-0031.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("哼","八神声音//iroi-0032.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("哈","八神声音//iroi-0036.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("呀","八神声音//iroi-0037.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("下马哥","八神声音//iroi-0038.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("鬼烧","八神声音//iroi-0044.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("葵1","八神声音//iroi-0047.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("葵2","八神声音//iroi-0048.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("葵3","八神声音//iroi-0049.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("系列","八神声音//iroi-0055.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("挣狞","八神声音//iroi-0059.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("挣狞2","八神声音//iroi-0064.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("绝招","八神声音//iroi-0076.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("发标","八神声音//iroi-0078.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("炸裂","八神声音//iroi-0080.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("炸裂2","八神声音//iroi-0092.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("炸裂3","八神声音//iroi-0092.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("嗡嗡","八神声音//iroi-0105.wav");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("炸裂4","八神声音//iroi-0142.wav");
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