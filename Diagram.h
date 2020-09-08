
// Diagram.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDiagramApp:
// О реализации данного класса см. Diagram.cpp
//

class CDiagramApp : public CWinApp
{
public:
	CDiagramApp();
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDiagramApp theApp;