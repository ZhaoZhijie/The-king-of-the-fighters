/*
��֡�������β��ó���10��
��֡�������β��ó���10��
*/

#ifndef MAKE_MOVE_H
#define MAKE_MOVE_H

struct MyRect
{
	// x1, y1 λ�õ�ƫ����, x2, y2 �� ��.
	float _x1, _y1, _x2, _y2;
	//�Ƿ�����赲�ж�
	int _pz;
	int _wd;
};

struct movep
{
	char	*_PID;			//����ͼID
	MyRect	_PRect;			//ͼƬλ�� Ҳ����ͼƬ�� ��
	MyRect	_ActRect[16];	//��������
	MyRect 	_DefRect[16];	//��������
	int		_ARLength;		//�������γ���
	int		_DRLength;		//�������γ���
	int		_ContinueFrame;	//��ͼƬ����֡
	int     _BackSkill;		//�Ƿ���ں�������
	int		_Bigx;			//���ű���x
	int		_Bigy;			//���ű���y
	float   _x;				//��ͼƬ�ı���루ê�㣩
	float   _y;				//��ͼƬ�ı����
	int _mx;//����λ��
	int _my;
	int		_site;			//λ������
	int		_TX;			//��ЧID
	int		_TX_X;			//����Ч�����λ��
	int		_TX_Y;			
	int     _BJTX;			//������ЧID
	int		_skdata;		//��������ID
};

//��Ϊ�������� �ı���� ����֡���� ��ͼƬ�ȵȹ����Ժ���

class CMove
{
	movep m_Move[70];	//���� ��ͼƬ Ĭ��64�� һ���������64��ͼƬ���֣�
	int m_Length;		//�ö�������
	int m_Rep;			//�ظ����� ���������ֵ����ô��Ӹ�ͼƬ��ʼ �ٲ��Ŵ˶��� ��������
	int m_NextMove;		//�����������������
	float m_x;			//�ö���ƫ������Ҳ���Ǵ˶�����ƫ�ƽ�ɫλ�ã�
	float m_y;
	int TX;				//��ЧID
	int BJTX;
	int m_level;		//�����ȼ� ��Ҫ��ʾ��������
	int m_Hit;			//���б��
	int m_frcMove;		//����ȡ�����⶯��
	int m_morHit;		//�����˺����

public: 
	CMove();
	~CMove();

	//��Ӷ���֡(Ҳ������Ӷ�����ͼƬ)
	void AddFrame(char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy, int mx, int my);

	//�޸Ķ���֡(Ҳ������Ӷ�����ͼƬ)
	void SetFrame(int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site, int bigx, int bigy);

	//�����Ч
	void AddTX(int f, int tx);
	//��ӱ�����Ч
    void AddBJTX(int f, int tx);
	//�����ʽ����ID
	void AddSkillData(int f, int id);
	//���֡��������
	void AddActRect(int f, float x1, float y1, float x2, float y2);
	//���֡��������
	void AddDefRect(int f, float x1, float y1, float x2, float y2, int pz, int wd);

	//�õ���������
	MyRect* GetActRect(int f);
	//�õ���������
	MyRect* GetDefRect(int f);
	//�õ��������γ���
	int GetActRectLen(int f);
	//�õ��������γ���
	int GetDefRectLen(int f);

	//�õ�����ͼ����
	int GetLength();

	//�����ظ�������ʼ֡
	bool SetRep(int f);
	//�õ������ظ���ʼ֡
	int GetRep();

	//���ý�������
	void SetNextMove(int id);
	//�õ���������ID
	int GetNextMove();

	//�õ���������ID
	int GetBackSkillID(int f);

	//�õ���֡����ʱ��
	int GetContinueFrame(int f);
	//�õ���������
	int GetBackSkill(int f);
	//�õ�λ�ò���
	int GetX(int f);
	int GetY(int f);

	//�õ�ͼƬID
	char* GetMoveP(int f);

	//�õ�ͼƬXY
	float GetPX1(int f);
	float GetPX2(int f);
	float GetPY1(int f);
	float GetPY2(int f);
	//�õ�����λ��
	int GetMX(int f);
	int GetMY(int f);
	//�õ�ͼƬ����
	int GetBigX(int f);
	int GetBigY(int f);

