#pragma once
#include "sketchelement.h"

class SketchElement_Circle :
	public SketchElement
{
public:
	SketchElement_Circle(void);
	virtual ~SketchElement_Circle(void);

public:
	void Set(CPoint pt, int iRadius);

private:
	CRect m_rect;

public:
	virtual void Draw(SketcherEngine* pSketcher, CDC* pDC);
};
