#include "3.h"
#include "stdio.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "����.h"
#define _SPEED 3
#define _MAP_W 1636
void C3::Init()
{
	m_BackNo=0;
	virX=_MAP_W/2-CGameEngine::GetGE()->GetClientW()/2;
	virY=0;

	for(int a=0;a<8;a++)
	{
		char bid[30];
		wchar_t bpath[30];
		sprintf(bid,"����%d",a);
		wsprintfW(bpath,L"pic\\back\\%d.bmp",a);
		CGameEngine::GetGE()->GetGO()->LoadImg(bid, bpath);
	}

	//���ؽ�ɫ
	CGameEngine::GetGE()->LoadRole("����",new CR_Iori);
	//�������
	Keys ks1={_GI_K_W, _GI_K_S, _GI_K_A, _GI_K_D, _GI_K_J, _GI_K_K, _GI_K_U, _GI_K_I};
	Keys ks2={_GI_K_UP, _GI_K_DOWN, _GI_K_LEFT, _GI_K_RIGHT, _GI_NK_1, _GI_NK_2, _GI_NK_4, _GI_NK_5};
	m_Player[0]=new CPlayer(ks1,_MAP_W/2-CGameEngine::GetGE()->GetClientW()/2+100, _FACE_RIGHT,_COR_GRAY);
	m_Player[1]=new CPlayer(ks2,_MAP_W/2+CGameEngine::GetGE()->GetClientW()/2-100, _FACE_LEFT,_COR_RED);
	//ѡ���ɫ
	m_Player[0]->SelectRole("����");
	m_Player[1]->SelectRole("����");
	//��ʼ����ѡ��ɫ
	CGameEngine::GetGE()->GetRole("����")->Init();
	//���ز��ű�������
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("��������","sound\\74.ogg");
	CGameEngine::GetGE()->GetAM()->SetLoopVolume(127);
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("��������");
	CGameEngine::GetGE()->SetEnterChange("��1");
}

