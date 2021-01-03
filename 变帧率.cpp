#include "±äÖ¡ÂÊ.h"
#include "GameEngine.h"

CTX_BZL::CTX_BZL(int cf, float fd)
{
	m_CF=cf;
	m_R=fd;
}

bool CTX_BZL::Run(float vir_x,float *py)
{
	if(m_CF-->0)
	{
		CGameEngine::GetGE()->SetSleepTime(m_R);
		return true;
	}
	CGameEngine::GetGE()->ResetSleepTime();
	return false;
}