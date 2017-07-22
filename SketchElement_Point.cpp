#include "StdAfx.h"
#include "SketchElement_Point.h"
#include "SketcherEngine.h"

SketchElement_Point::SketchElement_Point(void)
{
	m_color=RGB(0, 0, 0);
}

SketchElement_Point::~SketchElement_Point(void)
{
}

void SketchElement_Point::Draw(SketcherEngine* pSketcher, CDC* pDC)
{
	pDC->SetPixel(m_pt.x, m_pt.y, m_color);
}

void SketchElement_Point::Set(CPoint pt)
{
	m_pt=pt;
}
