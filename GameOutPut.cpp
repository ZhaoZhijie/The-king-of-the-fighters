#include "GameOutput.h"
#pragma comment(lib, "msimg32.lib")

CGameOutput::CGameOutput(HWND hWnd)
{
	m_hWnd = hWnd;
	//�õ��ͻ����� ��
	RECT r;
	//�õ��ͻ����ľ�������
	GetClientRect(m_hWnd, &r);
	//��ÿͻ����Ŀ��
	m_ClientW = r.right - r.left;
	m_ClientH = r.bottom - r.top;

	//�õ�����ʾ�豸
	m_MainDC = GetDC(m_hWnd);

	HBITMAP hbmp = 0;

	m_Dark = 0;

	//�õ����豸
	m_BackDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_BackDC, hbmp));
	DeleteObject(hbmp);
	
	//��ʼ��GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);



	//���ú��豸���屳��͸��
	SetBkMode(m_BackDC, TRANSPARENT);

	//�õ������豸
	m_MirrorDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_MirrorDC, hbmp));
	DeleteObject(hbmp);

	//�õ������豸
	m_DarkDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_DarkDC, hbmp));
	DeleteObject(hbmp);
	
	BitBlt(m_DarkDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, BLACKNESS);
}

CGameOutput::~CGameOutput()
{
	std::map<std::string, HDC>::iterator i;
	//����ͼƬ
	for(i = m_Bmp.begin(); i != m_Bmp.end(); ++i)
	{
		DeleteDC(i->second);
	}
	std::map<std::string, HFONT>::iterator j;
	//��������
	for(j = m_Font.begin(); j != m_Font.end(); ++j)
	{
		DeleteObject(j->second);
	}
	DeleteDC(m_BackDC);
	DeleteDC(m_MirrorDC);
	ReleaseDC(m_hWnd, m_MainDC);
}

//��ʼ����
void CGameOutput::Begin()
{
	//��ջ�ֽ
	BitBlt(m_BackDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, WHITENESS);
}

//��������
void CGameOutput::End()
{
	//BitBlt(m_DarkDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, BLACKNESS);
	if(m_Dark != 0)
	{
		BLENDFUNCTION bf = {AC_SRC_OVER, 0, m_Dark, 0};
		AlphaBlend(m_BackDC, 0, 0, m_ClientW, m_ClientH, m_DarkDC, 0, 0, m_ClientW, m_ClientH, bf);
	}
	BitBlt(m_MainDC, 0, 0, m_ClientW, m_ClientH, m_BackDC, 0, 0, SRCCOPY);
}

//����
void CGameOutput::DrawLine(int x1, int y1, int x2, int y2, unsigned int c, int w)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(0, 0, 0) != c)
	{
		newpen = CreatePen(PS_SOLID, w, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	POINT p;
	MoveToEx(m_BackDC, x1, y1, &p);
	LineTo(m_BackDC, x2, y2);

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

//������
//���ľ���
void CGameOutput::DrawRectangle(int left, int top, int right, int bottom, unsigned int c, int w)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(0, 0, 0) != c)
	{
		newpen = CreatePen(PS_SOLID, w, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	POINT p[] = 
	{
		{left, top},
		{right, top},
		{right, bottom},
		{left, bottom},
		{left, top}
	};

	POINT q;
	for(int i = 0; i < 4; ++i)
	{
		MoveToEx(m_BackDC, p[i].x, p[i].y, &q);
		LineTo(m_BackDC, p[i + 1].x, p[i + 1].y);
	}

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

//ʵ�ľ���
void CGameOutput::DrawSRectangle(int left, int top, int right, int bottom, unsigned int pc, unsigned int bc)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;

	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;

	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(0, 0, 0) != pc)
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(255, 255, 255) != bc)
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);
	}

	Rectangle(m_BackDC, left, top, right, bottom);

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}

	if(newbrush)
	{
		SelectObject(m_BackDC, oldbrush);
		DeleteObject(newbrush);
	}
}

