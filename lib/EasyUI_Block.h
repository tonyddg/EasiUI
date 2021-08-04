#pragma once
#include"EasyUI.h"

#define LISTMAX		256
#define SHORTLIST	32

struct imgList
{
	IMAGE list[LISTMAX];//�ļ�����
	int top;//���г���

	imgList();
};

struct strList
{
	TCHAR list[LISTMAX][LISTMAX];//�ļ�����
	int top;//���г���

	strList();
};

class ChooseBlock: public Page
{
public:

	ChooseBlock(int iRelPostionXG, int iRelPostionYG, int iStuffWG, int iStuffHG, DWORD dwBackgroundClrG, bool blIsTransparentG, bool blKeepRunG);
	ChooseBlock(int iRelPostionXG, int iRelPostionYG, int iStuffWG, int iStuffHG, int iBottomWG, int iBottomHG, int iSlideWidthG, int iBottomGapG, DWORD dwSlideClrG, DWORD dwPassedClrG, imgList &ilImgListG, DWORD dwBackgroundClrG, DWORD dwChoosedClrG, DWORD dwChoosedAlpG, DWORD dwClickClrG, DWORD dwClickAlpG, bool blIsTransparentG, bool blKeepRunG);
	~ChooseBlock();

	void SetState_All(int iSetState);

	void GetCommand(ExMessage* m, bool blValidChoosed);
	void Draw();
	void Flush();

	bool GetActiveBottom(int &iReceiveNum);

	bool Rebase(int iBottomWG, int iBottomHG, int iSlideWidthG, int iBottomGapG, DWORD dwSlideClrG, DWORD dwPassedClrG, imgList *ilImgListG, DWORD dwChoosedClrG, DWORD dwChoosedAlpG, DWORD dwClickClrG, DWORD dwClickAlpG);

private:

	SlideStuff* lpSideSlide;

	int iBottomQuantity;
	int iBottomGap;
	int iListLength;
	int iBottomDis;

	int iActiveNum;
	int iLastOffset;

	bool blIsEmpty;
};