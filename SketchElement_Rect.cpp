#include "StdAfx.h"
#include "SketchElement_Rect.h"
#include "SketcherEngine.h"

SketchElement_Rect::SketchElement_Rect(void)
{
	m_color=RGB(0, 0, 0);
}

SketchElement_Rect::~SketchElement_Rect(void)
{
}

void SketchElement_Rect::Draw(SketcherEngine *pSketcher, CDC *pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, m_color);

	CPen* pOldPen=pDC->SelectObject(&pen);
	CBrush* pOldBrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Rectangle(&m_rect);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
}

void SketchElement_Rect::Set(CPoint ptCenter, int iSideLength)
{
	m_rect.left=ptCenter.x - iSideLength / 2;
	m_rect.top=ptCenter.y - iSideLength / 2;

	m_rect.right=m_rect.left + iSideLength;
	m_rect.bottom=m_rect.top + iSideLength;
}
