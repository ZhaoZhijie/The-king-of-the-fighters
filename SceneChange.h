#ifndef _SCENE_CHANGE_H_
#define _SCENE_CHANGE_H_

class CSceneChange
{
	//friend ��Ԫ
	/*
	�˴��� CGameEngine �� ����Ϊ�� ��Ԫ
	��ô CSceneChange ��˽�г�Ա ��
	���Ա� CGameEngine ������
	*/
	friend class CGameEngine;
	int m_AllFrame;	//��֡��
	int m_CurFrame;	//��ǰ֡��
public:
	CSceneChange(int AllFrame);
	virtual ~CSceneChange();
	virtual void Render(int CurFrame);

	void SetBegin();
};

#endif