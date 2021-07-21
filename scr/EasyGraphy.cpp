#include"EasyGraphy.h"

bool RectCheck(int al, int at, int ar, int ab, int bl, int bt, int br, int bb)
{
	return !(ar < bl || ab < bt || bb < at || br < al);
}

//clr ΪBGR 0 < alpha < 255
void AlphaRectangle(int l, int t, int r, int b, DWORD clr, DWORD alpha)
{
	DWORD* pbImg = GetImageBuffer();

	DWORD fclr = BGRtoARGB(clr);

	alpha = inRange(alpha, 0, 255);

	int hw = getwidth();

	int rr = min(r, hw);
	int rb = min(b, getheight());

	for (int i = max(l, 0); i < rr; i++)
	{
		for (int j = max(t, 0); j < rb; j++)
		{
			pbImg[DW(j, i, hw)] = AlphaCocula(pbImg[DW(j, i, hw)], fclr, alpha);
		}
	}
}

void PutImgWithout(IMAGE* obj, int px, int py, DWORD* pbWnd, COLORREF withouter)
{
	int wX = getwidth();
	int wY = getheight();
	DWORD bitsub = 0x00FFFFFF;
	DWORD* pbImg = GetImageBuffer(obj);
	int iX = obj->getwidth();
	int iY = obj->getheight();
	int ofy = 0, ofx = 0;

	int sX = min(iX, wX - px);
	int sY = min(iY, wY - py);

	if (px < 0)ofx = -px;
	if (py < 0)ofy = -py;

	for (int i1 = ofx; i1 < sX; i1++)
	{
		for (int i2 = ofy; i2 < sY; i2++)
		{
			if ((pbImg[DW(i2, i1, iX)] & bitsub) == BGR(withouter))continue;	// ����Ƿ�Ҫ�ų�����ɫ

			pbWnd[DW(i2 + py, i1 + px, wX)] = pbImg[DW(i2, i1, iX)]; // �����Դ�
		}
	}
}