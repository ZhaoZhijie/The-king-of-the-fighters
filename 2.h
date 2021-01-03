#ifndef Scene_2_H_
#define Scene_2_H_

#include "Scene.h"
#include "SceneChange.h"
class C2 : public CScene
{
public:
	void Init();
	void OutputRun();		//绘制
	void LogicInputRun();	//输入和逻辑
	void Enter();			//入效果
	void Quit();			//出效果
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
};

#endif