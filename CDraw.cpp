

#include "stdafx.h"
#include "CDraw.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "CSector.h"



#include "Diagram.h"
#include "DiagramDlg.h"
#include "afxdialogex.h"


using namespace std;

CDraw::CDraw(CWnd *pWnd):CPaintDC(pWnd)
{}
	
CDraw::~CDraw(){}


int CDraw::iOpenDataFile()
{
	ifstream fInputData("input.dat");
	vector<string> aPartOfDiagramProcent;
	vector<string> aPartOfDiagramName;
	vector<string> aPartOfDiagramColor;
	char cDelim[] = " .,;";
	char *pPartSize = new char[10];
	char *pPartColor = new char[20];
	char *pPartName = new char[20];
	char *cNewString = new char[20];
	string sHelpString = "";
	if (fInputData.is_open())//Если удалось открыть файл
	{
		string sInput;
		getline(fInputData, sInput);//Считываем название диаграммы
		sNameOfDiagram = sInput;

		//Считываем массив процентов
		getline(fInputData, sInput);
		//Разбиваем строку на отдельные лексемы

		strcpy(cNewString,  sInput.c_str());
		pPartSize = strtok(cNewString, ",");
		
		while (pPartSize != NULL)
		{
			aPartOfDiagramProcent.push_back(pPartSize);
			pPartSize = strtok(NULL, cDelim);
		}


		//Считываем массив подписей секторов
		getline(fInputData, sInput);
		strcpy(cNewString, sInput.c_str());
		pPartColor = strtok(cNewString, cDelim);

		while (pPartColor != NULL)
		{
			aPartOfDiagramColor.push_back(pPartColor);
			pPartColor = strtok(NULL, cDelim);
		}

		//Считываем массив цветов
		getline(fInputData, sInput);
		strcpy(cNewString, sInput.c_str());
		pPartName = strtok(cNewString, cDelim);

		while (pPartName != NULL)
		{
			aPartOfDiagramName.push_back(pPartName);
			pPartName = strtok(NULL, cDelim);
		}
		fInputData.close();
	}
	else
	{
		return 1;
	}

	string sHelp = "";
	for (int i = 0; i < aPartOfDiagramColor.size(); i++)
	{
		CSector CObj;
		sHelp = aPartOfDiagramProcent[i];
		CObj.dSizeOfSector = atof(sHelp.c_str());
		CObj.sNameOfSector = aPartOfDiagramName[i];
		CObj.sColorOfSector = aPartOfDiagramColor[i];
		aSectors.push_back(CObj);
	}
	ofstream oFile;
	oFile.open("output.dat");
	oFile << aSectors.size() << endl;
	oFile.close();
	return 0;
}

bool CDraw::bSector()
{
	for (int i = 0; i < aSectors.size(); i++)
	{
		CSector CHelp = aSectors[i];
		double dPart = CHelp.dSizeOfSector;
		double dResultSize = dPart * 360 / 100;
		aAngles[i] = dResultSize;
	}
	return true;
}