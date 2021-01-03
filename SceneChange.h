#ifndef _SCENE_CHANGE_H_
#define _SCENE_CHANGE_H_

class CSceneChange
{
	//friend 友元
	/*
	此处把 CGameEngine 类 设置为了 友元
	那么 CSceneChange 的私有成员 就
	可以被 CGameEngine 访问了
	*/
	friend class CGameEngine;
	int m_AllFrame;	//总帧数
	int m_CurFrame;	//当前帧数
public:
	CSceneChange(int AllFrame);
	virtual ~CSceneChange();
	virtual void Render(int CurFrame);

	void SetBegin();
};

#endif