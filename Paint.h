#include "stdafx.h"
#include <string>

using namespace std;
class Paint : public Graphics{
public:
	Paint(HDC hdc);
	~Paint();
	void DrawMainEllipse(int iX, int iY, int iDiameter);
	void DrawSecondaryEllipse(int iX, int iY, int iDiameter);
	void DrawSector(double dLengthOfArc, double dStartAngle, string sColor, int iX, int iY, int iWidth, int iHeight, wchar_t *pName);
	void DrawMyText(wchar_t *pMyText, int iX, int iY);
};