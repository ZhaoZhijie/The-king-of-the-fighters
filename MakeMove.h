/*
单帧攻击矩形不得超过10个
单帧防御矩形不得超过10个
*/

#ifndef MAKE_MOVE_H
#define MAKE_MOVE_H

struct MyRect
{
	// x1, y1 位置点偏移量, x2, y2 宽 高.
	float _x1, _y1, _x2, _y2;
	//是否参与阻挡判断
	int _pz;
	int _wd;
};

struct movep
{
	char	*_PID;			//动作图ID
	MyRect	_PRect;			//图片位置 也就是图片宽 高
	MyRect	_ActRect[16];	//攻击矩形
	MyRect 	_DefRect[16];	//防御矩形
	int		_ARLength;		//攻击矩形长度
	int		_DRLength;		//防御矩形长度
	int		_ContinueFrame;	//该图片持续帧
	int     _BackSkill;		//是否存在后续技能
	int		_Bigx;			//缩放比例x
	int		_Bigy;			//缩放比例y
	float   _x;				//该图片改变距离（锚点）
	float   _y;				//该图片改变距离
	int _mx;//技能位移
	int _my;
	int		_site;			//位置属性
	int		_TX;			//特效ID
	int		_TX_X;			//该特效的相对位置
	int		_TX_Y;			
	int     _BJTX;			//背景特效ID
	int		_skdata;		//技能数据ID
};

//仅为基础功能 改变矩形 插入帧动作 改图片等等功能以后补完

class CMove
{
	movep m_Move[70];	//动作 （图片 默认64张 一个动作最大64张图片表现）
	int m_Length;		//该动作长度
	int m_Rep;			//重复动作 如果此项有值，那么会从该图片开始 再播放此动作 反复不断
	int m_NextMove;		//动作结束后接续动作
	float m_x;			//该动作偏移量（也就是此动作会偏移角色位置）
	float m_y;
	int TX;				//特效ID
	int BJTX;
	int m_level;		//动作等级 主要表示攻击力度
	int m_Hit;			//命中标记
	int m_frcMove;		//可用取消特殊动作
	int m_morHit;		//复数伤害标记

public: 
	CMove();
	~CMove();

	//添加动作帧(也就是添加动作的图片)
	void AddFrame(char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy, int mx, int my);

	//修改动作帧(也就是添加动作的图片)
	void SetFrame(int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy);

	//添加特效
	void AddTX(int f, int tx);
	//添加背景特效
    void AddBJTX(int f, int tx);
	//添加招式数据ID
	void AddSkillData(int f, int id);
	//添加帧攻击矩形
	void AddActRect(int f, float x1, float y1, float x2, float y2);
	//添加帧防御矩形
	void AddDefRect(int f, float x1, float y1, float x2, float y2, int pz, int wd);

	//得到攻击矩形
	MyRect* GetActRect(int f);
	//得到防御矩形
	MyRect* GetDefRect(int f);
	//得到攻击矩形长度
	int GetActRectLen(int f);
	//得到防御矩形长度
	int GetDefRectLen(int f);

	//得到动作图长度
	int GetLength();

	//设置重复动作起始帧
	bool SetRep(int f);
	//得到动作重复起始帧
	int GetRep();

	//设置接续动作
	void SetNextMove(int id);
	//得到接续动作ID
	int GetNextMove();

	//得到后续技能ID
	int GetBackSkillID(int f);

	//得到该帧持续时长
	int GetContinueFrame(int f);
	//得到后续技能
	int GetBackSkill(int f);
	//得到位置补正
	int GetX(int f);
	int GetY(int f);

	//得到图片ID
	char* GetMoveP(int f);

	//得到图片XY
	float GetPX1(int f);
	float GetPX2(int f);
	float GetPY1(int f);
	float GetPY2(int f);
	//得到动作位移
	int GetMX(int f);
	int GetMY(int f);
	//得到图片缩放
	int GetBigX(int f);
	int GetBigY(int f);

	float GetMoveX(int f);
	float GetMoveY(int f);
	void SetMoveX(int f,int x);
	void SetMoveY(int f, int y);
	//得到该帧位置属性
	void SetSite(int f, int zt);
	int GetSite(int f);
	

