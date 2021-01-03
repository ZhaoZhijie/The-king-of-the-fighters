#include "GameInput.h"

CGameInput::CGameInput(HWND hWnd)
{
	m_hWnd = hWnd;
	
	m_Key[_GI_M_L] = VK_LBUTTON; //鼠标左键
	m_Key[_GI_M_M] = VK_MBUTTON; //鼠标中键
	m_Key[_GI_M_R] = VK_RBUTTON; //鼠标右键
	m_Key[_GI_K_A] = 'A'; //键盘字母键A
	m_Key[_GI_K_B] = 'B'; //键盘字母键B
	m_Key[_GI_K_C] = 'C'; //键盘字母键C
	m_Key[_GI_K_D] = 'D'; //键盘字母键D
	m_Key[_GI_K_E] = 'E'; //键盘字母键E
	m_Key[_GI_K_F] = 'F'; //键盘字母键F
	m_Key[_GI_K_G] = 'G'; //键盘字母键G
	m_Key[_GI_K_H] = 'H'; //键盘字母键H
	m_Key[_GI_K_I] = 'I'; //键盘字母键I
	m_Key[_GI_K_J] = 'J'; //键盘字母键J
	m_Key[_GI_K_K] = 'K'; //键盘字母键K
	m_Key[_GI_K_L] = 'L'; //键盘字母键L
	m_Key[_GI_K_M] = 'M'; //键盘字母键M
	m_Key[_GI_K_N] = 'N'; //键盘字母键N
	m_Key[_GI_K_O] = 'O'; //键盘字母键O
	m_Key[_GI_K_P] = 'P'; //键盘字母键P
	m_Key[_GI_K_Q] = 'Q'; //键盘字母键Q
	m_Key[_GI_K_R] = 'R'; //键盘字母键R
	m_Key[_GI_K_S] = 'S'; //键盘字母键S
	m_Key[_GI_K_T] = 'T'; //键盘字母键T
	m_Key[_GI_K_U] = 'U'; //键盘字母键U
	m_Key[_GI_K_V] = 'V'; //键盘字母键V
	m_Key[_GI_K_W] = 'W'; //键盘字母键W
	m_Key[_GI_K_X] = 'X'; //键盘字母键X
	m_Key[_GI_K_Y] = 'Y'; //键盘字母键Y
	m_Key[_GI_K_Z] = 'Z'; //键盘字母键Z
	m_Key[_GI_K_0] = 0x30; //键盘数字键0
	m_Key[_GI_K_1] = 0x31; //键盘数字键1
	m_Key[_GI_K_2] = 0x32; //键盘数字键2
	m_Key[_GI_K_3] = 0x33; //键盘数字键3
	m_Key[_GI_K_4] = 0x34; //键盘数字键4
	m_Key[_GI_K_5] = 0x35; //键盘数字键5
	m_Key[_GI_K_6] = 0x36; //键盘数字键6
	m_Key[_GI_K_7] = 0x37; //键盘数字键7
	m_Key[_GI_K_8] = 0x38; //键盘数字键8
	m_Key[_GI_K_9] = 0x39; //键盘数字键9
	m_Key[_GI_K_F01] = VK_F1; //键盘键F1
	m_Key[_GI_K_F02] = VK_F2; //键盘键F2
	m_Key[_GI_K_F03] = VK_F3; //键盘键F3
	m_Key[_GI_K_F04] = VK_F4; //键盘键F4
	m_Key[_GI_K_F05] = VK_F5; //键盘键F5
	m_Key[_GI_K_F06] = VK_F6; //键盘键F6
	m_Key[_GI_K_F07] = VK_F7; //键盘键F7
	m_Key[_GI_K_F08] = VK_F8; //键盘键F8
	m_Key[_GI_K_F09] = VK_F9; //键盘键F9
	m_Key[_GI_K_F10] = VK_F10; //键盘键F10
	m_Key[_GI_K_F11] = VK_F11; //键盘键F11
	m_Key[_GI_K_F12] = VK_F12; //键盘键F12
	m_Key[_GI_K_ESC] = VK_ESCAPE; //键盘键Esc
	m_Key[_GI_K_OEM_3] = VK_OEM_3; //键盘键~
	m_Key[_GI_K_OEM_MINUS] = VK_OEM_MINUS; //键盘键_
	m_Key[_GI_K_OEM_PLUS] = VK_OEM_PLUS; //键盘键+
	m_Key[_GI_K_OEM_5] = VK_OEM_5; //键盘键|
	m_Key[_GI_K_BACK] = VK_BACK; //键盘键Back Space
	m_Key[_GI_K_TAB] = VK_TAB; //键盘键Tab
	m_Key[_GI_K_OEM_4] = VK_OEM_4; //键盘键{
	m_Key[_GI_K_OEM_6] = VK_OEM_6; //键盘键}
	m_Key[_GI_K_RETURN] = VK_RETURN; //键盘键Enter
	m_Key[_GI_K_CAPITAL_LOCK] = VK_CAPITAL; //键盘键Caps Lock
	m_Key[_GI_K_OEM_1] = VK_OEM_1; //键盘键:
	m_Key[_GI_K_OEM_7] = VK_OEM_7; //键盘键"
	m_Key[_GI_K_L_SHIFT] = VK_LSHIFT; //键盘键左Shift
	m_Key[_GI_K_OEM_COMMA] = VK_OEM_COMMA; //键盘键<
	m_Key[_GI_K_OEM_PERIOD] = VK_OEM_PERIOD; //键盘键>
	m_Key[_GI_K_OEM_2] = VK_OEM_2; //键盘键?
	m_Key[_GI_K_R_SHIFT] = VK_RSHIFT; //键盘键右Shift
	m_Key[_GI_K_L_CTRL] = VK_LCONTROL; //键盘键左Ctrl
	m_Key[_GI_K_L_ALT] = VK_LMENU; //键盘键左Alt
	m_Key[_GI_K_SPACE] = VK_SPACE; //键盘键Spacebar
	m_Key[_GI_K_R_ALT] = VK_RMENU; //键盘键右Alt
	m_Key[_GI_K_R_CTRL] = VK_RCONTROL; //键盘键右Ctrl
	m_Key[_GI_K_PRINT_SCREEN] = VK_SNAPSHOT; //键盘键Print Screen
	m_Key[_GI_K_SCROLL_LOCK] = VK_SCROLL; //键盘键Scroll Lock
	m_Key[_GI_K_INSERT] = VK_INSERT; //键盘键Insert
	m_Key[_GI_K_HOME] = VK_HOME; //键盘键Home
	m_Key[_GI_K_PAGE_UP] = VK_PRIOR; //键盘键Page Up
	m_Key[_GI_K_DELETE] = VK_DELETE; //键盘键Delete
	m_Key[_GI_K_END] = VK_END; //键盘键End
	m_Key[_GI_K_PAGE_DOWN] = VK_NEXT; //键盘键Page Down
	m_Key[_GI_K_UP] = VK_UP; //键盘键↑
	m_Key[_GI_K_DOWN] = VK_DOWN; //键盘键↓
	m_Key[_GI_K_LEFT] = VK_LEFT; //键盘键←
	m_Key[_GI_K_RIGHT] = VK_RIGHT; //键盘键→
	m_Key[_GI_NK_NUM_LOCK] = VK_NUMLOCK; //小键盘键Num Lock
	m_Key[_GI_NK_DIVIDE] = VK_DIVIDE; //小键盘键除
	m_Key[_GI_NK_MULTIPLY] = VK_MULTIPLY; //小键盘键乘
	m_Key[_GI_NK_ADD] = VK_ADD; //小键盘键加
	m_Key[_GI_NK_SEPARATOR] = VK_SEPARATOR; //小键盘键减
	m_Key[_GI_NK_DECIMAL] = VK_DECIMAL; //小键盘键小数点
	m_Key[_GI_NK_0] = VK_NUMPAD0; //小键盘键数字键0
	m_Key[_GI_NK_1] = VK_NUMPAD1; //小键盘键数字键1
	m_Key[_GI_NK_2] = VK_NUMPAD2; //小键盘键数字键2
	m_Key[_GI_NK_3] = VK_NUMPAD3; //小键盘键数字键3
	m_Key[_GI_NK_4] = VK_NUMPAD4; //小键盘键数字键4
	m_Key[_GI_NK_5] = VK_NUMPAD5; //小键盘键数字键5
	m_Key[_GI_NK_6] = VK_NUMPAD6; //小键盘键数字键6
	m_Key[_GI_NK_7] = VK_NUMPAD7; //小键盘键数字键7
	m_Key[_GI_NK_8] = VK_NUMPAD8; //小键盘键数字键8
	m_Key[_GI_NK_9] = VK_NUMPAD9; //小键盘键数字键9

	//所有按键设置初始状态为 持续放开
	for (unsigned int i = 0; i < _GI_KEY_NUM; ++i)
		m_KeyState[i] = _KS_UH;
}

