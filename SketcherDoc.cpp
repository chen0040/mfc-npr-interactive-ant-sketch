// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
#include "Sketcher.h"

#include "SketcherDoc.h"
#include "Display.h"
#include "DlgACConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_SKETCHER_SAVEIMAGE, &CSketcherDoc::OnSketcherSaveimage)
	ON_UPDATE_COMMAND_UI(ID_SKETCHER_SAVEIMAGE, &CSketcherDoc::OnUpdateSketcherSaveimage)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYSOURCE, &CSketcherDoc::OnUpdateImageDisplaysource)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYGRADIENTMAP, &CSketcherDoc::OnUpdateImageDisplaygradientmap)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYLUMINANCEMAP, &CSketcherDoc::OnUpdateImageDisplayluminancemap)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYCANVAS, &CSketcherDoc::OnUpdateImageDisplaycanvas)
	ON_UPDATE_COMMAND_UI(ID_SKETCHER_SKETCH, &CSketcherDoc::OnUpdateSketcherSketch)
	ON_COMMAND(ID_SKETCHER_OPTIONS, &CSketcherDoc::OnSketcherOptions)
	ON_COMMAND(ID_SKETCHER_CLEARCANVAS, &CSketcherDoc::OnSketcherClearcanvas)
	ON_COMMAND(ID_SKETCHER_BATCHRUN, &CSketcherDoc::OnSketcherBatchrun)
	ON_UPDATE_COMMAND_UI(ID_SKETCHER_BATCHRUN, &CSketcherDoc::OnUpdateSketcherBatchrun)
END_MESSAGE_MAP()


// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc()
: m_bRedrawCanvas(FALSE)
{
	// TODO: add one-time construction code here
	gDisplay.SetDoc(this);

	m_configuration.Load(_T("SketcherConfiguration.xml"));

	m_colony.Reset(&m_configuration);

}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc commands

bool CSketcherDoc::Load(LPCTSTR pFileName)
{
	if(!m_sketcher.Load(pFileName))
	{
		return false;
	}

	m_colony.Reset(&m_configuration);

	return true;
}

void CSketcherDoc::Display(CDC* pDC, const CRect& rect)
{
	if(m_sketcher.IsNull())
	{
		return;
	}

	m_sketcher.Display(pDC, rect);
}

void CSketcherDoc::OnSketcherSaveimage()
{
	// TODO: Add your command handler code here
	CFileDialog fdlg(FALSE, _T("bmp"), _T("result.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap File (*.bmp)|*.bmp|Jpeg File (*.jpg)|*.jpg|Gif File (*.gif)|*.gif|PNG File (*.png)|*.png|All Files (*.*)|*.*|"));

	if(fdlg.DoModal()==IDOK)
	{
		m_sketcher.Save(fdlg.GetPathName());
	}
}

void CSketcherDoc::OnUpdateSketcherSaveimage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CSketcherDoc::OnImageDisplaysource()
{
	// TODO: Add your command handler code here
	m_sketcher.SetDisplay(SketcherEngine::DISPLAY_SOURCE);
}

void CSketcherDoc::OnUpdateImageDisplaysource(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_sketcher.GetDisplay() == SketcherEngine::DISPLAY_SOURCE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CSketcherDoc::OnImageDisplaygradientmap(void)
{
	if(!m_sketcher.IsGradientMapImgAvailable())
	{
		gDisplay.SetStatusText(_T("Gradient Map does not exist. Create Gradient Map..."));
		gDisplay.SetViewText(_T("Gradient Map does not exist. Create Gradient Map..."));
		gDisplay.InvalidateView(FALSE);

		m_sketcher.CreateGradientMap();	

		m_sketcher.SetDisplay(SketcherEngine::DISPLAY_GRADIENT_MAP);
		gDisplay.ClearViewText();
		gDisplay.InvalidateView(FALSE);

		gDisplay.SetStatusText(_T("Gradient Map successfully created..."));
	}
	else
	{
		m_sketcher.SetDisplay(SketcherEngine::DISPLAY_GRADIENT_MAP);
		gDisplay.InvalidateView();
	}

	
}

void CSketcherDoc::OnUpdateImageDisplaygradientmap(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_sketcher.GetDisplay() == SketcherEngine::DISPLAY_GRADIENT_MAP)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CSketcherDoc::OnImageDisplayluminancemap(void)
{
	if(!m_sketcher.IsLuminanceMapImgAvailable())
	{
		gDisplay.SetStatusText(_T("Luminance Map does not exist. Create Luminance Map..."));

		gDisplay.SetViewText(_T("Luminance Map does not exist. Create Luminance Map..."));
		gDisplay.InvalidateView(FALSE);

		m_sketcher.CreateLuminanceMap();
		m_sketcher.SetDisplay(SketcherEngine::DISPLAY_LUMINANCE_MAP);

		gDisplay.ClearViewText();
		gDisplay.InvalidateView(FALSE);

		gDisplay.SetStatusText(_T("Luminance Map successfully created..."));
	}
	else
	{
		m_sketcher.SetDisplay(SketcherEngine::DISPLAY_LUMINANCE_MAP);
		gDisplay.InvalidateView();
	}

	
}

void CSketcherDoc::OnUpdateImageDisplayluminancemap(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_sketcher.GetDisplay() == SketcherEngine::DISPLAY_LUMINANCE_MAP)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CSketcherDoc::OnImageDisplaycanvas(void)
{
	m_sketcher.SetDisplay(SketcherEngine::DISPLAY_CANVAS);
}

void CSketcherDoc::OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_sketcher.GetDisplay() == SketcherEngine::DISPLAY_CANVAS)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CSketcherDoc::OnSketcherSketch(void)
{
	m_colony.DispatchAnt(&m_sketcher, &m_configuration);
}

