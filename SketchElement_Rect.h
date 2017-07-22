#pragma once
#include "sketchelement.h"

class SketchElement_Rect :
	public SketchElement
{
public:
	SketchElement_Rect(void);
	virtual ~SketchElement_Rect(void);

public:
	void Set(CPoint ptCenter, int iSideLength);
	void SetColor(COLORREF color);

private:
	CRect m_rect;
public:
	virtual void Draw(SketcherEngine* pSketcher, CDC* pDC);
};
