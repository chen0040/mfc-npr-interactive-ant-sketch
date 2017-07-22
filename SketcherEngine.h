#pragma once
#include "afx.h"
#include <vector>
#include "Vec2f.h"
#include "SketchElement.h"

class SketcherEngine :
	public CObject
{
public:
	SketcherEngine(void);
	~SketcherEngine(void);

public:
	bool Load(LPCTSTR filename);

private:
	CImage m_imgSource;
	CImage m_imgCanvas;
	CImage m_imgGradient;
	CImage m_imgLuminance;
	CImage m_imgBuffer;

protected:
	void UpdateBuffer(const CRect& drRect);
	void PaintBufferBackground(CDC* pDC, const CRect& drRect);

public:
	float GetGradientNorm(int x, int y);

public:
	void CreateGradientMap();
	void CreateLuminanceMap();

protected:
	int GetLuminance(COLORREF color);
	CPoint GetGradient(int x, int y);

public:
	int GetLuminance(int x, int y);

public:
	void Display(CDC* pDC, const CRect& rect);
protected:
	void DisplaySource(CDC* pDC, const CRect& rect);
	void DisplayGradientMap(CDC* pDC, const CRect& rect);
	void DisplayLuminanceMap(CDC* pDC, const CRect& rect);
	void DisplayCanvas(CDC* pDC, const CRect& rect);
protected:
	CRect GetCanvasRect(const CRect& rtClient);

public:
	static const int DISPLAY_SOURCE=0;
	static const int DISPLAY_GRADIENT_MAP=1;
	static const int DISPLAY_LUMINANCE_MAP=2;
	static const int DISPLAY_CANVAS=3;

protected:
	int m_iDisplay;
public:
	void SetDisplay(int iDisplay);
	int GetDisplay(void) const;
	bool IsNull(void) const;
	void Save(LPCTSTR pFilename);
	
	int GetWidth() const;
	int GetHeight() const;
	Vec2f GetDirection(int x, int y);
	bool IsGradientMapImgAvailable(void);
	bool IsLuminanceMapImgAvailable(void);
	void Draw(SketchElement* pElement);
	COLORREF SampleColor(int x, int y);
	void ResetCanvas(void);
};
