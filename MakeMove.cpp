#include "MakeMove.h"

CMove::CMove()
:
m_Length(0),
m_Rep(-1),
m_x(-1),
m_y(-1),
TX(0),
BJTX(0),
m_level(0),
m_Hit(0),
m_frcMove(-1),
m_morHit(0)
{	
}
CMove::~CMove()
{}

//添加动作帧
void CMove::AddFrame(char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy, int mx, int my)
{
	m_Move[m_Length]._ContinueFrame = CF;	//设置该图片的持续帧
	m_Move[m_Length]._PID = pid;			//图片路径
	m_Move[m_Length]._Bigx = bigx;			//缩放
	m_Move[m_Length]._Bigy = bigy;
	m_Move[m_Length]._site = site;			//位置属性
	m_Move[m_Length]._PRect._x1 = x1;		//人物矩形
	m_Move[m_Length]._PRect._y1 = y1;
	m_Move[m_Length]._PRect._x2 = x2;
	m_Move[m_Length]._PRect._y2 = y2;
	m_Move[m_Length]._x = x;				//锚点
	m_Move[m_Length]._y = y;
	m_Move[m_Length]._mx=mx;//技能位移
	m_Move[m_Length]._my=my;
	//-1为无数据 此处必须赋值
	m_Move[m_Length]._ARLength = 0;
	m_Move[m_Length]._DRLength = 0;
	m_Move[m_Length]._TX = -1;				//特效ID
	m_Move[m_Length]._skdata = -1;			//技能ID
	m_Move[m_Length]._BJTX = -1;			//背景特效ID
	m_Move[m_Length]._BackSkill = -1;		//后续技能ID
	m_Length++;
}

//修改动作帧
void CMove::SetFrame(int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy)
{
	m_Move[f]._ContinueFrame = CF;	//设置该图片的持续帧
	m_Move[f]._PID = pid;			//图片路径
	m_Move[f]._Bigx = bigx;			//缩放
	m_Move[f]._Bigy = bigy;
	m_Move[f]._site = site;			//位置属性
	m_Move[f]._PRect._x1 = x1;		//人物矩形
	m_Move[f]._PRect._y1 = y1;
	m_Move[f]._PRect._x2 = x2;
	m_Move[f]._PRect._y2 = y2;
	m_Move[f]._x = x;				//锚点
	m_Move[f]._y = y;
	//-1为无数据 此处必须赋值
	m_Move[f]._TX = -1;				//特效ID
	m_Move[f]._skdata = -1;			//技能ID
	m_Move[f]._BJTX = -1;			//背景特效ID
	m_Move[f]._BackSkill = -1;		//后续技能ID
}

//添加特效
void CMove::AddTX(int f, int tx)
{
	m_Move[f]._TX = tx;
}

//添加背景特效
void CMove::AddBJTX(int f, int tx)
{
	m_Move[f]._BJTX = tx;
}

//添加招式数据ID
void CMove::AddSkillData(int f, int id)
{
	m_Move[f]._skdata = id;
}

//添加帧攻击矩形
void CMove::AddActRect(int f, float x1, float y1, float x2, float y2)
{
	int iTmp = m_Move[f]._ARLength++;
	m_Move[f]._ActRect[iTmp]._x1 = x1;
	m_Move[f]._ActRect[iTmp]._x2 = x2;
	m_Move[f]._ActRect[iTmp]._y1 = y1;
	m_Move[f]._ActRect[iTmp]._y2 = y2;
	m_Move[f]._ActRect[iTmp]._pz = 1;
	m_Move[f]._ActRect[iTmp]._wd = 0;
}

//添加帧防御矩形
void CMove::AddDefRect(int f, float x1, float y1, float x2, float y2, int pz, int wd)
{
	int iTmp = m_Move[f]._DRLength++;
	m_Move[f]._DefRect[iTmp]._x1 = x1;
	m_Move[f]._DefRect[iTmp]._x2 = x2;
	m_Move[f]._DefRect[iTmp]._y1 = y1;
	m_Move[f]._DefRect[iTmp]._y2 = y2;
	m_Move[f]._DefRect[iTmp]._pz = pz;
	m_Move[f]._DefRect[iTmp]._wd = wd;
}

//得到攻击矩形
MyRect* CMove::GetActRect(int f)
{
	return m_Move[f]._ActRect;
}

//得到防御矩形
MyRect* CMove::GetDefRect(int f)
{
	return m_Move[f]._DefRect;
}

