#pragma once
#include "sketchelement.h"

class SketchElement_Line :
	public SketchElement
{
public:
	SketchElement_Line(void);
	virtual ~SketchElement_Line(void);

public:
	virtual void Draw(SketcherEngine* pSketcher, CDC* pDC);
};