//��Բ
//����Բ
void CGameOutput::DrawEllipse(int left, int top, int right, int bottom, unsigned int c)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(0, 0, 0) != c)
	{
		newpen = CreatePen(PS_SOLID, 1, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//�õ�����ϵͳԤ�����úõ�һЩ GDI����
	HBRUSH newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	
	HBRUSH oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);

	Ellipse(m_BackDC, left, top, right, bottom);

	//�˴���ɾ�»�ˢ ����Create ������ ��ɾ����
	SelectObject(m_BackDC, oldbrush);

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

//ʵ��Բ
void CGameOutput::DrawSEllipse(int left, int top, int right, int bottom, unsigned int pc, unsigned int bc)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;

	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;

	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(0, 0, 0) != pc)
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//�жϱʵ���ɫ �Ƿ�Ϊ��ɫ ������Ǻ�ɫ �͸ı���ɫ 
	if(RGB(255, 255, 255) != bc)
	{
		newbrush = CreateSolidBrush(bc);
		oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);
	}

	Ellipse(m_BackDC, left, top, right, bottom);

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}

	if(newbrush)
	{
		SelectObject(m_BackDC, oldbrush);
		DeleteObject(newbrush);
	}
}





//λͼ
bool CGameOutput::LoadBmp(const char* un, const char* fn)
{
	std::string s = un;
	//λͼ������ ������Ψһ�� 
	//�˴��ڲ���λͼӳ���� �Ƿ��Ѿ����ڸ�����
	//������� �����ʧ��
	if(m_Bmp.find(s) != m_Bmp.end())
		return false;

	HBITMAP hbmp = (HBITMAP)LoadImage(0, fn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//���û��ͼƬ ���ؼ�
	if(!hbmp)
		return false;

	//������ҪHDC �������豸 ��ͨ�� ���豸����
	HDC dc = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(dc, hbmp));
	DeleteObject(hbmp);

	m_Bmp.insert(std::pair<std::string, HDC>(s, dc));
	return true;
}
bool CGameOutput::ReleaseBmp(const char* fn)
{
	std::string s = fn;
	//ͨ���������ҵ� ��ͼƬ
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//���û�ҵ� ɾ��ʧ��
	if(i == m_Bmp.end())
		return false;

	//�ҵ���ֱ���ͷ� �豸
	DeleteDC(i->second);
	//ɾ��ӳ���е�����
	m_Bmp.erase(i);

	return true;
}

//����ͼƬ
bool CGameOutput::LoadImg(const char* un, const wchar_t* fn)
{
	std::string s = un;
	if(m_Bmp.find(s) != m_Bmp.end())
		return false;
	Image *img=new Image(fn);
	if(!img)
		return false;
	m_Img.insert(std::pair<std::string, Image*>(s, img));
	return true;
}

//����ĻЧ��
void CGameOutput::DrawRedBack()
{
	Point points[3];
	points[0]=Point(0,0);
	points[1]=Point(640,0);
	points[2]=Point(0,480);
	Graphics graphics(m_BackDC);
	ImageAttributes imAtt;
			ColorMatrix cm = {  
					1,0,0,0,0,  
					0,1,0,0,0,  
					0,0,1,0,0,  
					0,0,0,0.8,0,  
					0,0,0,0,1}; 
	imAtt.SetColorMatrix(&cm); 
	Image img(L"pic\\����.bmp");
	graphics.DrawImage(&img,points,3,0,0,640,480,UnitPixel,&imAtt);
}