//得到攻击矩形长度
int CMove::GetActRectLen(int f)
{
	return m_Move[f]._ARLength;
}
//得到防御矩形长度
int CMove::GetDefRectLen(int f)
{
	return m_Move[f]._DRLength;
}

//得到动作图长度
int CMove::GetLength()
{
	return m_Length;
}

//设置重复动作起始帧
bool CMove::SetRep(int f)
{
	if(f >= m_Length)
		return false;
	m_Rep = f;
	return true;
}

//得到动作重复起始帧
int CMove::GetRep()
{
	return m_Rep;
}

//得到该帧持续时长
int CMove::GetContinueFrame(int f)
{
	return m_Move[f]._ContinueFrame;
}

//得到后续技能
int CMove::GetBackSkill(int f)
{
	return m_Move[f]._BackSkill;
}

//得到补正
int CMove::GetX(int f)
{
	return m_Move[f]._mx;
}
int CMove::GetY(int f)
{
	return m_Move[f]._my;
}

//得到图片ID
char* CMove::GetMoveP(int f)
{
	return m_Move[f]._PID;
}

//得到图片XY
float CMove::GetPX1(int f)
{
	return m_Move[f]._PRect._x1;
}
float CMove::GetPX2(int f)
{
	return m_Move[f]._PRect._x2;
}
float CMove::GetPY1(int f)
{
	return m_Move[f]._PRect._y1;
}
float CMove::GetPY2(int f)
{
	return m_Move[f]._PRect._y2;
}

//得到动作位移
int CMove::GetMX(int f)
{
	return m_Move[f]._mx;
}
int CMove::GetMY(int f)
{
	return m_Move[f]._my;
}

//得到图片缩放
int CMove::GetBigX(int f)
{
	return m_Move[f]._Bigx;
}

int CMove::GetBigY(int f)
{
	return m_Move[f]._Bigy;
}

float CMove::GetMoveX(int f)
{
	return m_Move[f]._x;
}
float CMove::GetMoveY(int f)
{
	return m_Move[f]._y;
}
void CMove::SetMoveX(int f,int x)
{
	m_Move[f]._x=x;
}
void CMove::SetMoveY(int f,int y)
{
	m_Move[f]._y=y;
}
//设置接续动作
void CMove::SetNextMove(int id)
{
	m_NextMove = id;
}
//得到接续动作ID
int CMove::GetNextMove()
{
	return m_NextMove;
}

//得到后续技能ID
int CMove::GetBackSkillID(int f)
{
	return m_Move[f]._BackSkill;
}

//得到该帧位置属性
int CMove::GetSite(int f)
{
	return m_Move[f]._site;
}

//设置位置属性
void CMove::SetSite(int f, int zt)
{
	m_Move[f]._site = zt;
}


//特效位置
void CMove::InitTX(float x, float y)
{
	m_x = x;
	m_y = y;
}

void CMove::InitBJTX(int zl)
{
	m_x = 0;
	m_y = 0;
	BJTX = zl;
}

void CMove::SetTX(float x, float y)
{
	m_x = x;
	m_y = y;
}

float CMove::GetTX_x()
{
	return m_x;
}
float CMove::GetTX_y()
{
	return m_y;
}

int CMove::GetBJTXID(int f)
{
	return m_Move[f]._BJTX;
}

int CMove::GetTXID(int f)
{
	return m_Move[f]._TX;
}

int CMove::GetTXLX()
{
	return TX;
}

int CMove::GetBJTXLX()
{
	return BJTX;
}

void CMove::SetTXLX(int tx)
{
	TX = tx;
}

//得到技能数据ID
int CMove::GetSkillDataID(int f)
{
	return m_Move[f]._skdata;
}

//动作相关
void CMove::SetMoveLevel(int level)
{
	m_level = level;
}
void CMove::SetmorHit(int mor)
{
	m_morHit = mor;
}

void CMove::SetFRCMove(int Move)
{
	m_frcMove = Move;
}
int CMove::GetMoveLevel()
{
	return m_level;
}
int CMove::GetmorHit()
{
	return m_morHit;
}

int CMove::GetFRCMove()
{
	return m_frcMove;
}

//----------------------------------


CMoves::CMoves()
:
m_movLen(0),
m_movMax(1024)
{
	for(int i = 0; i < m_movMax; ++i)
		m_Moves[i].SetRep(-1);
}

CMoves::~CMoves()
{}

////扩容
//void CMoves::movExpand()
//{
//	int iTmp = m_movMax;
//	m_movMax *= 2;
//	
//	CMove *pm = new CMove[iTmp];
//
//	for(int i = 0; i < iTmp; ++i)
//		pm[i] = m_Moves[i];
//
//	delete []m_Moves;
//	m_Moves = new CMove[m_movMax];
//
//	for(int j = 0; j < iTmp; ++j)
//		m_Moves[j] = pm[j];
//
//	delete []pm;
//}