//���
void C3::OutputRun()
{
	sprintf(dbug,"����%d",m_BackNo++/5%8);
	int type=_BACK_PRE;
	if(m_Player[0]->m_CurMove==61||m_Player[1]->m_CurMove==61||m_Player[0]->m_CurMove==103||m_Player[1]->m_CurMove==103)
	{
		type=_BACK_RED;
	}
	CGameEngine::GetGE()->GetGO()->DrawImg(dbug,0,0,640,480,virX,virY,640,480,0,1,type);
	
	//Ҫ���ж�˭�Ȼ�
	int outer=m_Player[0]->m_HurtS==NULL?1:0;
	for(int num=0;num<2;num++)
	{
		int no=(outer+num)%2;
		int dx=m_Player[no]->m_x -virX- CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player[no]->m_CurMove, m_Player[no]->m_CurF);
		int dy=m_Player[no]->m_y  - CGameEngine::GetGE()->GetMoves()->GetMoveY(m_Player[no]->m_CurMove, m_Player[no]->m_CurF);
		int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(m_Player[no]->m_CurMove, m_Player[no]->m_CurF);
		int m=_MIRROR_NONE;
		if(m_Player[no]->m_Face==_FACE_LEFT)
		{
			dx=m_Player[no]->m_x-virX - sw+CGameEngine::GetGE()->GetMoves()->GetMoveX(m_Player[no]->m_CurMove, m_Player[no]->m_CurF);
			m=_MIRROR_LR;
		}
		CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(m_Player[no]->m_CurMove,m_Player[no]->m_CurF), 
			dx,dy,m,m_Player[no]->m_Cor);//m_Player[num]->m_Cor

			////���ƹ�������
			//for(int i=0;i<CGameEngine::GetGE()->GetMoves()->GetActLength(m_Player[no]->m_CurMove,m_Player[no]->m_CurF);i++)
			//{
			//	MyRect mrt=CGameEngine::GetGE()->GetMoves()->GetActRect(m_Player[no]->m_CurMove,m_Player[no]->m_CurF)[i];
			//	RECT rt={
			//		m_Player[no]->m_x-virX+(m_Player[no]->m_Face==_FACE_RIGHT?mrt._x1:-mrt._x2),
			//		m_Player[no]->m_y+mrt._y1,
			//		m_Player[no]->m_x-virX+(m_Player[no]->m_Face==_FACE_RIGHT?mrt._x2:-mrt._x1),
			//		m_Player[no]->m_y+mrt._y2
			//	};
			//	CGameEngine::GetGE()->GetGO()->DrawRectangle(rt.left,rt.top,rt.right,rt.bottom,RGB(255,0,0));
			//}
			////���Ʒ�������
			//for(int i=0;i<CGameEngine::GetGE()->GetMoves()->GetDefLength(m_Player[no]->m_CurMove,m_Player[no]->m_CurF);i++)
			//{
			//	MyRect mrt=CGameEngine::GetGE()->GetMoves()->GetDefRect(m_Player[no]->m_CurMove,m_Player[no]->m_CurF)[i];
			//	RECT rt={
			//		m_Player[no]->m_x-virX+(m_Player[no]->m_Face==_FACE_RIGHT?mrt._x1:-mrt._x2),
			//		m_Player[no]->m_y+mrt._y1,
			//		m_Player[no]->m_x-virX+(m_Player[no]->m_Face==_FACE_RIGHT?mrt._x2:-mrt._x1),
			//		m_Player[no]->m_y+mrt._y2
			//	};
			//	CGameEngine::GetGE()->GetGO()->DrawRectangle(rt.left,rt.top,rt.right,rt.bottom,RGB(0,0,255));
			//}
			//CGameEngine::GetGE()->GetGO()->DrawLine(m_Player[no]->m_x-50-virX,m_Player[num]->m_y,m_Player[no]->m_x+50-virX,m_Player[no]->m_y);
			//CGameEngine::GetGE()->GetGO()->DrawLine(m_Player[no]->m_x-virX,m_Player[num]->m_y-20,m_Player[no]->m_x-virX,m_Player[no]->m_y+20);
			
			m_Player[no]->m_CurCF++;
			//�ж�ά��֡ �Ƿ񳬹� ��ͼƬ�涨֡��
			int curc=CGameEngine::GetGE()->GetMoves()->GetContinueFrame(m_Player[no]->m_CurMove, m_Player[no]->m_CurF);
			if(curc <= m_Player[no]->m_CurCF&&curc!=-1)
			{
				//ͼƬ++  �л�����һ��ͼƬ
				m_Player[no]->m_CurF++;
				//ͼƬ�л��Ժ� ����֡��0
				m_Player[no]->m_CurCF = 0;
				//�ö��� ͼƬ�������  ���л���Ĭ�ϵ���һ������
				if(CGameEngine::GetGE()->GetMoves()->GetFrameLen(m_Player[no]->m_CurMove) <= m_Player[no]->m_CurF)
				{
					m_Player[no]->m_CurMove = CGameEngine::GetGE()->GetMoves()->GetNextMove(m_Player[no]->m_CurMove);
					m_Player[no]->m_CurF = 0;
				}
			}

			//���ӵ�
			for(std::list<Bullet>::iterator b=m_Player[no]->m_Bullet.begin();b!=m_Player[no]->m_Bullet.end();)
			{
				int dx=b->_x -virX- CGameEngine::GetGE()->GetMoves()->GetMoveX(b->_CurM,b->_CurF);
				int dy=b->_y- CGameEngine::GetGE()->GetMoves()->GetMoveY(b->_CurM,b->_CurF);	
				int sw=CGameEngine::GetGE()->GetMoves()->GetPX2(b->_CurM,b->_CurF);	
				if(b->_mirror==_MIRROR_LR)
				{
					dx=b->_x -virX +CGameEngine::GetGE()->GetMoves()->GetMoveX(b->_CurM,b->_CurF)-sw;
				}
				CGameEngine::GetGE()->GetGO()->DrawRole(CGameEngine::GetGE()->GetMoves()->GetMoveP(b->_CurM,b->_CurF),
					dx,dy,b->_mirror);
	
			////���ƹ�������
			//for(int i=0;i<CGameEngine::GetGE()->GetMoves()->GetActLength(b->_CurM, b->_CurF);i++)
			//{
			//	MyRect mrt=CGameEngine::GetGE()->GetMoves()->GetActRect(b->_CurM, b->_CurF)[i];
			//	RECT rt={
			//		b->_x-virX+(b->_mirror==_MIRROR_NONE?mrt._x1:-mrt._x2),
			//		b->_y+mrt._y1,
			//		b->_x-virX+(b->_mirror==_MIRROR_NONE?mrt._x2:-mrt._x1),
			//		b->_y+mrt._y2
			//	};
			//	CGameEngine::GetGE()->GetGO()->DrawRectangle(rt.left,rt.top,rt.right,rt.bottom,RGB(255,0,0));
			//}
			////���Ʒ�������
			//for(int i=0;i<CGameEngine::GetGE()->GetMoves()->GetDefLength(b->_CurM, b->_CurF);i++)
			//{
			//	MyRect mrt=CGameEngine::GetGE()->GetMoves()->GetDefRect(b->_CurM, b->_CurF)[i];
			//	RECT rt={
			//		b->_x-virX+mrt._x1,
			//		b->_y+mrt._y1,
			//		b->_x-virX+mrt._x2,
			//		b->_y+mrt._y2
			//	};
			//	CGameEngine::GetGE()->GetGO()->DrawRectangle(rt.left,rt.top,rt.right,rt.bottom,RGB(0,0,255));
			//}
			bool add=true;
			b->_CF++;
			if(CGameEngine::GetGE()->GetMoves()->GetContinueFrame(b->_CurM, b->_CurF)<=b->_CF)
			{
				b->_CurF++;
				b->_CF=0;
				if(b->_CurF>=CGameEngine::GetGE()->GetMoves()->GetFrameLen(b->_CurM))
				{
					if(b->_type==_ZD_LAST)
						b->_CurF=0;
					else if(b->_type==_ZD_ONCE)
					{
						b=m_Player[no]->m_Bullet.erase(b);
						add=false;
					}
				}
			}
			if(add)
				b++;
		}
	}

	for(int p=0;p<2;p++)
	{
		//����Ч
		for(std::list<CTeXiao*>::iterator tx=m_Player[p]->m_TX.begin();tx!=m_Player[p]->m_TX.end();)
		{
			if((*tx)->Run(virX,&virY))
				tx++;
			else
				tx=m_Player[p]->m_TX.erase(tx);
		}	
	}

	

}

