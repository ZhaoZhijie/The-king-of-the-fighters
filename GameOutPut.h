#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <string>
#include <map> //映射
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
//镜像标记
#define _MIRROR_NONE 0	//不镜像
#define _MIRROR_LR 1	//左右镜像
#define _MIRROR_UD 2	//上下镜像
#define _MIRROR_LRUD 3	//左右上下 镜像
#define _COR_GREEN 1//绿色
#define _COR_RED 2//红色
#define _COR_GRAY 3 //灰色
#define _COR_BLUE 4 //蓝色
#define _BACK_PRE 0
#define _BACK_RED 1


class CGameOutput
{
	HWND m_hWnd;						//窗口
	int m_ClientW, m_ClientH;			//窗口客户区的宽 高
	HDC m_MainDC;						//主显示设备
	HDC m_BackDC;						//后备显示设备
	HDC m_DarkDC;						//亮度设备
	HDC m_MirrorDC;						//镜像设备
	std::map<std::string, HFONT> m_Font;//字体映射
	std::map<std::string, HDC> m_Bmp;	//位图映射
	std::map<std::string, Image*> m_Img;	//多格式图片映射
	unsigned char m_Dark;				//亮度值
public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	//开始绘制
	void Begin();

	//结束绘制
	void End();

	//绘制方法

	//画线
	void DrawLine(int x1, int y1, int x2, int y2, unsigned int c = RGB(0, 0, 0), int w = 1);
	//void DrawLine(POINT b, POINT e, unsigned int c = RGB(0, 0, 0)), int w = 1);

	//画矩形
	//空心矩形
	void DrawRectangle(int left, int top, int right, int bottom, unsigned int c = RGB(0, 0, 0), int w = 1);

	//实心矩形
	void DrawSRectangle(int left, int top, int right, int bottom, unsigned int pc = RGB(0, 0, 0), unsigned int bc = RGB(255, 255, 255));

	//画圆
	//空心圆
	void DrawEllipse(int left, int top, int right, int bottom, unsigned int c = RGB(0, 0, 0));

	//实心圆
	void DrawSEllipse(int left, int top, int right, int bottom, unsigned int pc = RGB(0, 0, 0), unsigned int bc = RGB(255, 255, 255));

	//任意格式图片
	bool LoadImg(const char* un, const wchar_t* fn);
	bool DrawImg(const char* un,int dx, int dy, int dw, int dh, int sx=0, int sy=0, int sw=0, int sh=0, char m = _MIRROR_NONE ,float alpha=1,int type=_BACK_PRE);
	//绘制角色专用
	bool DrawRole(const char* un,int dx, int dy, char m = _MIRROR_NONE,int cor=_COR_RED, float alpha=1);
	//红屏幕效果
	void DrawRedBack();
	//位图
	bool LoadBmp(const char* un, const char* fn);
	bool ReleaseBmp(const char* fn);

	bool DrawBmp(const char* fn, int dx, int dy, int dw, int dh, int sx, int sy);

	//绘制透明色位图 + 镜像
	bool DrawMiBmp(const char* fn, 
		int dx, int dy, int dw, int dh,
		int sx, int sy, int sw, int sh, char m = _MIRROR_NONE,
		unsigned int c = RGB(0, 255, 0));

	//字体相关
	bool LoadFont(const char* id,			//字体ID
				int w = 0, int h = 0,		//字体宽高
				int we = 400,				//字体粗细
				bool i = false,				//是否为斜体
				bool u = false,				//是否有下划线
				bool s = false,				//是否有穿越先
				const char* fn = "旧宋体"); //字体外观名称

	bool ReleaseFont(const char* id);

	//绘制单行文字
	bool DrawStringS(const char* id,
					int x, int y,	//文字要绘制的位置
					const char* t,	//要绘制的文字
					unsigned int c);//文字颜色

	//绘制多行文字
	bool DrawString(const char* id,
					int x, int y,	//文字要绘制的位置
					int w, int h,	//文字矩形的宽高
					const char* t,	//要绘制的文字
					unsigned int c);//文字颜色

	//获取亮度
	unsigned char GetDark();
	//设置亮度
	void SetDark(unsigned char d);
};

#endif