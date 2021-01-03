#include "Role.h"
//根据两个玩家的状态判断攻击者的出招 判断不只是依据按键输入还要看距离血量等各种信息
CSkill * CRole::SearchSkill(CPlayer* actp, CPlayer* defp)
{
	//先匹配攻击者的按键输入，在根据技能要求判定具体技能
	char * skillstr=actp->GetKeyStr();
	for(int i=0;i<m_Len;i++)
	{
		if(strstr(skillstr,m_Code[i]._Key))
		{
			CSkill* tmpSkill=CGameEngine::GetGE()->GetSkill(m_Code[i]._SkillName);
			if(tmpSkill->TriggerJudge(actp,defp))
			{
				return tmpSkill;
			}
		}
	}
	return NULL;
}