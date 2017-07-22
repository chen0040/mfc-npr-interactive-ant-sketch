#pragma once
#include "afx.h"
#include <fstream>
#include <iostream>

class CMainFrame;
class CSketcherDoc;
class CSketcherView;

class Display :
	public CObject
{
private:
	Display(void);
	Display(const Display& rhs) { }
	Display& operator=(const Display& rhs) { return *this; }

public:
	~Display(void);
	static Display& Instance();

public:
	void SetMainFrame(CMainFrame* pMainFrm);
	void SetStatusText(LPCTSTR pMessage);
	void SetView(CSketcherView* pView);
	void SetDoc(CSketcherDoc* pDoc);

private:
	static Display* m_pInstance;
	static bool m_bSingletonFlag;
	CMainFrame* m_pMainFrm;
	CSketcherView* m_pView;
	CSketcherDoc* m_pDoc;
public:
	void InvalidateView(BOOL bErased=TRUE);
	void SetViewText(LPCTSTR pText);
	void ClearViewText(void);

public:
	std::ofstream& operator<< (const char* pMessage);

private:
	std::ofstream m_outfile;
};

#define gDisplay Display::Instance()

