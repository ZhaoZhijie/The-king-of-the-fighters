#include "Scene.h"


CScene::~CScene()
{}

void CScene::Init()
{}
void  CScene::Enter()//���볡��
{}	
//void  CScene::Run()
//{}
void CScene::OutputRun(){}		//����
void CScene::LogicInputRun(){}	//������߼�
void  CScene::Quit()//�����˳�
{}	
void  CScene::End()//����
{}

void CScene::SetQuitChange(std::string QuitChange)
{
	m_QuitChange = QuitChange;
}
void CScene::SetEnterChange(std::string EnterChange)
{
	m_EnterChange = EnterChange;
}