	//特效位置
	void InitTX(float x, float y);
	void InitBJTX(int zl);
	void SetTX(float x, float y);
	void SetTXLX(int tx);
	float GetTX_x();
	float GetTX_y();

	int GetBJTXID(int f);
	int GetTXID(int f);
	
	//特效类型
	int GetTXLX();
	int GetBJTXLX();

	//得到技能数据ID
	int GetSkillDataID(int f);

	//动作相关
	void SetMoveLevel(int level);
	void SetmorHit(int mor);
	void SetFRCMove(int Move);
	int GetMoveLevel();
	int GetmorHit();
	int GetFRCMove();
};

//---------------------------------------------------------------------
class CMoves
{
	CMove m_Moves[3000];			//角色动作
	int m_movLen;			
	int m_movMax;

	//扩容
	//void movExpand();

public:
	CMoves();
	~CMoves();

	//构成动作
	void AddMove(CMove mv);
	bool AddFrame(int id, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int mx = 0, int my = 0, int site = 5, int bigx = 0, int bigy = 0);

	void SetFrame(int id, int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site = 5, int bigx = 0, int bigy = 0);
	//添加特效
	bool AddTX(int id, int f, int tx);
	//添加背景特效
	bool AddBJTX(int id, int f, int tx);
	//添加招式数据ID
	bool AddSkillData(int id, int f, int data);

	//添加攻击矩形
	void AddActRect(int id, int f, float x1, float y1, float x2, float y2);

	//添加防御矩形
	void AddDefRect(int id, int f, float x1, float y1, float x2, float y2, int pz = 1, int wd = 0);

	//得到单帧攻击矩形
	MyRect* GetActRect(int id, int f);

	//得到单帧防御矩形
	MyRect* GetDefRect(int id, int f);

	//得到图片XY
	float GetPX1(int id, int f);
	float GetPX2(int id, int f);
	float GetPY1(int id, int f);
	float GetPY2(int id, int f);
	//得到动作位移
	int GetMX(int id, int f);
	int GetMY(int id, int f);

	//得到位置补正
	int GetX(int id, int f);
	int GetY(int id, int f);

	//得到单帧攻击矩形长度
	int GetActLength(int id, int f);

	//得到单帧防御矩形长度
	int GetDefLength(int id, int f);

	//设置角色全部动作长度
	void SetMoveLength(int len);

	//得到角色全部动作长度
	int GetMoveLength();

	//得到动作帧长度
	int GetFrameLen(int id);

	//得到该帧持续时长
	int GetContinueFrame(int id, int f);

	//得到角色动作
	CMove* GetMove(int id);

	//得到图片帧KEY
	char* GetMoveP(int id, int f);

	//设置重复动作起始帧
	bool SetRep(int id, int f);

	//得到动作重复起始帧
	int GetRep(int id);

	//得到图片缩放
	int GetBigX(int id, int f);
	int GetBigY(int id, int f);

	float GetMoveX(int id, int f);
	float GetMoveY(int id, int f);
	void SetMoveX(int id , int f , int x); 
	void SetMoveY(int id  , int f , int y);
	//设置接续动作
	bool SetNextMove(int id, int mid);
	//得到接续动作ID
	int GetNextMove(int id);

	//得到后续技能ID
	int GetBackSkillID(int id, int f);

	//得到该帧位置属性
	int GetSite(int id, int f);

	void SetZT(int id, int zt);
	int GetZT(int id);

	//特效位置
	void InitTX(int id, int zl = 1, float x = 0, float y = 0);
	void InitBJTX(int id, int zl);
	void SetTX(int id, float x, float y);
	float GetTX_x(int id);
	float GetTX_y(int id);
	int GetTXLX(int id);
	int GetBJTXLX(int id);

	int GetTXID(int id, int f);
	int GetBJTXID(int id, int f);

	//得到技能数据ID
	int GetSkillDataID(int id, int f);

	//动作相关
	void SetMoveLevel(int id, int level);
	void SetmorHit(int id, int mor = 0);
	void SetFRCMove(int id, int Move);
	int GetMoveLevel(int id);
	int GetmorHit(int id);
	int GetFRCMove(int id);
	void SetMoveData(int id, int level, int move = -1, int mor = 0);
};
#endif