#pragma once
#include "sketchelement.h"

class SketchElement_Point :
	public SketchElement
{
public:
	SketchElement_Point(void);
	virtual ~SketchElement_Point(void);

private:
	CPoint m_pt;
public:
	void Set(CPoint pt);

public:
	virtual void Draw(SketcherEngine* pSketcher, CDC* pDC);
};
