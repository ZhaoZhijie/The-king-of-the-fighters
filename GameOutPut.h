#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <string>
#include <map> //ӳ��
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
//������
#define _MIRROR_NONE 0	//������
#define _MIRROR_LR 1	//���Ҿ���
#define _MIRROR_UD 2	//���¾���
#define _MIRROR_LRUD 3	//�������� ����
#define _COR_GREEN 1//��ɫ
#define _COR_RED 2//��ɫ
#define _COR_GRAY 3 //��ɫ
#define _COR_BLUE 4 //��ɫ
#define _BACK_PRE 0
#define _BACK_RED 1


class CGameOutput
{
	HWND m_hWnd;						//����
	int m_ClientW, m_ClientH;			//���ڿͻ����Ŀ� ��
	HDC m_MainDC;						//����ʾ�豸
	HDC m_BackDC;						//����ʾ�豸
	HDC m_DarkDC;						//�����豸
	HDC m_MirrorDC;						//�����豸
	std::map<std::string, HFONT> m_Font;//����ӳ��
	std::map<std::string, HDC> m_Bmp;	//λͼӳ��
	std::map<std::string, Image*> m_Img;	//���ʽͼƬӳ��
	unsigned char m_Dark;				//����ֵ
public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	//��ʼ����
	void Begin();

	//��������
	void End();

	//���Ʒ���

	//����
	void DrawLine(int x1, int y1, int x2, int y2, unsigned int c = RGB(0, 0, 0), int w = 1);
	//void DrawLine(POINT b, POINT e, unsigned int c = RGB(0, 0, 0)), int w = 1);

	//������
	//���ľ���
	void DrawRectangle(int left, int top, int right, int bottom, unsigned int c = RGB(0, 0, 0), int w = 1);

	//ʵ�ľ���
	void DrawSRectangle(int left, int top, int right, int bottom, unsigned int pc = RGB(0, 0, 0), unsigned int bc = RGB(255, 255, 255));

	//��Բ
	//����Բ
	void DrawEllipse(int left, int top, int right, int bottom, unsigned int c = RGB(0, 0, 0));

	//ʵ��Բ
	void DrawSEllipse(int left, int top, int right, int bottom, unsigned int pc = RGB(0, 0, 0), unsigned int bc = RGB(255, 255, 255));

	//�����ʽͼƬ
	bool LoadImg(const char* un, const wchar_t* fn);
	bool DrawImg(const char* un,int dx, int dy, int dw, int dh, int sx=0, int sy=0, int sw=0, int sh=0, char m = _MIRROR_NONE ,float alpha=1,int type=_BACK_PRE);
	//���ƽ�ɫר��
	bool DrawRole(const char* un,int dx, int dy, char m = _MIRROR_NONE,int cor=_COR_RED, float alpha=1);
	//����ĻЧ��
	void DrawRedBack();
	//λͼ
	bool LoadBmp(const char* un, const char* fn);
	bool ReleaseBmp(const char* fn);

	bool DrawBmp(const char* fn, int dx, int dy, int dw, int dh, int sx, int sy);

	//����͸��ɫλͼ + ����
	bool DrawMiBmp(const char* fn, 
		int dx, int dy, int dw, int dh,
		int sx, int sy, int sw, int sh, char m = _MIRROR_NONE,
		unsigned int c = RGB(0, 255, 0));

	//�������
	bool LoadFont(const char* id,			//����ID
				int w = 0, int h = 0,		//������
				int we = 400,				//�����ϸ
				bool i = false,				//�Ƿ�Ϊб��
				bool u = false,				//�Ƿ����»���
				bool s = false,				//�Ƿ��д�Խ��
				const char* fn = "������"); //�����������

	bool ReleaseFont(const char* id);

	//���Ƶ�������
	bool DrawStringS(const char* id,
					int x, int y,	//����Ҫ���Ƶ�λ��
					const char* t,	//Ҫ���Ƶ�����
					unsigned int c);//������ɫ

	//���ƶ�������
	bool DrawString(const char* id,
					int x, int y,	//����Ҫ���Ƶ�λ��
					int w, int h,	//���־��εĿ��
					const char* t,	//Ҫ���Ƶ�����
					unsigned int c);//������ɫ

	//��ȡ����
	unsigned char GetDark();
	//��������
	void SetDark(unsigned char d);
};

#endif