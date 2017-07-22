#include "StdAfx.h"
#include "SketchElement.h"
#include "SketcherEngine.h"

SketchElement::SketchElement(void)
{
}

SketchElement::~SketchElement(void)
{
}

void SketchElement::SetDrawConstraint(int iCanvasWidth, int iCanvasHeight)
{
	m_iCanvasWidth=iCanvasWidth;
	m_iCanvasHeight=iCanvasHeight;
}

void SketchElement::SetPosition(int x, int y)
{
	m_pos.x=x;
	m_pos.y=y;
}
