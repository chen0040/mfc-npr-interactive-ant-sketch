// SketcherView.cpp : implementation of the CSketcherView class
//

#include "stdafx.h"
#include "Sketcher.h"

#include "SketcherDoc.h"
#include "MainFrm.h"
#include "SketcherView.h"
#include "Display.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CView)

BEGIN_MESSAGE_MAP(CSketcherView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SKETCHER_LOADIMAGE, &CSketcherView::OnSketcherLoadimage)
	ON_COMMAND(ID_IMAGE_DISPLAYSOURCE, &CSketcherView::OnImageDisplaysource)
	ON_COMMAND(ID_IMAGE_DISPLAYGRADIENTMAP, &CSketcherView::OnImageDisplaygradientmap)
	ON_COMMAND(ID_IMAGE_DISPLAYLUMINANCEMAP, &CSketcherView::OnImageDisplayluminancemap)
	ON_COMMAND(ID_IMAGE_DISPLAYCANVAS, &CSketcherView::OnImageDisplaycanvas)
	ON_COMMAND(ID_SKETCHER_SKETCH, &CSketcherView::OnSketcherSketch)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView()
{
	// TODO: add construction code here
	gDisplay.SetView(this);
}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);

	pDoc->Display(pDC, rect);

	if(!m_strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 255, 0));
		pDC->DrawText(m_strText, -1, &rect, DT_CENTER);
	}
}


// CSketcherView printing

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView message handlers

void CSketcherView::OnSketcherLoadimage()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog fdlg(TRUE, _T("bmp"), _T("source.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap File (*.bmp)|*.bmp|Jpeg File (*.jpg)|*.jpg|Gif File (*.gif)|*.gif|PNG File (*.png)|*.png|Tiff File (*.tif)|*.tif|All Files (*.*)|*.*|"));

	if(fdlg.DoModal() == IDOK)
	{
		CMainFrame* pMainFrame=(CMainFrame*)(this->GetParentFrame());

		CString strFilename=fdlg.GetPathName();

		CString fmt;
		fmt.Format(_T("Loading %s ..."), strFilename);
		pMainFrame->SetStatusText(fmt);

		pDoc->Load(strFilename);

		pMainFrame->SetStatusText(_T("Complete Loading"));
	}

	Invalidate();
	UpdateWindow();

}

void CSketcherView::OnImageDisplaysource()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnImageDisplaysource();

	Invalidate();
	UpdateWindow();
}

void CSketcherView::OnImageDisplaygradientmap()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnImageDisplaygradientmap();
}

void CSketcherView::OnImageDisplayluminancemap()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnImageDisplayluminancemap();

}

void CSketcherView::OnImageDisplaycanvas()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnImageDisplaycanvas();

	Invalidate();
	UpdateWindow();
}

void CSketcherView::OnSketcherSketch()
{
	// TODO: Add your command handler code here
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSketcherSketch();

	Invalidate(FALSE);
	UpdateWindow();
}

void CSketcherView::SetViewText(LPCTSTR pText)
{
	m_strText=pText;
}

void CSketcherView::ClearViewText(void)
{
	m_strText="";
}

void CSketcherView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	

	if(nChar==VK_RETURN)
	{
		CSketcherDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->OnSketcherBatchrun();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
