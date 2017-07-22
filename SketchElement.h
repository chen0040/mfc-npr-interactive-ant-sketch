#pragma once
#include "afx.h"
#include "Vec2f.h"

class SketcherEngine;

class SketchElement :
	public CObject
{
public:
	SketchElement(void);
	~SketchElement(void);

public:
	void SetColor(COLORREF color) { m_color=color; }
	void SetMarkAngle(float angle) { m_fMarkAngle=angle; }
	void SetMarkLength(int len) { m_iMarkLength=len; }
	void SetMarkThickness(int t) { m_iMarkThickness = t; }
	void SetMarkShape(int iShape) { m_iMarkShape=iShape; }
	void SetDrawConstraint(int iCanvasWidth, int iCanvasHeight);
	void SetDirectedDraw(bool bDirected) { m_bDirectedDraw=bDirected; }
	void SetOrientation(const Vec2f& orientation) { m_orientation=orientation; }

public:
	virtual void Draw(SketcherEngine* pSketcher, CDC* pDC)=0;

protected:
	COLORREF m_color;
	float m_fMarkAngle;
	int m_iMarkThickness;
	int m_iMarkShape;
	int m_iMarkLength;
	int m_iCanvasWidth;
	int m_iCanvasHeight;
	bool m_bDirectedDraw;
	Vec2f m_orientation;
	CPoint m_pos;
public:
	void SetPosition(int x, int y);
};
