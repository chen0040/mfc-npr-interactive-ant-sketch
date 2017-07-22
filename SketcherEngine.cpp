#include "StdAfx.h"
#include "SketcherEngine.h"
#include <comdef.h>
#include <cmath>
#include "Display.h"

SketcherEngine::SketcherEngine(void)
: m_iDisplay(DISPLAY_CANVAS)
{
}

SketcherEngine::~SketcherEngine(void)
{
	
}

void SketcherEngine::UpdateBuffer(const CRect& drRect)
{
	if(m_imgBuffer.IsNull())
	{
		m_imgBuffer.Create(drRect.Width(), drRect.Height(), m_imgSource.GetBPP());
	}
	else
	{
		if(m_imgBuffer.GetWidth() != drRect.Width() || m_imgBuffer.GetHeight() != drRect.Height())
		{
			m_imgBuffer.Destroy();
			m_imgBuffer.Create(drRect.Width(), drRect.Height(), m_imgSource.GetBPP());
		}
	}
}

void SketcherEngine::PaintBufferBackground(CDC* pDC, const CRect& drRect)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 125, 125));

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(125, 125, 125));

	CBrush* pOldBrush=pDC->SelectObject(&brush);
	CPen* pOldPen=pDC->SelectObject(&pen);

	pDC->Rectangle(&drRect);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	pen.DeleteObject();
	brush.DeleteObject();
}

bool SketcherEngine::Load(LPCTSTR filename)
{
	m_imgSource.Destroy();

	HRESULT hResult=m_imgSource.Load(filename);
	if(FAILED(hResult))
	{
		CString fmt;
		fmt.Format(_T("Error: Failed to load %s: \n %x - %s"), filename, hResult, _com_error(hResult));
		AfxMessageBox(fmt, MB_OK);
		return false;
	}

	m_imgCanvas.Destroy();
	m_imgCanvas.Create(m_imgSource.GetWidth(), m_imgSource.GetHeight(), m_imgSource.GetBPP());

	ResetCanvas();

	m_imgGradient.Destroy();
	m_imgLuminance.Destroy();

	return true;
}

void SketcherEngine::CreateGradientMap()
{
	const float PI=3.14159265f;

	m_imgGradient.Destroy();
	m_imgGradient.Create(m_imgSource.GetWidth(), m_imgSource.GetHeight(), m_imgSource.GetBPP());

	int height=m_imgSource.GetHeight();
	int width=m_imgSource.GetWidth();

	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			int norm=static_cast<int>(GetGradientNorm(x, y));

			m_imgGradient.SetPixel(x, y, RGB(norm, norm, norm));
		}
	}
}

int SketcherEngine::GetLuminance(COLORREF color)
{
	int r=GetRValue(color);
	int g=GetGValue(color);
	int b=GetBValue(color);
	return static_cast<int>(0.299f * r + 0.587f * g + 0.114f * b);
}

void SketcherEngine::CreateLuminanceMap()
{
	m_imgLuminance.Destroy();
	m_imgLuminance.Create(m_imgSource.GetWidth(), m_imgSource.GetHeight(), m_imgSource.GetBPP());

	int height=m_imgSource.GetHeight();
	int width=m_imgSource.GetWidth();
	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			int luminance=GetLuminance(x, y);
			m_imgLuminance.SetPixel(x, y, RGB(luminance, luminance, luminance));
		}
	}
}

