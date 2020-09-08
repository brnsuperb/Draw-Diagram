#include "stdafx.h"
#include "Paint.h"


void Paint::DrawMainEllipse(int iX, int iY, int iDiameter)
{
	FillEllipse(new SolidBrush(Color::LightGray), RectF(iX, iY, iDiameter, iDiameter));
}


void Paint::DrawSecondaryEllipse(int iX, int iY, int iDiameter)
{
	FillEllipse(new SolidBrush(Color::White), RectF(iX, iY, iDiameter, iDiameter));
}


void Paint::DrawSector(double dLengthOfArc, double dStartAngle, string sColor, int iX, int iY, int iWidth, int iHeight, wchar_t *pName)
{
	REAL CLengthOfArc = 0.0f;
	CLengthOfArc += dLengthOfArc;
	REAL CStartAngle = 0.0f;
	CStartAngle += dStartAngle;
	
	char *pColor = new char[6];
	strcpy(pColor,sColor.c_str());
	char cPartOne[2], cPartTwo[2], cPartThree[2];
	cPartOne[0] = pColor[0];
	cPartOne[1] = pColor[1];
	cPartTwo[0] = pColor[2];
	cPartTwo[1] = pColor[3];
	cPartThree[0] = pColor[4];
	cPartThree[1] = pColor[5];
	

	int iR = strtol(cPartOne, NULL, 16);
	if (iR > 255) iR = 255;
	if (iR < 0) iR = 0;
	int iG = strtol(cPartTwo, NULL, 16);
	if (iG > 255) iG = 255;
	if (iG < 0) iG = 0;
	int iB = strtol(cPartThree, NULL, 16);
	if (iB > 255) iB = 255;
	if (iB < 0) iB = 0;

	int iRadius = 240;
	Color CColor(iR, iG, iB);
	FillPie(new SolidBrush(CColor), iX, iY, iWidth, iHeight, CStartAngle, CLengthOfArc);
	Font font(&FontFamily(L"Calibri"), 16);
	Status st = DrawString(pName, -1, &font, PointF(iX + (iRadius - 75) + (iRadius * cos(((CStartAngle + (CLengthOfArc/2)) * 3.14) / 180)), iY + (iRadius - 75) + (iRadius  * sin(((CStartAngle + (CLengthOfArc/2))* 3.14) / 180))), new SolidBrush(Color::Black));
}

void Paint::DrawMyText(wchar_t *pMyText, int iX, int iY)
{
	Font font(&FontFamily(L"Calibri"), 16);
	Status st = DrawString(pMyText, -1, &font, PointF(iX, iY), new SolidBrush(Color::Black));
}

Paint::Paint(HDC hdc) : Graphics(hdc){}
Paint::~Paint(){}