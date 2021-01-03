#include "GameOutput.h"
#pragma comment(lib, "msimg32.lib")

CGameOutput::CGameOutput(HWND hWnd)
{
	m_hWnd = hWnd;
	//得到客户区宽、 高
	RECT r;
	//得到客户区的矩形区域
	GetClientRect(m_hWnd, &r);
	//求得客户区的宽高
	m_ClientW = r.right - r.left;
	m_ClientH = r.bottom - r.top;

	//得到主显示设备
	m_MainDC = GetDC(m_hWnd);

	HBITMAP hbmp = 0;

	m_Dark = 0;

	//得到后备设备
	m_BackDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_BackDC, hbmp));
	DeleteObject(hbmp);
	
	//初始化GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);



	//设置后备设备字体背景透明
	SetBkMode(m_BackDC, TRANSPARENT);

	//得到镜像设备
	m_MirrorDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_MirrorDC, hbmp));
	DeleteObject(hbmp);

	//得到亮度设备
	m_DarkDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_DarkDC, hbmp));
	DeleteObject(hbmp);
	
	BitBlt(m_DarkDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, BLACKNESS);
}

CGameOutput::~CGameOutput()
{
	std::map<std::string, HDC>::iterator i;
	//销毁图片
	for(i = m_Bmp.begin(); i != m_Bmp.end(); ++i)
	{
		DeleteDC(i->second);
	}
	std::map<std::string, HFONT>::iterator j;
	//销毁字体
	for(j = m_Font.begin(); j != m_Font.end(); ++j)
	{
		DeleteObject(j->second);
	}
	DeleteDC(m_BackDC);
	DeleteDC(m_MirrorDC);
	ReleaseDC(m_hWnd, m_MainDC);
}

//开始绘制
void CGameOutput::Begin()
{
	//清空画纸
	BitBlt(m_BackDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, WHITENESS);
}

//结束绘制
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

//画线
void CGameOutput::DrawLine(int x1, int y1, int x2, int y2, unsigned int c, int w)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
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

//画矩形
//空心矩形
void CGameOutput::DrawRectangle(int left, int top, int right, int bottom, unsigned int c, int w)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
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

//实心矩形
void CGameOutput::DrawSRectangle(int left, int top, int right, int bottom, unsigned int pc, unsigned int bc)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;

	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;

	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
	if(RGB(0, 0, 0) != pc)
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
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

//画圆
//空心圆
void CGameOutput::DrawEllipse(int left, int top, int right, int bottom, unsigned int c)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;
	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
	if(RGB(0, 0, 0) != c)
	{
		newpen = CreatePen(PS_SOLID, 1, c);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//得到操作系统预先设置好的一些 GDI对象
	HBRUSH newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	
	HBRUSH oldbrush = (HBRUSH)SelectObject(m_BackDC, newbrush);

	Ellipse(m_BackDC, left, top, right, bottom);

	//此处不删新画刷 不是Create 出来的 不删除。
	SelectObject(m_BackDC, oldbrush);

	if(newpen)
	{
		SelectObject(m_BackDC, oldpen);
		DeleteObject(newpen);
	}
}