CPoint SketcherEngine::GetGradient(int x, int y)
{
	CPoint dir;

	int pixel[3][3];
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			pixel[i][j]=0;
		}
	}

	int width=m_imgSource.GetWidth();
	int height=m_imgSource.GetHeight();

	for(int i=0; i<3; i++)
	{
		int yy=y + i - 1;
		if(yy < 0)
		{
			continue;
		}
		else if(yy >= height)
		{
			break;
		}
		for(int j=0; j<3; j++)
		{
			int xx=x+j-1;
			if(xx < 0)
			{
				continue;
			}
			else if(xx >= width)
			{
				break;
			}

			if(m_imgLuminance.IsNull())
			{
				pixel[i][j]=GetLuminance(xx, yy); 
			}
			else
			{
				pixel[i][j]=GetRValue(m_imgLuminance.GetPixel(xx, yy));
			}
		}
	}

	dir.x= - pixel[0][0] + pixel[0][2]
		- 2 * pixel[1][0] + 2 * pixel[1][2]
		- pixel[2][0] + pixel[2][2];

	dir.y= - pixel[0][0] + pixel[2][0]
		- 2 * pixel[0][1] + 2 * pixel[2][1]
		- pixel[0][2] + pixel[2][2];

	return dir;
}

int SketcherEngine::GetLuminance(int x, int y)
{
	return GetLuminance(m_imgSource.GetPixel(x, y));
}

float SketcherEngine::GetGradientNorm(int x, int y)
{
	CPoint dir=GetGradient(x, y);

	float xx=static_cast<float>(dir.x);
	float yy=static_cast<float>(dir.y);

	float l=sqrt(xx * xx + yy * yy);

	return l;
}

void SketcherEngine::DisplaySource(CDC* pDC, const CRect& vrect)
{
	m_imgSource.StretchBlt(pDC->m_hDC, vrect.left, vrect.top, vrect.Width(), vrect.Height(), SRCCOPY);
}

CRect SketcherEngine::GetCanvasRect(const CRect& rtClient)
{
	CRect vrect;

	int img_width=m_imgSource.GetWidth();
	int img_height=m_imgSource.GetHeight();

	float img_aspect=static_cast<float>(img_width) / static_cast<float>(img_height);

	int rt_width=rtClient.Width();
	int rt_height=rtClient.Height();

	float rt_aspect=static_cast<float>(rt_width) / static_cast<float>(rt_height);

	vrect.left=0;
	vrect.top=0;
	int canvas_width=rt_width;
	int canvas_height=rt_height;
	if(img_aspect < rt_aspect)
	{
		canvas_width=static_cast<int>(rt_height * img_aspect);	
		vrect.left=static_cast<int>((rt_width - canvas_width) / 2.0);
	}
	else if(img_aspect > rt_aspect)
	{
		canvas_height=static_cast<int>(rt_width / img_aspect);
		vrect.top=static_cast<int>((rt_height-canvas_height) / 2.0);
	}
	vrect.right=vrect.left + canvas_width;
	vrect.bottom=vrect.top+canvas_height;

	return vrect;
}

void SketcherEngine::SetDisplay(int iDisplay)
{
	m_iDisplay=iDisplay;
}

void SketcherEngine::Display(CDC* pDC, const CRect& rect)
{
	UpdateBuffer(rect);

	CDC* pBufferDC=CDC::FromHandle(m_imgBuffer.GetDC());

	PaintBufferBackground(pBufferDC, rect);

	CRect vrect=GetCanvasRect(rect);
	switch(m_iDisplay)
	{
	case DISPLAY_SOURCE:
		DisplaySource(pBufferDC, vrect);
		break;
	case DISPLAY_GRADIENT_MAP:
		DisplayGradientMap(pBufferDC, vrect);
		break;
	case DISPLAY_LUMINANCE_MAP:
		DisplayLuminanceMap(pBufferDC, vrect);
		break;
	case DISPLAY_CANVAS:
		DisplayCanvas(pBufferDC, vrect);
		break;
	}

	m_imgBuffer.ReleaseDC();

	m_imgBuffer.BitBlt(pDC->m_hDC, 0, 0, SRCCOPY);
}

int SketcherEngine::GetDisplay(void) const
{
	return m_iDisplay;
}

bool SketcherEngine::IsNull(void) const
{
	return m_imgSource.IsNull();
}