void CSketcherDoc::OnUpdateSketcherSketch(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_colony.IsNull())
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
	}
}

void CSketcherDoc::OnSketcherOptions()
{
	// TODO: Add your command handler code here
	CDlgACConfig dlg;

	dlg.m_T0=m_configuration.GetT0();
	dlg.m_T1=m_configuration.GetT1();
	dlg.m_Tgap=m_configuration.GetTgap();
	dlg.m_Thatch=m_configuration.GetThatch();
	dlg.m_fMarkAngle=m_configuration.GetMarkAngle();
	dlg.m_fSharpTurnThreshold=m_configuration.GetSharpTurnThreshold();

	dlg.m_iStepSize=m_configuration.GetStepSize();
	dlg.m_iJumpRadius=m_configuration.GetJumpRadius();
	dlg.m_iMaxJumps=m_configuration.GetMaxJumps();
	dlg.m_iMarkLength=m_configuration.GetMarkLength();
	dlg.m_iMarkThickness=m_configuration.GetMarkThickness();
	dlg.m_iMaxSteps=m_configuration.GetMaxSteps();

	dlg.m_iT0=static_cast<int>(dlg.m_T0 * 100.0f / 255.0f);
	dlg.m_iT1=static_cast<int>(dlg.m_T1 * 100.0f / 255.0f);
	dlg.m_iTgap=static_cast<int>(dlg.m_Tgap * 100.0f / 255.0f);
	dlg.m_iThatch=static_cast<int>(dlg.m_Thatch * 100.0f / 255.0f);
	dlg.m_iMarkAngle=static_cast<int>(dlg.m_fMarkAngle * 100.0f / 360.0f);
	dlg.m_iSharpTurnThreshold=static_cast<int>(dlg.m_fSharpTurnThreshold * 100.0f / 360.0f);

	dlg.m_iColonySize=m_configuration.GetColonySize();
	dlg.m_iColorCopy=m_configuration.GetColorCopy();
	dlg.m_iMarkingBehavior=m_configuration.GetMarkingBehavior();

	dlg.m_bRedraw=m_bRedrawCanvas;
	dlg.m_bDirectedDraw=m_configuration.GetDirectedDraw() ? TRUE : FALSE;

	dlg.m_iAntsPerExecution=m_configuration.GetAntsPerExecution();
	dlg.m_iAntsPerRefresh=m_configuration.GetAntsPerRefresh();

	if(dlg.DoModal()==IDOK)
	{
		m_configuration.SetT0(dlg.m_T0);
		m_configuration.SetT1(dlg.m_T1);
		m_configuration.SetTgap(dlg.m_Tgap);
		m_configuration.SetThatch(dlg.m_Thatch);
		m_configuration.SetMarkAngle(dlg.m_fMarkAngle);
		m_configuration.SetSharpTurnThreshold(dlg.m_fSharpTurnThreshold);

		m_configuration.SetStepSize(dlg.m_iStepSize);
		m_configuration.SetJumpRadius(dlg.m_iJumpRadius);
		m_configuration.SetMaxJumps(dlg.m_iMaxJumps);
		m_configuration.SetMarkLength(dlg.m_iMarkLength);
		m_configuration.SetMarkThickness(dlg.m_iMarkThickness);
		m_configuration.SetMaxSteps(dlg.m_iMaxSteps);

		m_configuration.SetColonySize(dlg.m_iColonySize);
		m_configuration.SetAntsPerExecution(dlg.m_iAntsPerExecution);
		m_configuration.SetAntsPerRefresh(dlg.m_iAntsPerRefresh);

		m_configuration.SetMarkingBehavior(dlg.m_iMarkingBehavior);
		m_configuration.SetColorCopy(dlg.m_iColorCopy);

		m_colony.Reset(&m_configuration);

		if(dlg.m_bDirectedDraw==TRUE)
		{
			m_configuration.SetDirectedDraw(true);
		}
		else
		{
			m_configuration.SetDirectedDraw(false);
		}

		m_bRedrawCanvas=dlg.m_bRedraw;

		if(dlg.m_bRedraw==TRUE)
		{
			m_sketcher.ResetCanvas();
			gDisplay.InvalidateView(FALSE);
		}
	}
}

void CSketcherDoc::OnSketcherClearcanvas()
{
	// TODO: Add your command handler code here
	m_sketcher.ResetCanvas();
	gDisplay.InvalidateView(FALSE);
}

void CSketcherDoc::OnSketcherBatchrun()
{
	// TODO: Add your command handler code here
	if(m_colony.IsNull())
	{
		m_colony.Reset(&m_configuration);
		m_colony.DispatchAnt(&m_sketcher, &m_configuration);
	}
}

void CSketcherDoc::OnUpdateSketcherBatchrun(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_sketcher.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_colony.IsNull())
		{
			pCmdUI->Enable(TRUE);
		}
		else
		{
			pCmdUI->Enable(FALSE);
		}
	}
}
