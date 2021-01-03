#include "1.h"
#include "GameEngine.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Scene.h"
#include "SceneChange.h"


void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadImg("��־", L"pic\\back\\��־.bmp");
	CGameEngine::GetGE()->GetGO()->LoadImg("��ɫ", L"pic\\back\\��ɫ.bmp");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("����","sound\\kof97����.mp3");
	m_V=100;
	m_CF=0;
	m_Alpha=0;
	//SetQuitChange("��1");
}

void C1::OutputRun()
{
	if(m_CF==30)
		CGameEngine::GetGE()->GetAM()->PlayLoopAudio("����");
	if(m_CF>200&&m_CF%2==0)
	{
		CGameEngine::GetGE()->GetAM()->SetLoopVolume(m_V--);
		m_Alpha+=0.01;
		if(m_Alpha>0.99)
		{
			CGameEngine::GetGE()->SetCurScene("˵������");
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("����");
			return;
		}
	}
	CGameEngine::GetGE()->GetGO()->DrawImg("��־",0,0,640,480,0,0,640,480);
	CGameEngine::GetGE()->GetGO()->DrawRole("��ɫ", 0,0,_MIRROR_NONE,_COR_RED,m_Alpha);
	m_CF++;
}

void C1::LogicInputRun()
{

}

void C1::Enter()
{
	//CGameEngine::GetGE()->SetEnterChange("��1");
}
void C1::Quit()
{
	//CGameEngine::GetGE()->SetQuitChange("��1");
}
