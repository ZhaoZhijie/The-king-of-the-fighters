#include "GameEngine.h"
#include "1.h"
#include "2.h"
#include "3.h"
#include "Enter1.h"
#include "Quit1.h"
#include <windows.h>

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPervInstance,
					  LPSTR lpCmdLine,
					  int nShowCmd)
{
	CGameEngine::GetGE()->Init(640, 480);

	CGameEngine::GetGE()->LoadScene("战斗场景", new C3);
	CGameEngine::GetGE()->LoadScene("开始场景", new C1);
	CGameEngine::GetGE()->LoadScene("说明场景", new C2);
	CGameEngine::GetGE()->LoadSceneChange("入1", new CEnter1);
	CGameEngine::GetGE()->LoadSceneChange("出1", new CQuit1);
	

	CGameEngine::GetGE()->SetInitScene("开始场景");
	
	CGameEngine::GetGE()->Run();

	return 1;
}