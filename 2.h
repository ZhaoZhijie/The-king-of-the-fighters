#ifndef Scene_2_H_
#define Scene_2_H_

#include "Scene.h"
#include "SceneChange.h"
class C2 : public CScene
{
public:
	void Init();
	void OutputRun();		//����
	void LogicInputRun();	//������߼�
	void Enter();			//��Ч��
	void Quit();			//��Ч��
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
};

#endif