#ifndef ENTER_1_H
#define ENTER_1_H

#include "SceneChange.h"

class CEnter1 : public CSceneChange
{
	int w, h;
public:
	CEnter1();
	void Render(int CurFrame);
};

#endif