	float GetMoveX(int f);
	float GetMoveY(int f);
	void SetMoveX(int f,int x);
	void SetMoveY(int f, int y);
	//�õ���֡λ������
	void SetSite(int f, int zt);
	int GetSite(int f);
	

	//��Чλ��
	void InitTX(float x, float y);
	void InitBJTX(int zl);
	void SetTX(float x, float y);
	void SetTXLX(int tx);
	float GetTX_x();
	float GetTX_y();

	int GetBJTXID(int f);
	int GetTXID(int f);
	
	//��Ч����
	int GetTXLX();
	int GetBJTXLX();

	//�õ���������ID
	int GetSkillDataID(int f);

	//�������
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
	CMove m_Moves[3000];			//��ɫ����
	int m_movLen;			
	int m_movMax;

	//����
	//void movExpand();

public:
	CMoves();
	~CMoves();

	//���ɶ���
	void AddMove(CMove mv);
	bool AddFrame(int id, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int mx = 0, int my = 0, int site = 5, int bigx = 0, int bigy = 0);

	void SetFrame(int id, int f, char *pid, float x1, float y1, float x2, float y2, int CF, float x, float y, int site = 5, int bigx = 0, int bigy = 0);
	//�����Ч
	bool AddTX(int id, int f, int tx);
	//��ӱ�����Ч
	bool AddBJTX(int id, int f, int tx);
	//�����ʽ����ID
	bool AddSkillData(int id, int f, int data);

	//��ӹ�������
	void AddActRect(int id, int f, float x1, float y1, float x2, float y2);

	//��ӷ�������
	void AddDefRect(int id, int f, float x1, float y1, float x2, float y2, int pz = 1, int wd = 0);

	//�õ���֡��������
	MyRect* GetActRect(int id, int f);

	//�õ���֡��������
	MyRect* GetDefRect(int id, int f);

	//�õ�ͼƬXY
	float GetPX1(int id, int f);
	float GetPX2(int id, int f);
	float GetPY1(int id, int f);
	float GetPY2(int id, int f);
	//�õ�����λ��
	int GetMX(int id, int f);
	int GetMY(int id, int f);

	//�õ�λ�ò���
	int GetX(int id, int f);
	int GetY(int id, int f);

	//�õ���֡�������γ���
	int GetActLength(int id, int f);

	//�õ���֡�������γ���
	int GetDefLength(int id, int f);

	//���ý�ɫȫ����������
	void SetMoveLength(int len);

	//�õ���ɫȫ����������
	int GetMoveLength();

	//�õ�����֡����
	int GetFrameLen(int id);

	//�õ���֡����ʱ��
	int GetContinueFrame(int id, int f);

	//�õ���ɫ����
	CMove* GetMove(int id);

	//�õ�ͼƬ֡KEY
	char* GetMoveP(int id, int f);

	//�����ظ�������ʼ֡
	bool SetRep(int id, int f);

	//�õ������ظ���ʼ֡
	int GetRep(int id);

	//�õ�ͼƬ����
	int GetBigX(int id, int f);
	int GetBigY(int id, int f);

	float GetMoveX(int id, int f);
	float GetMoveY(int id, int f);
	void SetMoveX(int id , int f , int x); 
	void SetMoveY(int id  , int f , int y);
	//���ý�������
	bool SetNextMove(int id, int mid);
	//�õ���������ID
	int GetNextMove(int id);

	//�õ���������ID
	int GetBackSkillID(int id, int f);

	//�õ���֡λ������
	int GetSite(int id, int f);

	void SetZT(int id, int zt);
	int GetZT(int id);

	//��Чλ��
	void InitTX(int id, int zl = 1, float x = 0, float y = 0);
	void InitBJTX(int id, int zl);
	void SetTX(int id, float x, float y);
	float GetTX_x(int id);
	float GetTX_y(int id);
	int GetTXLX(int id);
	int GetBJTXLX(int id);

	int GetTXID(int id, int f);
	int GetBJTXID(int id, int f);

	//�õ���������ID
	int GetSkillDataID(int id, int f);

	//�������
	void SetMoveLevel(int id, int level);
	void SetmorHit(int id, int mor = 0);
	void SetFRCMove(int id, int Move);
	int GetMoveLevel(int id);
	int GetmorHit(int id);
	int GetFRCMove(int id);
	void SetMoveData(int id, int level, int move = -1, int mor = 0);
};
#endif