void SketcherEngine::Save(LPCTSTR pFilename)
{
	switch(m_iDisplay)
	{
	case DISPLAY_SOURCE:
		m_imgSource.Save(pFilename);
		break;
	case DISPLAY_GRADIENT_MAP:
		if(m_imgGradient.IsNull())
		{
			CreateGradientMap();
		}
		m_imgGradient.Save(pFilename);
		break;
	case DISPLAY_LUMINANCE_MAP:
		if(m_imgLuminance.IsNull())
		{
			CreateLuminanceMap();
		}
		m_imgLuminance.Save(pFilename);
		break;
	case DISPLAY_CANVAS:
		m_imgCanvas.Save(pFilename);
		break;
	}
}

void SketcherEngine::DisplayGradientMap(CDC* pDC, const CRect& rect)
{
	if(m_imgGradient.IsNull())
	{
		gDisplay.SetStatusText(_T("Gradient Map does not exist. Create Gradient Map..."));
		CreateGradientMap();
		gDisplay.SetStatusText(_T("Gradient Map successfully created..."));
	}
	m_imgGradient.StretchBlt(pDC->m_hDC, rect.left, rect.top, rect.Width(), rect.Height(), SRCCOPY);
}

void SketcherEngine::DisplayLuminanceMap(CDC* pDC, const CRect& rect)
{
	if(m_imgLuminance.IsNull())
	{
		gDisplay.SetStatusText(_T("Luminance Map does not exist. Create Luminance Map..."));
		CreateLuminanceMap();
		gDisplay.SetStatusText(_T("Luminance Map successfully created..."));
	}

	m_imgLuminance.StretchBlt(pDC->m_hDC, rect.left, rect.top, rect.Width(), rect.Height(), SRCCOPY);
}

int SketcherEngine::GetWidth() const
{
	if(m_imgSource.IsNull())
	{
		return -1;
	}
	return m_imgSource.GetWidth();
}

int SketcherEngine::GetHeight() const
{
	if(m_imgSource.IsNull())
	{
		return -1;
	}

	return m_imgSource.GetHeight();
}

Vec2f SketcherEngine::GetDirection(int x, int y)
{
	CPoint dir=GetGradient(x, y);

	Vec2f orientation;

	float xx=-static_cast<float>(dir.y) / 255.0f;
	float yy=static_cast<float>(dir.x) / 255.0f;

	float l=sqrt(xx * xx + yy * yy);

	if(l == 0)
	{
		orientation.SetX(0);
		orientation.SetY(0);
	}
	else
	{
		orientation.SetX(xx / l);
		orientation.SetY(yy / l);
	}

	return orientation;
}

void SketcherEngine::DisplayCanvas(CDC* pDC, const CRect& rect)
{
	m_imgCanvas.StretchBlt(pDC->m_hDC, rect.left, rect.top, rect.Width(), rect.Height(), SRCCOPY);
}

bool SketcherEngine::IsGradientMapImgAvailable(void)
{
	return !m_imgGradient.IsNull();
}

bool SketcherEngine::IsLuminanceMapImgAvailable(void)
{
	return !m_imgLuminance.IsNull();
}

void SketcherEngine::Draw(SketchElement* pElement)
{
	CDC* pDC=CDC::FromHandle(m_imgCanvas.GetDC());
	pElement->Draw(this, pDC);
	m_imgCanvas.ReleaseDC();
}

COLORREF SketcherEngine::SampleColor(int x, int y)
{
	return m_imgSource.GetPixel(x, y);
}

void SketcherEngine::ResetCanvas(void)
{
	if(m_imgCanvas.IsNull())
	{
		return;
	}
	else
	{
		CDC* pDC=CDC::FromHandle(m_imgCanvas.GetDC());

		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 255, 255));

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

		CPen* pOldPen=pDC->SelectObject(&pen);
		CBrush* pOldBrush=(CBrush*)pDC->SelectObject(&brush);

		pDC->Rectangle(0, 0, m_imgCanvas.GetWidth(), m_imgCanvas.GetHeight());

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		brush.DeleteObject();
		pen.DeleteObject();

		m_imgCanvas.ReleaseDC();
	}
}