//������߼�
void C3::LogicInputRun()
{
	//����������ҵ���ؼ���
	for(int e=0;e<2;e++)
	{
		//˫����ǰ���ں���״̬ վ�� �¶� ���� ���� ������������
		int m_Site=CGameEngine::GetGE()->GetMoves()->GetSite(m_Player[e]->m_CurMove,m_Player[e]->m_CurF);
		int m_EnemySite=CGameEngine::GetGE()->GetMoves()->GetSite(m_Player[(e+1)%2]->m_CurMove,m_Player[(e+1)%2]->m_CurF);
		//�������ﳯ��ֻ�����ﴦ�ڿɲٿ�״̬ʱ���ܸ��³��򣬱������ڱ���ʱ����Ծ��
		//��ʹ˫��λ�÷���ҲҪ�ȵ�ǰ���������ſɸ���
		if((m_Site==10||m_Site==12||m_Site==20||m_Site==22)&&m_Player[e]->m_CurMove!=79)
		{
			if(m_Player[e]->m_x < m_Player[(e+1)%2]->m_x)
				m_Player[e]->m_Face=_FACE_RIGHT;
			else
				m_Player[e]->m_Face=_FACE_LEFT;
		}

		//��������֡����
		if(m_Player[e]->m_Tag!=0)
		{
			if(m_Player[e]->m_LF++>300)
			{
				m_Player[e]->m_LF=0;
				m_Player[e]->m_Tag=0;
			}
		}
		//��⵱ǰ֡�Ƿ������
		if(m_Site==15)
		{
			m_Player[e]->m_Tag=m_Player[e]->m_CurMove;
			m_Player[e]->m_LF=0;
		}

		//�ӵ�λ������
		for(std::list<Bullet>::iterator b=m_Player[e]->m_Bullet.begin(); b!=m_Player[e]->m_Bullet.end();b++)
		{
			b->_x+=(m_Player[e]->m_Face==_FACE_RIGHT?b->_vx:-b->_vx);
		}
		
		//��ȡ����ҵİ�������
		m_Player[e]->GetKeyIn();
		//����ͷż���
		m_Player[e]->m_Role->SearchSkill(m_Player[e], m_Player[(e+1)%2]);
		if(m_Player[e]->m_CurS)
			m_Player[e]->m_CurS->TriggerControl(m_Player[e], m_Player[(e+1)%2]);
		if(m_Player[e]->m_HurtS)
			m_Player[e]->m_HurtS->HitControl(m_Player[(e+1)%2], m_Player[e]);

		//�����ƶ�
		if(m_Player[e]->m_Face==_FACE_RIGHT)
			m_Player[e]->m_x+=m_Player[e]->m_vx;
		else
			m_Player[e]->m_x-=m_Player[e]->m_vx;
		m_Player[e]->m_y+=m_Player[e]->m_vy;

		//�ı��ٶ� 
		if(m_Player[e]->m_vx!=0&&m_Player[e]->m_y==400)
		{
			//�ڵ�����Ҫ�ܵ�Ħ������
			int prev=m_Player[e]->m_vx;
			m_Player[e]->m_vx+=m_Player[e]->m_vx>0?-_F:_F;
			if(prev*m_Player[e]->m_vx<0)
				m_Player[e]->m_vx=0;
		}
		else if(m_Player[e]->m_y<400)
		{//����
			m_Player[e]->m_vy+=_G;
		}
		else if(m_Player[e]->m_y>400)
		{//���
			m_Player[e]->m_vy=0;
			m_Player[e]->m_y=400;
		}

		//���Է���ÿ����������������Ĺ������� �ӵ����� ������������ײ
		for(int u=0;u<CGameEngine::GetGE()->GetMoves()->GetDefLength(m_Player[(e+1)%2]->m_CurMove,m_Player[(e+1)%2]->m_CurF);u++)
		{
			//�Է���������
			MyRect mydefR=CGameEngine::GetGE()->GetMoves()->GetDefRect(m_Player[(e+1)%2]->m_CurMove,m_Player[(e+1)%2]->m_CurF)[u];
			RECT def={
				m_Player[(e+1)%2]->m_x+(m_Player[(e+1)%2]->m_Face==_FACE_RIGHT ? mydefR._x1 : -mydefR._x2),
				m_Player[(e+1)%2]->m_y+mydefR._y1,
				m_Player[(e+1)%2]->m_x+(m_Player[(e+1)%2]->m_Face==_FACE_RIGHT ? mydefR._x2 : -mydefR._x1),
				m_Player[(e+1)%2]->m_y+mydefR._y2,
			};
			RECT c;

			//����������������ײ
			for(int v=0;v<CGameEngine::GetGE()->GetMoves()->GetActLength(m_Player[e]->m_CurMove,m_Player[e]->m_CurF);v++)
			{
				MyRect myactR=CGameEngine::GetGE()->GetMoves()->GetActRect(m_Player[e]->m_CurMove,m_Player[e]->m_CurF)[v];
				RECT act={
					m_Player[e]->m_x+(m_Player[e]->m_Face==_FACE_RIGHT ? myactR._x1 : -myactR._x2),
					m_Player[e]->m_y+myactR._y1,
					m_Player[e]->m_x+(m_Player[e]->m_Face==_FACE_RIGHT ? myactR._x2 : -myactR._x1),
					m_Player[e]->m_y+myactR._y2,
				};
				if(IntersectRect(&c, &act, &def))
				{
					m_Player[e]->m_CurS->HitJudge(m_Player[e],m_Player[(e+1)%2]);
					break;
				}
			}

			//��ÿ���ӵ��Ĺ�����������ײ
			for(std::list<Bullet>::iterator b=m_Player[e]->m_Bullet.begin();b!=m_Player[e]->m_Bullet.end();)
			{
				bool tag=false;
				for(int i=0;i<CGameEngine::GetGE()->GetMoves()->GetActLength(b->_CurM,b->_CurF);i++)
				{
					MyRect bactR=CGameEngine::GetGE()->GetMoves()->GetActRect(b->_CurM,b->_CurF)[i];
					RECT bact={
						b->_x+(b->_mirror==_MIRROR_NONE?bactR._x1:-bactR._x2), 
						b->_y+bactR._y1, 
						b->_x+(b->_mirror==_MIRROR_NONE?bactR._x2:-bactR._x1), 
						b->_y+ bactR._y2};
					//��Է���ɫ��ײ
					if(IntersectRect(&c, &bact, &def))
					{
						b->_Sk->HitJudge(m_Player[e],m_Player[(e+1)%2]);
						if(b->_type==_ZD_LAST)
						{
							b=m_Player[e]->m_Bullet.erase(b);
							tag=true;
						}
						break;
					}
					//�ӵ���ǽ����ײ ���ӵ�����
					if((bact.left>virX+640||bact.right<virX)&&b->_type==_ZD_LAST)
					{
						b=m_Player[e]->m_Bullet.erase(b);
						tag=true;	
						break;
					}
				}
				if(!tag)
					b++;
			}
			int mSite=CGameEngine::GetGE()->GetMoves()->GetSite(m_Player[e]->m_CurMove,m_Player[e]->m_CurF);
			int hSite=CGameEngine::GetGE()->GetMoves()->GetSite(m_Player[(e+1)%2]->m_CurMove,m_Player[(e+1)%2]->m_CurF);
			//�����������������ײ
			for(int v=0;v<CGameEngine::GetGE()->GetMoves()->GetDefLength(m_Player[e]->m_CurMove,m_Player[e]->m_CurF);v++)
			{
				MyRect hdefR=CGameEngine::GetGE()->GetMoves()->GetDefRect(m_Player[e]->m_CurMove,m_Player[e]->m_CurF)[v];
				RECT hdef={
					m_Player[e]->m_x+(m_Player[e]->m_Face==_FACE_RIGHT ? hdefR._x1 : -hdefR._x2),
					m_Player[e]->m_y+hdefR._y1,
					m_Player[e]->m_x+(m_Player[e]->m_Face==_FACE_RIGHT ? hdefR._x2 : -hdefR._x1),
					m_Player[e]->m_y+hdefR._y2,
				};
				//��������ǽ�ڵ���ײ ���ұ߽�
				if(hdef.left<virX)
				{
					if(def.right-hdef.left<640)
					{
						if(hdef.left>0)
							virX=hdef.left;
						else
						{
							virX=0;
							m_Player[e]->m_x=m_Player[e]->m_Face==_FACE_RIGHT?-hdefR._x1:hdefR._x2;
						}
					}
					else
						m_Player[e]->m_x+=virX-hdef.left;
				}
				else if(hdef.right>virX+640)
				{
					if(hdef.right-def.left<640)
					{
						if(hdef.right<1636)
							virX+=(hdef.right-virX-640);
						else
						{
							virX=1636-640;
							m_Player[e]->m_x=1636-(m_Player[e]->m_Face==_FACE_RIGHT ? hdefR._x2 : -hdefR._x1);
						}
					}
					else
						m_Player[e]->m_x-=hdef.right-virX-640;
				}
				if(def.left<virX)
				{
					if(hdef.right-def.left<640)
					{
						if(def.left>0)
							virX=def.left;
						else
						{
							virX=0;
							m_Player[(e+1)%2]->m_x=m_Player[(e+1)%2]->m_Face==_FACE_RIGHT?-mydefR._x1:mydefR._x2;						
						}
					}
					else
						m_Player[(e+1)%2]->m_x+=virX-def.left;
				}
				else if(def.right>virX+640)
				{
					if(def.right-hdef.left<640)
					{
						if(def.right<1636)
							virX+=(def.right-virX-640);
						else
						{
							virX=1636-640;
							m_Player[(e+1)%2]->m_x=1636-(m_Player[(e+1)%2]->m_Face==_FACE_RIGHT ? mydefR._x2 : -mydefR._x1);
						}
					}
					else 
						m_Player[(e+1)%2]->m_x-=def.right-virX-640;
				}
				//���������ҵ���ײ
				if(IntersectRect(&c, &hdef, &def)&&m_Player[e]->m_HurtS==NULL&&m_Player[(e+1)%2]->m_HurtS==NULL)
				{
					if(m_Player[e]->m_x<m_Player[(e+1)%2]->m_x)
						m_Player[e]->m_x=m_Player[e]->m_x-c.right+c.left;
					else 
						m_Player[e]->m_x=m_Player[e]->m_x+c.right-c.left;
				}

			}//����������ײ���

		}//ȫ����ײ����

	}

}

//��Ч��
void C3::Enter()
{}

//��Ч��
void C3::Quit()
{}