//void CMoves::arExpand()
//{
//	int iTmp = m_arMax;
//	m_arMax *= 2;
//
//	MyRect *pr = new MyRect[iTmp];
//
//	for(int i = 0; i < iTmp; ++i)
//		pr[i] = m_ActRec[i];
//
//	delete []m_ActRec;
//	m_ActRec = new MyRect[m_arMax];
//
//	for(int j = 0; j < iTmp; ++j)
//		m_ActRec[j] = pr[j];
//
//	delete []pr;
//}

//void CMoves::drExpand()
//{
//	int iTmp = m_drMax;
//	m_drMax *= 2;
//
//	MyRect *pr = new MyRect[iTmp];
//
//	for(int i = 0; i < iTmp; ++i)
//		pr[i] = m_DefRec[i];
//
//	delete []m_DefRec;
//	m_DefRec = new MyRect[m_drMax];
//
//	for(int j = 0; j < iTmp; ++j)
//		m_DefRec[j] = pr[j];
//
//	delete []pr;
//}

//构成动作
void CMoves::AddMove(CMove mv)
{
	m_Moves[m_movLen++] = mv;

	//if(m_movLen == m_movMax)
		//movExpand();
}
bool CMoves::AddFrame(int id, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y,int mx, int my, int site, int bigx, int bigy)
{
	if(id < m_movLen || id > m_movMax)
		return false;
	m_Moves[id].AddFrame(pid, x1, y1, x2, y2, CF, x, y, site, bigx, bigy, mx, my);
	return true;
}

void CMoves::SetFrame(int id, int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy)
{
	if(id < m_movLen || id > m_movMax)
		return;
	m_Moves[id].SetFrame(f, pid, x1, y1, x2, y2, CF, x, y, site, bigx, bigy);
	return;
}

//添加特效
bool CMoves::AddTX(int id, int f, int tx)
{
	if(id < m_movLen || id > m_movMax)
		return false;
	m_Moves[id].AddTX(f, tx);
	return true;
}

//添加背景特效
bool CMoves::AddBJTX(int id, int f, int tx)
{
	if(id < m_movLen || id > m_movMax)
		return false;
	m_Moves[id].AddBJTX(f, tx);
	return true;
}

//添加招式数据ID
bool CMoves::AddSkillData(int id, int f, int data)
{
	if(id < m_movLen || id > m_movMax)
		return false;
	m_Moves[id].AddSkillData(f, data);
	return true;
}

//添加攻击矩形
void CMoves::AddActRect(int id, int f, float x1, float y1, float x2, float y2)
{
	m_Moves[id].AddActRect(f, x1, y1, x2, y2);
}

//添加防御矩形
void CMoves::AddDefRect(int id, int f, float x1, float y1, float x2, float y2, int pz, int wd)
{
	m_Moves[id].AddDefRect(f, x1, y1, x2, y2, pz, wd);
}

//得到单帧攻击矩形
MyRect* CMoves::GetActRect(int id, int f)
{
	return m_Moves[id].GetActRect(f);
}

//得到单帧防御矩形
MyRect* CMoves::GetDefRect(int id, int f)
{
	return m_Moves[id].GetDefRect(f);
}

//得到图片XY
float CMoves::GetPX1(int id, int f)
{
	return m_Moves[id].GetPX1(f);
}
float CMoves::GetPX2(int id, int f)
{
	return m_Moves[id].GetPX2(f);
}
float CMoves::GetPY1(int id, int f)
{
	return m_Moves[id].GetPY1(f);
}
float CMoves::GetPY2(int id, int f)
{
	return m_Moves[id].GetPY2(f);
}
int CMoves::GetMX(int id, int f)
{
	return m_Moves[id].GetMX(f);
}
int CMoves::GetMY(int id, int f)
{
	return m_Moves[id].GetMY(f);
}
//得到位置补正
int CMoves::GetX(int id, int f)
{
	return m_Moves[id].GetX(f);
}
int CMoves::GetY(int id, int f)
{
	return m_Moves[id].GetY(f);
}
//设置角色全部动作长度
void CMoves::SetMoveLength(int len)
{
	m_movLen = len;
}

//得到角色全部动作长度
int CMoves::GetMoveLength()
{
	return m_movLen;
}

//得到动作帧长度
int CMoves::GetFrameLen(int id)
{
	return m_Moves[id].GetLength();
}

