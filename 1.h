#ifndef Scene_1_H_
#define Scene_1_H_

#include "Scene.h"
#include "SceneChange.h"
class C1 : public CScene
{
private:
	int m_CF;
	int m_V;
	float m_Alpha;
public:
	void Init();
	void OutputRun();		//����
	void LogicInputRun();	//������߼�
	void Enter();			//��Ч��
	void Quit();			//��Ч��
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
};

#endif