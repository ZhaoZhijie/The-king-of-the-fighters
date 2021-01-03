#include "Quit1.h"
#include "GameEngine.h"

CQuit1::CQuit1()
:
CSceneChange(32)
{
	w = CGameEngine::GetGE()->GetClientW();
	h = CGameEngine::GetGE()->GetClientH();
}
void CQuit1::Render(int CurFrame)
{
	if(CurFrame <= 1)
	{
		CGameEngine::GetGE()->GetGO()->SetDark(0);
	}
	
	CGameEngine::GetGE()->GetGO()->DrawSRectangle(0, 0, (w / 32) * CurFrame, h, RGB(0,0,0) , RGB(0,0,0));
}