void CGameInput::Run()
{
	for(int i = 0; i < _GI_KEY_NUM; ++i)
	{
		//如果这次按键按下
		if(GetAsyncKeyState(m_Key[i]) & 0x8000)
		{
			//上次按键不是按下
			if(m_KeyState[i] == _KS_UH || m_KeyState[i] == _KS_UC)
				m_KeyState[i] = _KS_DC; //这次为 瞬间按下
			//上次按键是按下状态
			else
				m_KeyState[i] = _KS_DH;//这次为 持续按下
		}
		//如果这次按键没有按下
		else
		{
			//如果上次按键 没有按下
			if(m_KeyState[i] == _KS_UH || m_KeyState[i] == _KS_UC)
				m_KeyState[i] = _KS_UH; //这次按键为 持续放开
			//如果上次按键是按下状态
			else
				m_KeyState[i] = _KS_UC;	//这次按键为 瞬间放开
		}
	}
}
int CGameInput::Get(unsigned char Key)
{
	if(Key >= _GI_KEY_NUM)
		return _KS_IK;

	return m_KeyState[Key];
}

//判断x y是否在客户区内 并获取鼠标位置
bool CGameInput::GetCursor(int* x, int* y)
{
	POINT p;
	//获取鼠标位置
	GetCursorPos(&p);
	//转换鼠标左边为 该窗口的实际坐标
	ScreenToClient(m_hWnd, &p);
	*x = p.x;
	*y = p.y;

	RECT r;
	GetClientRect(m_hWnd, &r);

	return TRUE == PtInRect(&r, p);
}