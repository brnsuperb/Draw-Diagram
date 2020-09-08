
// DiagramDlg.cpp : файл реализации
//


#include "stdafx.h"
#include "Diagram.h"
#include "DiagramDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "CDraw.h"
#include "GdiPlus.h"
#include "Paint.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CDiagramDlg



CDiagramDlg::CDiagramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiagramDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiagramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDiagramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// обработчики сообщений CDiagramDlg

BOOL CDiagramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDiagramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDiagramDlg::OnPaint()
{
	CDraw dc(this);
	int i = dc.iOpenDataFile();
	if (i != 0)
	{
		//Если не удалось открыть файл
		AfxMessageBox(_T("Error! Can't open the input file"));
	}

	bool bFlag = dc.bSector();
	if (!bFlag)
	{
		//Exception
		AfxMessageBox(_T("Error! Incorrect input data!\nPlease fix the input data file"));
	}


	//Основной эллипс
	CRect rect;
	GetClientRect(&rect);
	Paint CPainter(dc.m_hDC);
	CPainter.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	//SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
	//CPainter.SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);
	int iWindWidth = rect.Width() / 2;//Половина ширины окна
	int iWindHeight = rect.Height() / 2;//Половина высоты окна
	int iMainEllipseDiameter = 350;//Диаметр всей диаграммы
	CPainter.DrawMainEllipse(iWindWidth - (iMainEllipseDiameter/2), iWindHeight - (iMainEllipseDiameter/2), iMainEllipseDiameter);

	double dSummAngle = 0;
	int iWidthOfSector = 350; //Толщина бублика
	for (int i = 0; i < dc.aSectors.size(); i++)
	{
		string sNameOfPart = dc.aSectors[i].sNameOfSector;
		string sSectorSize = to_string(dc.aSectors[i].dSizeOfSector);
		int iIndex = sSectorSize.find(".");
		sNameOfPart = sNameOfPart + "\n" + sSectorSize.substr(0, iIndex + 2) + " " + "%";
		unsigned int uiNameLength = sNameOfPart.length() + 1;
		char *pName = new char[uiNameLength];
		strcpy(pName, sNameOfPart.c_str());
		wchar_t *pNewName = new wchar_t[uiNameLength];
		MultiByteToWideChar(CP_ACP, 0, pName, -1, (LPWSTR)pNewName, uiNameLength);
		CPainter.DrawSector(dc.aAngles[i], dSummAngle, dc.aSectors[i].sColorOfSector, rect.Width() / 2 - (iWidthOfSector / 2), rect.Height() / 2 - (iWidthOfSector / 2), iWidthOfSector, iWidthOfSector, pNewName);
		dSummAngle += dc.aAngles[i];
	}

	int iSecondaryEllipseDiameter = 200;//Диаметр внутреннего эллипса
	CPainter.DrawSecondaryEllipse(iWindWidth - (iSecondaryEllipseDiameter/2), iWindHeight - (iSecondaryEllipseDiameter/2), iSecondaryEllipseDiameter);

	//Название диаграммы
	string sDiagramName = dc.sNameOfDiagram;
	if (sDiagramName.length() > 15)
	{
		if (sDiagramName[15] != ' ')
		{
			sDiagramName = sDiagramName.substr(0, 14) + "-" + sDiagramName.substr(14, sDiagramName.length() - 1);
		}
		sDiagramName = sDiagramName.substr(0, 15) + "\n" + sDiagramName.substr(15, sDiagramName.length() - 1);
	}
	unsigned int uiNameLength = sDiagramName.length() + 1;
	char *pName = new char[uiNameLength];
	strcpy(pName, sDiagramName.c_str());
	wchar_t *pNewName = new wchar_t[uiNameLength];
	MultiByteToWideChar(CP_ACP, 0, pName, -1, (LPWSTR)pNewName, uiNameLength);
	CPainter.DrawMyText(pNewName, iWindWidth - 75, iWindHeight - 25);
	delete[] pName;
	delete[] pNewName;

	//Invalidate();
	UpdateWindow();

	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	
	


}



// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDiagramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