//实心圆
void CGameOutput::DrawSEllipse(int left, int top, int right, int bottom, unsigned int pc, unsigned int bc)
{
	HPEN newpen = 0;
	HPEN oldpen = 0;

	HBRUSH newbrush = 0;
	HBRUSH oldbrush = 0;

	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
	if(RGB(0, 0, 0) != pc)
	{
		newpen = CreatePen(PS_SOLID, 1, pc);
		oldpen = (HPEN)SelectObject(m_BackDC, newpen);
	}

	//判断笔的颜色 是否为黑色 如果不是黑色 就改变颜色 
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





//位图
bool CGameOutput::LoadBmp(const char* un, const char* fn)
{
	std::string s = un;
	//位图的名称 必须是唯一的 
	//此处在查找位图映射里 是否已经存在该名字
	//如果存在 则加载失败
	if(m_Bmp.find(s) != m_Bmp.end())
		return false;

	HBITMAP hbmp = (HBITMAP)LoadImage(0, fn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//如果没有图片 返回假
	if(!hbmp)
		return false;

	//所有需要HDC 创建的设备 都通过 主设备创建
	HDC dc = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(dc, hbmp));
	DeleteObject(hbmp);

	m_Bmp.insert(std::pair<std::string, HDC>(s, dc));
	return true;
}
bool CGameOutput::ReleaseBmp(const char* fn)
{
	std::string s = fn;
	//通过迭代器找到 该图片
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//如果没找到 删除失败
	if(i == m_Bmp.end())
		return false;

	//找到后直接释放 设备
	DeleteDC(i->second);
	//删除映射中的数据
	m_Bmp.erase(i);

	return true;
}

//加载图片
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

//红屏幕效果
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
	Image img(L"pic\\红屏.bmp");
	graphics.DrawImage(&img,points,3,0,0,640,480,UnitPixel,&imAtt);
}

//绘制角色专用
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
//画多种格式图片
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
	//通过迭代器找到 该图片
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//如果没找到 删除失败
	if(i == m_Bmp.end())
		return false;

	BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);
	return true;
}

//绘制透明色位图 + 镜像
bool CGameOutput::DrawMiBmp(const char* fn, 
		int dx, int dy, int dw, int dh,
		int sx, int sy, int sw, int sh, char m ,unsigned int c)
{
	if(m < _MIRROR_NONE || m > _MIRROR_LRUD)
		return false;

	std::string s = fn;
	//通过迭代器找到 该图片
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);

	//如果没找到 删除失败
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

//字体相关
bool CGameOutput::LoadFont(const char* id,	//字体ID
				int w, int h,		//字体宽高
				int we,				//字体粗细
				bool i,				//是否为斜体
				bool u,				//是否有下划线
				bool s,				//是否有穿越先
				const char* fn) //字体外观名称
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
	//字体是否存在
	std::string s = id;
	std::map<std::string, HFONT>::iterator i = m_Font.find(s);
	//如果没有字体 则返回假
	if(i == m_Font.end())
		return false;

	//有则删除
	DeleteObject(i->second);
	m_Font.erase(i);

	return true;
}

//绘制单行文字
bool CGameOutput::DrawStringS(const char* id,
					int x, int y,	//文字要绘制的位置
					const char* t,	//要绘制的文字
					unsigned int c)//文字颜色
{
	if(id)
	{
		//查找是否存在字体
		std::string s = id;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if(i == m_Font.end())
			return false;

		//改变字体
		HFONT oldfont = (HFONT)SelectObject(m_BackDC, i->second);
		//改变字体颜色 并获得以前的颜色
		unsigned int pc = SetTextColor(m_BackDC, c);
		TextOutA(m_BackDC, x, y, t, (int)strlen(t));
		//把字体以前的颜色 设置回去
		SetTextColor(m_BackDC, pc);
		//设置回以前的字体（默认字体）
		SelectObject(m_BackDC, oldfont);
	}
	//使用默认字体 只需要改字体颜色
	else
	{
		unsigned int pc = SetTextColor(m_BackDC, c);
		TextOutA(m_BackDC, x, y, t, (int)strlen(t));
		SetTextColor(m_BackDC, pc);
	}
	return true;
}

//绘制多行文字
bool CGameOutput::DrawString(const char* id,
					int x, int y,	//文字要绘制的位置
					int w, int h,	//文字矩形的宽高
					const char* t,	//要绘制的文字
					unsigned int c)//文字颜色
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

//获取亮度
unsigned char CGameOutput::GetDark()
{
	return m_Dark;
}
//设置亮度
void CGameOutput::SetDark(unsigned char d)
{
	m_Dark = d;
}