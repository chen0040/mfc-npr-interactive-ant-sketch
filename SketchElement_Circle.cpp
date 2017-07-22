#include "StdAfx.h"
#include "SketchElement_Circle.h"

SketchElement_Circle::SketchElement_Circle(void)
{
}

SketchElement_Circle::~SketchElement_Circle(void)
{
}

void SketchElement_Circle::Draw(SketcherEngine* pSketcher, CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, m_color);

	CPen* pOldPen=pDC->SelectObject(&pen);
	CBrush* pOldBrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Ellipse(&m_rect);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
}

void SketchElement_Circle::Set(CPoint ptCenter, int iRadius)
{
	m_rect.left=ptCenter.x - iRadius;
	m_rect.top=ptCenter.y - iRadius;

	m_rect.right=m_rect.left + iRadius * 2;
	m_rect.bottom=m_rect.top + iRadius * 2;
}