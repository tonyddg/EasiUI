#pragma once
#include"EasyGraphic.h"
#include<set>

#define STS_DISABLE			-1//δ����(��������Ϣ������Ȼ��ͼ)
#define STS_NOCOMMAND		-2//�����������
#define STS_NONE			-3//������
#define STS_ERROR			-4//����
#define STS_OUT				-5//δ����Page��
#define STS_HIDE			-6//����
#define STS_DELETE			-7//�ȴ�ɾ��
#define STS_BEYOND			-8//�ڱ߽��⣨������ͼ���ڣ�
#define STS_UNPREPARED		-9//δ׼���õ�

#define STS_SET_DISABLE	0
#define STS_SET_HIDE	1
#define STS_SET_DELETE	2
#define STS_SET_REABLE	3

bool DrawCheck(int iState);
bool GetcommandCheck(int iState);
bool DeleteCheck(int iState);
void GetCurrentOrigin(std::pair<int, int> &piReceiveOrigin);
void SetCurrentOrigin(std::pair<int, int> piSetOrigin);

#define SIC_BASE	0
#define SIC_PAGE	1
#define SIC_BOTTOM	2
#define SIC_STR		3
#define SIC_SLIDE	4

class BaseStuff
{
	friend class Page;
	friend class ChooseBlock;

public:

	int GetRelPostionX();
	int GetRelPostionY();

	int GetState();

	virtual void ReRelPostion(int iRelPostionXG, int iRelPostionYG);

	//����STS_SET_ ʹ��ʱȷ��Ŀ������Page��
	bool SetState(int iSetStateG);

	//����Ϊǿ������״̬������������Ļ���ֹͣ
	void SetKeepRun(bool blKeepRunG);

	virtual ~BaseStuff();

protected:

	int iRelPostionX;
	int iRelPostionY;
	int iStuffW;
	int iStuffH;

	int iStuffState;

	int iDefultState;

	bool blKeepRun;

	int iIdentityCode;

	virtual void GetCommand(ExMessage* m, bool blValidChoosed);
	virtual void Draw();

};

struct StuffPoint
{
	BaseStuff* lpStuffPoint;
	int iPriorityLevel;

	StuffPoint(BaseStuff * lpStuffPointG, int iPriorityLevelG);
};

bool operator> (StuffPoint a, StuffPoint b);
bool operator< (StuffPoint a, StuffPoint b);

class Page: public BaseStuff
{
public:

	Page(int iRelPostionXG, int iRelPostionYG, int iStuffWG, int iStuffHG, DWORD dwBackgroundClrG, bool blIsTransparentG, bool blKeepRunG, bool blAbsDealG, bool blAutoFlushG);

	bool Insert(BaseStuff * lpInsertStuffG, int iPriorityLevelG);
	void GetCommand(ExMessage* m, bool blValidChoosed);
	void Draw();

	virtual void Flush();
	virtual void StateFlush();//����Page�е���Stuff��������״̬��������GetCommand�У������ɾ��ʧ�������ȱʧ��BEYOND��DELETE�޷�ʵʱִ�У����ƶ�Pageʱ����ʹ�ã�ʱ����ʹ��

protected:

	std::set<StuffPoint> setStuffinPage;

	bool blAutoFlush;//�Ƿ��Զ�ˢ�� ������ģʽ����Ч
	bool blAbsDeal;//����ģʽ���������iStuffW��iStuffH�ڵ�������Ա���ʾ��������blKeepRun����Ȼ���У�����߽���Ĳ�����Ȼ�޷���ʾ
	bool blIsTransparent;
	DWORD dwBackgroundClr;

	IMAGE imgCacheDisplay;
};

#define STS_BS_UNCHOOSED	1
#define STS_BS_CHOOSED		2
#define STS_BS_CLICKED		3
#define STS_BS_RELEASE		4

class BottomStuff: public BaseStuff
{
public:

	BottomStuff(int iRelPostionXG, int iRelPostionYG, IMAGE * lpBottomIconG, DWORD dwChoosedClrG, DWORD dwChoosedAlpG, DWORD dwClickClrG, DWORD dwClickAlpG, bool blKeepRunG);

	void FlushWH();

private:

	IMAGE* lpBottomIcon;

	DWORD dwChoosedClr;
	DWORD dwChoosedAlp;

	DWORD dwClickClr;
	DWORD dwClickAlp;

	void GetCommand(ExMessage* m, bool blValidChoosed);
	void Draw();
};

class StrStuff : public BaseStuff
{
public:

	StrStuff(int iRelPostionXG, int iRelPostionYG, int iStuffWG, int iStuffHG, TCHAR * lpDisplayStrG, DWORD dwBackgroundClrG, DWORD dwTextClrG, int iWordSizeG, UINT uFormatG, bool blIsTransparentG, bool blAutoFlushG, bool blKeepRunG);

	void Flush();

private:

	TCHAR* lpDisplayStr;
	bool blIsTransparent;
	DWORD dwBackgroundClr;
	DWORD dwTextClr;
	int iWordSize;
	UINT uFormat;

	bool blAutoFlush;

	IMAGE imgCacheDisplay;

	//void GetCommand(ExMessage* m);
	void Draw();
};

#define STS_SL_UNCHOOSED	1
#define STS_SL_CHOOSED		2
#define STS_SL_HOLD			3

class SlideStuff : public BaseStuff
{
	friend class ChooseBlock;

public:

	SlideStuff(int iRelPostionXG, int iRelPostionYG, int iStuffWG, int iStuffHG, int iSlideLengthG, int iSlideWidthG, int iMaxValueG, DWORD dwBackgroundClrG, DWORD dwSlideClrG, DWORD dwPassedClrG, int iHeadRadius, bool blIsTransparentG, bool blIsReverseG, bool blProcessModeG, bool blKeepRunG);

	int GetValue();
	bool SetValue(int iPreValueG);

	bool SetMaxValue(int iMaxValueG);

private:

	int iSlideLength;// ����Ҫ�� iStuffH >= iSlideLength �� iStuffWidth >= iSlideLength >= iHeadRadius ���� ״̬Ϊ ERROE
	int iSlideWidth;
	int iMaxValue;
	int iPreValue;

	int iMidPositionX;
	int iMidPositionY;
	double dLengthDivMaxvalue;
	int iHeadDivLDM;

	DWORD dwBackgroundClr;
	DWORD dwSlideClr;
	DWORD dwPassedClr;

	int iHeadRadius;

	bool blIsTransparent;
	bool blIsReverse;//true:��ֱģʽ false:ˮƽģʽ
	bool blProcessMode;//true:������ģʽ false:�����ģʽ ��ģʽ�� iHeadRadius Ϊ�ƶ����ĳ��� �˳��Ȱ�����iSlideLength dwPassedClr Ϊ�ƶ�������ɫ 

	int iLastMouse;

	int iPassedLength;

	void GetCommand(ExMessage* m, bool blValidChoosed);
	void Draw();
};