//���ƽ�ɫר��
bool CGameOutput::DrawRole(const char* un,int dx, int dy, char m, int cor, float alpha)
{
	std::string s = un;
	std::map<std::string, Image*>::iterator i=m_Img.find(s);
	if(i == m_Img.end())
		return false;
	Graphics graphics(m_BackDC);
	Point points[3];
	int srcw=i->second->GetWidth();
	int srch=i->second->GetHeight();
	switch(m)
	{
	case _MIRROR_NONE:
		points[0]=Point(dx,dy);
		points[1]=Point(dx+srcw,dy);
		points[2]=Point(dx,dy+srch);
		break;
	case _MIRROR_LR:
		points[0]=Point(dx+srcw,dy);
		points[1]=Point(dx,dy);
		points[2]=Point(dx+srcw,dy+srch);
		break;
	case _MIRROR_UD:
		points[0]=Point(dx,dy+srch);
		points[1]=Point(dx,dy+srch);
		points[2]=Point(dx,dy);
		break;
	case _MIRROR_LRUD:
		points[0]=Point(dx+srcw,dy+srch);
		points[1]=Point(dx,dy);
		points[2]=Point(dx+srcw,dy);
		break;
	}
	ImageAttributes imAtt;
	imAtt.SetColorKey(Color(255, 0, 255),Color(255, 0, 255));
	switch(cor)
	{
	case _COR_GREEN:
		{
			ColorMatrix cm = {  
					0,1,0,0,0,  
					1,0,0,0,0,  
					0,0,1,0,0,  
					0,0,0,alpha,0,  
					0,0,0,0,1}; 
			imAtt.SetColorMatrix(&cm); 
			break;
		}
	case _COR_RED:
		{
			ColorMatrix cm = {  
					1,0,0,0,0,  
					0,1,0,0,0,  
					0,0,1,0,0,  
					0,0,0,alpha,0,  
					0,0,0,0,1}; 
			imAtt.SetColorMatrix(&cm); 
			break;		
		}
	case _COR_GRAY:
		{
			ColorMatrix cm = {  
					1,1,1,0,0,  
					0,0,0,0,0,  
					0,0,0,0,0,  
					0,0,0,alpha,0,  
					0,0,0,0,1}; 
			imAtt.SetColorMatrix(&cm); 
			break;		
		}
	case _COR_BLUE:
		{//19 74 211
			ColorMatrix cm = {  
					0,0,0,0,0,  
					0,0,0,0,0,  
					0,0,0,0,0,  
					0,0,0,alpha,0,  
					1,1,1,0,1}; 
			imAtt.SetColorMatrix(&cm); 
			break;		
		}
	}	
	graphics.DrawImage(i->second,points,3,0,0,srcw,srch,UnitPixel,&imAtt);
}
//�����ָ�ʽͼƬ
bool CGameOutput::DrawImg(const char* un,int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, char m, float alpha, int type)
{
	std::string s = un;
	std::map<std::string, Image*>::iterator i=m_Img.find(s);
	if(i == m_Img.end())
		return false;
	Graphics graphics(m_BackDC);
	Point points[3];
	switch(m)
	{
	case _MIRROR_NONE:
		points[0]=Point(dx,dy);
		points[1]=Point(dx+dw,dy);
		points[2]=Point(dx,dy+dh);
		break;
	case _MIRROR_LR:
		points[0]=Point(dx+dw,dy);
		points[1]=Point(dx,dy);
		points[2]=Point(dx+dw,dy+dh);
		break;
	case _MIRROR_UD:
		points[0]=Point(dx,dy+dh);
		points[1]=Point(dx,dy+dh);
		points[2]=Point(dx,dy);
		break;
	case _MIRROR_LRUD:
		points[0]=Point(dx+dw,dy+dh);
		points[1]=Point(dx,dy);
		points[2]=Point(dx+dw,dy);
		break;
	}
	int srcw=sw==0?dw:sw;
	int srch=sw==0?dh:sh;//ImageAttributes imAtt
	ImageAttributes imAtt;
	imAtt.SetColorKey(Color(255, 0, 255),Color(255, 0, 255));
	
	if(type==_BACK_RED)
	{
		ColorMatrix cm = {  
			1,0,0,0,0,  
			0,0,0,0,0,  
			0,0,0,0,0,  
			0,0,0,1,0,  
			0,0,0,0,1};  
		imAtt.SetColorMatrix(&cm); 		
	}
	graphics.DrawImage(i->second,points,3,sx,sy,srcw,srch,UnitPixel,&imAtt);
}


bool CGameOutput::DrawBmp(const char* fn, int dx, int dy, int dw, int dh, int sx, int sy)
{
	std::string s = fn;
	//ͨ���������ҵ� ��ͼƬ
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//���û�ҵ� ɾ��ʧ��
	if(i == m_Bmp.end())
		return false;

	BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);
	return true;
}