//得到该帧持续时长
int CMoves::GetContinueFrame(int id, int f)
{
	return m_Moves[id].GetContinueFrame(f);
}

//得到单帧攻击矩形长度
int CMoves::GetActLength(int id, int f)
{
	return m_Moves[id].GetActRectLen(f);
}

//得到单帧防御矩形长度
int CMoves::GetDefLength(int id, int f)
{
	return m_Moves[id].GetDefRectLen(f);
}

//得到角色动作
CMove* CMoves::GetMove(int id)
{
	return &m_Moves[id];
}

//得到图片帧KEY
char* CMoves::GetMoveP(int id, int f)
{
	return m_Moves[id].GetMoveP(f);
}

//设置重复动作起始帧
bool CMoves::SetRep(int id, int f)
{
	return m_Moves[id].SetRep(f);
}

int CMoves::GetRep(int id)
{
	return m_Moves[id].GetRep();
}

//得到图片缩放
int CMoves::GetBigX(int id, int f)
{
	return m_Moves[id].GetBigX(f);
}

int CMoves::GetBigY(int id, int f)
{
	return m_Moves[id].GetBigY(f);
}

float CMoves::GetMoveX(int id, int f)
{
	return m_Moves[id].GetMoveX(f);
}
float CMoves::GetMoveY(int id, int f)
{
	return m_Moves[id].GetMoveY(f);
}
void CMoves::SetMoveX(int id, int f,int x)
{
	m_Moves[id].SetMoveX(f,x);
}
void CMoves::SetMoveY(int id, int f,int y)
{
	m_Moves[id].SetMoveY(f,y);
}
//设置接续动作
bool CMoves::SetNextMove(int id, int mid)
{
	if(mid < 0)
		return false;
	m_Moves[id].SetNextMove(mid);
	return true;
}

	//得到接续动作ID
int CMoves::GetNextMove(int id)
{
	return m_Moves[id].GetNextMove();
}

//得到后续技能ID
int CMoves::GetBackSkillID(int id, int f)
{
	return m_Moves[id].GetBackSkillID(f);
}

//得到该帧位置属性
int CMoves::GetSite(int id, int f)
{
	return m_Moves[id].GetSite(f);
}

//void CMoves::SetZT(int id, int zt)
//{
//	m_Moves[id].SetZT(zt);
//}
//int CMoves::GetZT(int id)
//{
//	return m_Moves[id].GetZT();
//}

//特效位置
void CMoves::InitTX(int id, int zl , float x, float y)
{
	m_Moves[id].SetTXLX(zl);
	m_Moves[id].InitTX(x, y);
}

void CMoves::InitBJTX(int id, int zl)
{
	m_Moves[id].InitBJTX(zl);
}

void CMoves::SetTX(int id, float x, float y)
{
	m_Moves[id].SetTX(x, y);
}

float CMoves::GetTX_x(int id)
{
	return m_Moves[id].GetTX_x();
}
float CMoves::GetTX_y(int id)
{
	return m_Moves[id].GetTX_y();
}

int CMoves::GetTXID(int id, int f)
{
	return m_Moves[id].GetTXID(f);
}

int CMoves::GetTXLX(int id)
{
	return m_Moves[id].GetTXLX();
}

int CMoves::GetBJTXID(int id, int f)
{
	return m_Moves[id].GetBJTXID(f);
}

int CMoves::GetBJTXLX(int id)
{
	return m_Moves[id].GetBJTXLX();
}

//得到技能数据ID
int CMoves::GetSkillDataID(int id, int f)
{
	return m_Moves[id].GetSkillDataID(f);
}

//动作相关

//设置动作等级
void CMoves::SetMoveLevel(int id, int level)
{
	m_Moves[id].SetMoveLevel(level);
}
//设置HIT数
void CMoves::SetmorHit(int id, int mor)
{
	m_Moves[id].SetmorHit(mor);
}

void CMoves::SetFRCMove(int id, int Move)
{
	m_Moves[id].SetFRCMove(Move);
}
int CMoves::GetMoveLevel(int id)
{
	return m_Moves[id].GetMoveLevel();
}
int CMoves::GetmorHit(int id)
{
	return m_Moves[id].GetmorHit();
}
int CMoves::GetFRCMove(int id)
{
	return m_Moves[id].GetFRCMove();
}

void CMoves::SetMoveData(int id, int level, int move, int mor)
{
	m_Moves[id].SetMoveLevel(level);
	m_Moves[id].SetmorHit(mor);
	m_Moves[id].SetFRCMove(move);
}