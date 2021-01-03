#include "Player.h"
#define _DEC 30
CPlayer::CPlayer(Keys ks, int x, int face, int cor)
{
	m_CurMove=1;
	m_CurF=0;
	m_CurCF=0;
	m_CurS=NULL;
	m_HurtS=NULL;
	m_Tag=0;
	m_LF=0;
	memset(m_KeyHold, 0, 8);
	m_Bullet.clear();
	m_TX.clear();
	m_Keys=ks;
	m_x=x;
	m_y=400;
	m_vx=0;
	m_vy=0;
	m_Face=face;
	m_Cor=cor;
	m_Knum=0;
	m_KCF=0;
}

void CPlayer::Push(unsigned char k)
{
	m_KCF=0;
	m_Keyin[m_Knum++]=k;
	if(m_Knum==7)
	{
		for(int i=1;i<=6;i++)
		{
			m_Keyin[i-1]=m_Keyin[i];
		}
		m_Keyin[6]=0;
		m_Knum=6;
	}
}

void CPlayer::GetKeyIn()
{
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._U)==_KS_DC)
		Push(m_Keys._U);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._D)==_KS_DC)
		Push(m_Keys._D);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._L)==_KS_DC)
		Push(m_Keys._L);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._R)==_KS_DC)
		Push(m_Keys._R);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._a)==_KS_DC)
		Push(m_Keys._a);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._b)==_KS_DC)
		Push(m_Keys._b);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._x)==_KS_DC)
		Push(m_Keys._x);
	if(CGameEngine::GetGE()->GetGI()->Get(m_Keys._y)==_KS_DC)
		Push(m_Keys._y);
	if(m_KCF++>_DEC)
		EmptyKeyIn();
}

void CPlayer::EmptyKeyIn()
{
	m_Knum=0;
	m_KCF=0;
	memset(m_Keyin,0,7);
}

char*  CPlayer::GetKeyStr()
{
	for(int i=0;i<m_Knum;i++)
	{
		if(m_Keyin[i]==m_Keys._U)
			m_Kstr[i]='U';
		else if(m_Keyin[i]==m_Keys._D)
			m_Kstr[i]='D';
		else if(m_Keyin[i]==m_Keys._L)
		{
			if(m_Face==_FACE_RIGHT)
				m_Kstr[i]='B';
			else
				m_Kstr[i]='F';
		}
		else if(m_Keyin[i]==m_Keys._R)
		{
			if(m_Face==_FACE_RIGHT)
				m_Kstr[i]='F';
			else
				m_Kstr[i]='B';
		}
		else if(m_Keyin[i]==m_Keys._a)
			m_Kstr[i]='a';
		else if(m_Keyin[i]==m_Keys._b)
			m_Kstr[i]='b';
		else if(m_Keyin[i]==m_Keys._x)
			m_Kstr[i]='x';
		else if(m_Keyin[i]==m_Keys._y)
			m_Kstr[i]='y';
	}
	m_Kstr[m_Knum]='\0';
	return m_Kstr;
}


char* CPlayer::GetHoldKey()
{
	memset(m_KeyHold, 0, 8);
	int len=0;
	if(GetKeyState('U') == _KS_DH)
		m_KeyHold[len++]='U';
	if(GetKeyState('D') == _KS_DH)
		m_KeyHold[len++]='D';
	if(GetKeyState('F') == _KS_DH)
			m_KeyHold[len++]='F';
	if(GetKeyState('B') == _KS_DH)
			m_KeyHold[len++]='B';
	m_KeyHold[len]='\0';
	return m_KeyHold;
}

bool CPlayer::SelectRole(char * name)
{
	return m_Role=CGameEngine::GetGE()->GetRole(name);
}

int CPlayer::GetKeyState(char key)
{
	switch(key)
	{
	case 'F':
		{
			if(m_Face==_FACE_RIGHT)
				return CGameEngine::GetGE()->GetGI()->Get(m_Keys._R);
			else
				return CGameEngine::GetGE()->GetGI()->Get(m_Keys._L);
		}
	case 'B':
		{
			if(m_Face==_FACE_RIGHT)
				return CGameEngine::GetGE()->GetGI()->Get(m_Keys._L);
			else
				return CGameEngine::GetGE()->GetGI()->Get(m_Keys._R);
		}
	case 'U':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._U);
	case 'D':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._D);		
	case 'a':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._a);		
	case 'b':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._b);		
	case 'x':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._x);		
	case 'y':
		return CGameEngine::GetGE()->GetGI()->Get(m_Keys._y);		
	}
}