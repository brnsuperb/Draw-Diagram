
// Diagram.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CDiagramApp:
// � ���������� ������� ������ ��. Diagram.cpp
//

class CDiagramApp : public CWinApp
{
public:
	CDiagramApp();
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CDiagramApp theApp;