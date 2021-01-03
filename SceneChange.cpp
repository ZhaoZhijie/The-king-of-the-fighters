#include "SceneChange.h"

CSceneChange::CSceneChange(int AllFrame)
{
	m_AllFrame = AllFrame;
	m_CurFrame = 0;
}

CSceneChange::~CSceneChange()
{}

void CSceneChange::Render(int CurFrame)
{}

void CSceneChange::SetBegin()
{
	m_CurFrame = 0;
}