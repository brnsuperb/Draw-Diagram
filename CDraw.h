#include <vector>
#include "CSector.h"
#include "Diagram.h"
#include "DiagramDlg.h"
#include "afxdialogex.h"

using namespace Gdiplus;
class CDraw: public CPaintDC{
public:
	CDraw(CWnd *pWnd);
	~CDraw();
	int iOpenDataFile();
	bool bSector();
	std::vector<CSector> aSectors;//Массив секторов екторов
	int iCountOfSectors = 0;
	std::string sNameOfDiagram;
	double aAngles[100];
};