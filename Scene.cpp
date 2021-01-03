#include "Scene.h"


CScene::~CScene()
{}

void CScene::Init()
{}
void  CScene::Enter()//进入场景
{}	
//void  CScene::Run()
//{}
void CScene::OutputRun(){}		//绘制
void CScene::LogicInputRun(){}	//输入和逻辑
void  CScene::Quit()//场景退出
{}	
void  CScene::End()//结束
{}

void CScene::SetQuitChange(std::string QuitChange)
{
	m_QuitChange = QuitChange;
}
void CScene::SetEnterChange(std::string EnterChange)
{
	m_EnterChange = EnterChange;
}