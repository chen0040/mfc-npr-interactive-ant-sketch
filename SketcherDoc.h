// SketcherDoc.h : interface of the CSketcherDoc class
//


#pragma once

#include "SketcherEngine.h"
#include "AntColony.h"
#include "AntColonyConfiguration.h"


class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	SketcherEngine m_sketcher;
	AntColony m_colony;
	AntColonyConfiguration m_configuration;
	BOOL m_bRedrawCanvas;

public:
	bool Load(LPCTSTR pFileName);
	void Display(CDC* pDC, const CRect& rect);
	void OnImageDisplaysource();
	afx_msg void OnSketcherSaveimage();
	afx_msg void OnUpdateSketcherSaveimage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageDisplaysource(CCmdUI *pCmdUI);
	void OnImageDisplaygradientmap(void);
	afx_msg void OnUpdateImageDisplaygradientmap(CCmdUI *pCmdUI);
	void OnImageDisplayluminancemap(void);
	afx_msg void OnUpdateImageDisplayluminancemap(CCmdUI *pCmdUI);
	void OnImageDisplaycanvas(void);
	afx_msg void OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI);
	void OnSketcherSketch(void);
	afx_msg void OnUpdateSketcherSketch(CCmdUI *pCmdUI);
	afx_msg void OnSketcherOptions();
	afx_msg void OnSketcherClearcanvas();
	afx_msg void OnSketcherBatchrun();
	afx_msg void OnUpdateSketcherBatchrun(CCmdUI *pCmdUI);
};


