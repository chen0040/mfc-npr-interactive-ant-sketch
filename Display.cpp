#include "StdAfx.h"
#include "Display.h"
#include "MainFrm.h"
#include "SketcherView.h"
#include "SketcherDoc.h"

Display* Display::m_pInstance=NULL;
bool Display::m_bSingletonFlag=false;

Display::Display(void)
: m_pView(NULL)
, m_pDoc(NULL)
, m_pMainFrm(NULL)
{
	m_outfile.open("debug.txt");
}

Display::~Display(void)
{
	m_outfile.close();
}

Display& Display::Instance()
{
	if(m_bSingletonFlag==false)
	{
		m_pInstance=new Display();
		m_bSingletonFlag=true;
	}

	return *m_pInstance;
}

std::ofstream& Display::operator << (const char* pMessage)
{
	m_outfile << pMessage; 

	return m_outfile;
}

void Display::SetMainFrame(CMainFrame* pMainFrm)
{
	m_pMainFrm=pMainFrm;
}

void Display::SetStatusText(LPCTSTR pMessage)
{
	ASSERT(m_pMainFrm);

	m_pMainFrm->SetStatusText(pMessage);
}

void Display::SetView(CSketcherView* pView)
{
	m_pView=pView;
}

void Display::SetDoc(CSketcherDoc* pDoc)
{
	m_pDoc=pDoc;
}
void Display::InvalidateView(BOOL bErased)
{
	m_pView->Invalidate(bErased);
	m_pView->UpdateWindow();
}

void Display::SetViewText(LPCTSTR pText)
{
	m_pView->SetViewText(pText);
}

void Display::ClearViewText(void)
{
	m_pView->ClearViewText();
}
