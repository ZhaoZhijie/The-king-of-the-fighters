#include "1.h"
#include "GameEngine.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Scene.h"
#include "SceneChange.h"


void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadImg("标志", L"pic\\back\\标志.bmp");
	CGameEngine::GetGE()->GetGO()->LoadImg("白色", L"pic\\back\\白色.bmp");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("玛丽","sound\\kof97玛丽.mp3");
	m_V=100;
	m_CF=0;
	m_Alpha=0;
	//SetQuitChange("出1");
}

void C1::OutputRun()
{
	if(m_CF==30)
		CGameEngine::GetGE()->GetAM()->PlayLoopAudio("玛丽");
	if(m_CF>200&&m_CF%2==0)
	{
		CGameEngine::GetGE()->GetAM()->SetLoopVolume(m_V--);
		m_Alpha+=0.01;
		if(m_Alpha>0.99)
		{
			CGameEngine::GetGE()->SetCurScene("说明场景");
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("玛丽");
			return;
		}
	}
	CGameEngine::GetGE()->GetGO()->DrawImg("标志",0,0,640,480,0,0,640,480);
	CGameEngine::GetGE()->GetGO()->DrawRole("白色", 0,0,_MIRROR_NONE,_COR_RED,m_Alpha);
	m_CF++;
}

void C1::LogicInputRun()
{

}

void C1::Enter()
{
	//CGameEngine::GetGE()->SetEnterChange("入1");
}
void C1::Quit()
{
	//CGameEngine::GetGE()->SetQuitChange("出1");
}
