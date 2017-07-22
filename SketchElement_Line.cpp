#include "StdAfx.h"
#include "SketchElement_Line.h"
#include "SketcherEngine.h"

SketchElement_Line::SketchElement_Line(void)
{
}

SketchElement_Line::~SketchElement_Line(void)
{
}

void SketchElement_Line::Draw(SketcherEngine *pSketcher, CDC *pDC)
{
	static const float PI=3.14159265f;

	CPen pen;

	COLORREF color=m_color;

	pen.CreatePen(PS_SOLID, m_iMarkThickness, color);

	CPen* pOldPen=pDC->SelectObject(&pen);
	CBrush* pOldBrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	float rad=m_fMarkAngle * PI / 180.0f;

	int dx=0;
	int dy=0;
	if(m_bDirectedDraw)
	{
		dx=static_cast<int>(m_orientation.GetX() * m_iMarkLength / 2);
		dy=static_cast<int>(m_orientation.GetY() * m_iMarkLength / 2);
	}
	else
	{
		dx=static_cast<int>(m_iMarkLength * cos(rad) / 2);
		dy=static_cast<int>(m_iMarkLength * sin(rad) / 2 );
	}

	int sx=m_pos.x + dx;
	int sy=m_pos.y + dy;

	int ex=m_pos.x - dx;
	int ey=m_pos.y - dy;

	if(sx < 0) sx=0;
	if(sx >= m_iCanvasWidth) sx=m_iCanvasWidth;
	if(sy < 0) sy=0;
	if(sy >= m_iCanvasHeight) sy=m_iCanvasHeight;

	if(ex < 0) ex=0;
	if(ex >= m_iCanvasWidth) ex=m_iCanvasWidth;
	if(ey < 0) ey=0;
	if(ey >= m_iCanvasHeight) ey=m_iCanvasHeight;

	pDC->MoveTo(ex, ey);
	pDC->LineTo(sx, sy);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
}