//����͸��ɫλͼ + ����
bool CGameOutput::DrawMiBmp(const char* fn, 
		int dx, int dy, int dw, int dh,
		int sx, int sy, int sw, int sh, char m ,unsigned int c)
{
	if(m < _MIRROR_NONE || m > _MIRROR_LRUD)
		return false;

	std::string s = fn;
	//ͨ���������ҵ� ��ͼƬ
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//���û�ҵ� ɾ��ʧ��
	if(i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _MIRROR_NONE: 
		{
			TransparentBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, sw, sh, c);
			break;
		}
	case _MIRROR_LR:
		{
			StretchBlt(m_MirrorDC, dw - 1, 0, -dw, dh, i->second, sx, sy, sw, sh, SRCCOPY);
			TransparentBlt(m_BackDC, dx, dy, dw, dh, m_MirrorDC, 0, 0, dw, dh, c);
			break;
		}
	case _MIRROR_UD:
		{
			StretchBlt(m_MirrorDC, 0, dh - 1, dw, -dh, i->second, sx, sy, sw, sh, SRCCOPY);
			TransparentBlt(m_BackDC, dx, dy, dw, dh, m_MirrorDC, 0, 0, dw, dh, c);
			break;
		}
	case _MIRROR_LRUD:
		{
			StretchBlt(m_MirrorDC, dw - 1, dh - 1, -dw, -dh, i->second, sx, sy, sw, sh, SRCCOPY);
			TransparentBlt(m_BackDC, dx, dy, dw, dh, m_MirrorDC, 0, 0, dw, dh, c);
			break;
		}
	}
	return true;
}

//�������
bool CGameOutput::LoadFont(const char* id,	//����ID
				int w, int h,		//������
				int we,				//�����ϸ
				bool i,				//�Ƿ�Ϊб��
				bool u,				//�Ƿ����»���
				bool s,				//�Ƿ��д�Խ��
				const char* fn) //�����������
{
	std::string sid = id;;
	if(m_Font.find(sid) != m_Font.end())
		return false;

	HFONT font = CreateFontA(h, w, 0, 0, we, i, u, s, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fn);

	if(!font)
		return false;

	m_Font.insert(std::pair<std::string, HFONT>(sid, font));

	return true;
}

bool CGameOutput::ReleaseFont(const char* id)
{
	//�����Ƿ����
	std::string s = id;
	std::map<std::string, HFONT>::iterator i = m_Font.find(s);
	//���û������ �򷵻ؼ�
	if(i == m_Font.end())
		return false;

	//����ɾ��
	DeleteObject(i->second);
	m_Font.erase(i);

	return true;
}

//���Ƶ�������
bool CGameOutput::DrawStringS(const char* id,
					int x, int y,	//����Ҫ���Ƶ�λ��
					const char* t,	//Ҫ���Ƶ�����
					unsigned int c)//������ɫ
{
	if(id)
	{
		//�����Ƿ��������
		std::string s = id;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if(i == m_Font.end())
			return false;

		//�ı�����
		HFONT oldfont = (HFONT)SelectObject(m_BackDC, i->second);
		//�ı�������ɫ �������ǰ����ɫ
		unsigned int pc = SetTextColor(m_BackDC, c);
		TextOutA(m_BackDC, x, y, t, (int)strlen(t));
		//��������ǰ����ɫ ���û�ȥ
		SetTextColor(m_BackDC, pc);
		//���û���ǰ�����壨Ĭ�����壩
		SelectObject(m_BackDC, oldfont);
	}
	//ʹ��Ĭ������ ֻ��Ҫ��������ɫ
	else
	{
		unsigned int pc = SetTextColor(m_BackDC, c);
		TextOutA(m_BackDC, x, y, t, (int)strlen(t));
		SetTextColor(m_BackDC, pc);
	}
	return true;
}

//���ƶ�������
bool CGameOutput::DrawString(const char* id,
					int x, int y,	//����Ҫ���Ƶ�λ��
					int w, int h,	//���־��εĿ��
					const char* t,	//Ҫ���Ƶ�����
					unsigned int c)//������ɫ
{
	if(id)
	{
		std::string s = id;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if(i == m_Font.end())
			return false;

		HFONT oldfont = (HFONT)SelectObject(m_BackDC, i->second);
		unsigned int pc = SetTextColor(m_BackDC, c);

		RECT r = {x, y, x + w, y + h};

		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);
		SetTextColor(m_BackDC, pc);
		SelectObject(m_BackDC, oldfont);
	}
	else
	{
		unsigned int pc = SetTextColor(m_BackDC, c);
		RECT r = {x, y, x + w, y + h};
		DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);
		SetTextColor(m_BackDC, pc);
	}
	return true;
}

//��ȡ����
unsigned char CGameOutput::GetDark()
{
	return m_Dark;
}
//��������
void CGameOutput::SetDark(unsigned char d)
{
	m_Dark = d;
}