#include "Role.h"
//����������ҵ�״̬�жϹ����ߵĳ��� �жϲ�ֻ�����ݰ������뻹Ҫ������Ѫ���ȸ�����Ϣ
CSkill * CRole::SearchSkill(CPlayer* actp, CPlayer* defp)
{
	//��ƥ�乥���ߵİ������룬�ڸ��ݼ���Ҫ���ж����弼��
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