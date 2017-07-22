#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgACConfig dialog

class CDlgACConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgACConfig)

public:
	CDlgACConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgACConfig();

// Dialog Data
	enum { IDD = IDD_DLGACCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_T0;
	float m_T1;
	float m_Tgap;
	float m_Thatch;
	float m_fSharpTurnThreshold;
	float m_fMarkAngle;
	int m_iT0;
	int m_iT1;
	int m_iTgap;
	int m_iThatch;
	int m_iSharpTurnThreshold;
	int m_iMarkAngle;
	afx_msg void OnNMReleasedcaptureSliderT0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderT1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderTgap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderThatch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderSharpturnthreshold(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderMarkangle(NMHDR *pNMHDR, LRESULT *pResult);
	int m_iStepSize;
	int m_iJumpRadius;
	int m_iMaxSteps;
	int m_iMaxJumps;
	int m_iMarkLength;
	int m_iMarkThickness;
	int m_iColonySize;
	BOOL m_bRedraw;
	BOOL m_bDirectedDraw;
	int m_iAntsPerExecution;
	int m_iAntsPerRefresh;
	int m_iColorCopy;
	int m_iMarkingBehavior;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioCopyrgb();
	afx_msg void OnBnClickedRadioGreyscalefromluminance();
	afx_msg void OnBnClickedRadioEdgedrawing();
	afx_msg void OnBnClickedRadioFillingandhatching();
};
