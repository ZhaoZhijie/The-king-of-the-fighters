#include "2.h"
#include "GameEngine.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Scene.h"
#include "SceneChange.h"


void C2::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadImg("招式", L"pic\\back\\招式.bmp");
}

void C2::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawRole("招式", 0,0,_MIRROR_NONE,_COR_RED);
}

void C2::LogicInputRun()
{
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_SPACE)==_KS_DC||(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RETURN)==_KS_DC))
		CGameEngine::GetGE()->SetCurScene("战斗场景");
}

void C2::Enter()
{
	//CGameEngine::GetGE()->SetEnterChange("入1");
}
void C2::Quit()
{
	//CGameEngine::GetGE()->SetQuitChange("出1");
}