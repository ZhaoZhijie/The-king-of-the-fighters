#include "ΥπΖΑ.h"

CTX_ZP::CTX_ZP(int len)
{
	m_Len=len;
}

bool CTX_ZP::Run(float vir_x,float *py)
{
	if(m_Len<0)
	{
		*py=0;
		return false;
	}
	if(m_Len%3==0)
		*py=2;
	else if(m_CurF%3==1)
		*py=0;
	else
		*py=-2;
	m_Len--;
	return true;
}