#include "Enter1.h"
#include "GameEngine.h"


CEnter1::CEnter1()
:
//此处 帮助父类构造
CSceneChange(32)
{
	w = CGameEngine::GetGE()->GetClientW();
	h = CGameEngine::GetGE()->GetClientH();
}
	
void CEnter1::Render(int CurFrame)
{
	if(CurFrame <= 1)
	{
		CGameEngine::GetGE()->GetGO()->SetDark(0);
	}
	
	CGameEngine::GetGE()->GetGO()->DrawSRectangle(0, 0, w - (w / 32) * CurFrame, h, RGB(0,0,0) , RGB(0,0,0));
}