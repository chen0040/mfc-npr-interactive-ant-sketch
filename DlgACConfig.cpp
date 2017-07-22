// DlgACConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "DlgACConfig.h"
#include "AntColonyConfiguration.h"


// CDlgACConfig dialog

IMPLEMENT_DYNAMIC(CDlgACConfig, CDialog)

CDlgACConfig::CDlgACConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgACConfig::IDD, pParent)
	, m_T0(0)
	, m_T1(0)
	, m_Tgap(0)
	, m_Thatch(0)
	, m_fSharpTurnThreshold(0)
	, m_fMarkAngle(0)
	, m_iT0(0)
	, m_iT1(0)
	, m_iTgap(0)
	, m_iThatch(0)
	, m_iSharpTurnThreshold(0)
	, m_iMarkAngle(0)
	, m_iStepSize(0)
	, m_iJumpRadius(0)
	, m_iMaxSteps(0)
	, m_iMaxJumps(0)
	, m_iMarkLength(0)
	, m_iMarkThickness(0)
	, m_iColonySize(0)
	, m_bRedraw(FALSE)
	, m_bDirectedDraw(FALSE)
	, m_iAntsPerExecution(0)
	, m_iAntsPerRefresh(0)
	, m_iColorCopy(0)
	, m_iMarkingBehavior(0)
{

}

CDlgACConfig::~CDlgACConfig()
{
}

void CDlgACConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_T0, m_T0);
	DDV_MinMaxFloat(pDX, m_T0, 0.0f, 255.0f);
	DDX_Text(pDX, IDC_EDIT_T1, m_T1);
	DDV_MinMaxFloat(pDX, m_T1, 0, 255.0f);
	DDX_Text(pDX, IDC_EDIT_TGAP, m_Tgap);
	DDV_MinMaxFloat(pDX, m_Tgap, 0, 255.0f);
	DDX_Text(pDX, IDC_EDIT_THATCH, m_Thatch);
	DDV_MinMaxFloat(pDX, m_Thatch, 0, 255.0f);
	DDX_Text(pDX, IDC_EDIT_SHARPTURNTHRESHOLD, m_fSharpTurnThreshold);
	DDV_MinMaxFloat(pDX, m_fSharpTurnThreshold, 0, 255.0f);
	DDX_Text(pDX, IDC_EDIT_MARKANGLE, m_fMarkAngle);
	DDV_MinMaxFloat(pDX, m_fMarkAngle, 0, 360.0f);
	DDX_Slider(pDX, IDC_SLIDER_T0, m_iT0);
	DDV_MinMaxInt(pDX, m_iT0, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_T1, m_iT1);
	DDV_MinMaxInt(pDX, m_iT1, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_TGAP, m_iTgap);
	DDV_MinMaxInt(pDX, m_iTgap, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_THATCH, m_iThatch);
	DDV_MinMaxInt(pDX, m_iThatch, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_SHARPTURNTHRESHOLD, m_iSharpTurnThreshold);
	DDV_MinMaxInt(pDX, m_iSharpTurnThreshold, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_MARKANGLE, m_iMarkAngle);
	DDV_MinMaxInt(pDX, m_iMarkAngle, 0, 100);
	DDX_Text(pDX, IDC_EDIT_STEPSIZE, m_iStepSize);
	DDV_MinMaxInt(pDX, m_iStepSize, 1, 200);
	DDX_Text(pDX, IDC_EDIT_JUMPRADIUS, m_iJumpRadius);
	DDV_MinMaxInt(pDX, m_iJumpRadius, 2, 100);
	DDX_Text(pDX, IDC_EDIT_MAXSTEPS, m_iMaxSteps);
	DDV_MinMaxInt(pDX, m_iMaxSteps, 10, 1000);
	DDX_Text(pDX, IDC_EDIT_MAXJUMPS, m_iMaxJumps);
	DDV_MinMaxInt(pDX, m_iMaxJumps, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_MARKLENGTH, m_iMarkLength);
	DDV_MinMaxInt(pDX, m_iMarkLength, 1, 500);
	DDX_Text(pDX, IDC_EDIT_MARKTHICKNESS, m_iMarkThickness);
	DDV_MinMaxInt(pDX, m_iMarkThickness, 1, 100);
	DDX_Text(pDX, IDC_EDIT_COLONYSIZE, m_iColonySize);
	DDV_MinMaxInt(pDX, m_iColonySize, 10, 10000000);
	DDX_Check(pDX, IDC_CHECK_REDRAW, m_bRedraw);
	DDX_Check(pDX, IDC_CHECK_DIRECTEDDRAW, m_bDirectedDraw);
	DDX_Text(pDX, IDC_EDIT_ANTSPEREXECUTION, m_iAntsPerExecution);
	DDV_MinMaxInt(pDX, m_iAntsPerExecution, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_ANTSPERREFRESH, m_iAntsPerRefresh);
	DDV_MinMaxInt(pDX, m_iAntsPerRefresh, 1, 1000000);
}


BEGIN_MESSAGE_MAP(CDlgACConfig, CDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_T0, &CDlgACConfig::OnNMReleasedcaptureSliderT0)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_T1, &CDlgACConfig::OnNMReleasedcaptureSliderT1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TGAP, &CDlgACConfig::OnNMReleasedcaptureSliderTgap)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_THATCH, &CDlgACConfig::OnNMReleasedcaptureSliderThatch)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SHARPTURNTHRESHOLD, &CDlgACConfig::OnNMReleasedcaptureSliderSharpturnthreshold)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MARKANGLE, &CDlgACConfig::OnNMReleasedcaptureSliderMarkangle)
	ON_BN_CLICKED(IDC_RADIO_COPYRGB, &CDlgACConfig::OnBnClickedRadioCopyrgb)
	ON_BN_CLICKED(IDC_RADIO_GREYSCALEFROMLUMINANCE, &CDlgACConfig::OnBnClickedRadioGreyscalefromluminance)
	ON_BN_CLICKED(IDC_RADIO_EDGEDRAWING, &CDlgACConfig::OnBnClickedRadioEdgedrawing)
	ON_BN_CLICKED(IDC_RADIO_FILLINGANDHATCHING, &CDlgACConfig::OnBnClickedRadioFillingandhatching)
END_MESSAGE_MAP()


void CDlgACConfig::OnNMReleasedcaptureSliderT0(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_T0=static_cast<float>(m_iT0 / 100.0f * 255.0f);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgACConfig::OnNMReleasedcaptureSliderT1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_T1=static_cast<float>(m_iT1 / 100.0f * 255.0f);
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgACConfig::OnNMReleasedcaptureSliderTgap(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Tgap=static_cast<float>(m_iTgap / 100.0f * 255.0f);
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgACConfig::OnNMReleasedcaptureSliderThatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Thatch=static_cast<float>(m_iThatch / 100.0f * 255.0f);
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgACConfig::OnNMReleasedcaptureSliderSharpturnthreshold(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fSharpTurnThreshold=static_cast<float>(m_iSharpTurnThreshold / 100.0f * 255.0f);
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgACConfig::OnNMReleasedcaptureSliderMarkangle(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fMarkAngle=static_cast<float>(m_iMarkAngle / 100.0f * 255.0f);
	UpdateData(FALSE);

	*pResult = 0;
}

BOOL CDlgACConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	switch(m_iColorCopy)
	{
	case AntColonyConfiguration::COLORCOPY_LUMINANCE:
		this->CheckDlgButton(IDC_RADIO_GREYSCALEFROMLUMINANCE, 1);
		break;
	case AntColonyConfiguration::COLORCOPY_RGB:
		this->CheckDlgButton(IDC_RADIO_COPYRGB, 1);
		break;
	}

	switch(m_iMarkingBehavior)
	{
	case AntColonyConfiguration::MARKINGBEHAVIOR_EDGEDRAWING:
		this->CheckDlgButton(IDC_RADIO_EDGEDRAWING, 1);
		break;
	case AntColonyConfiguration::MARKINGBEHAVIOR_FILLINGHATCHING:
		this->CheckDlgButton(IDC_RADIO_FILLINGANDHATCHING, 1);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgACConfig::OnBnClickedRadioCopyrgb()
{
	// TODO: Add your control notification handler code here
	m_iColorCopy=AntColonyConfiguration::COLORCOPY_RGB;
}

void CDlgACConfig::OnBnClickedRadioGreyscalefromluminance()
{
	// TODO: Add your control notification handler code here
	m_iColorCopy=AntColonyConfiguration::COLORCOPY_LUMINANCE;
}

void CDlgACConfig::OnBnClickedRadioEdgedrawing()
{
	// TODO: Add your control notification handler code here
	m_iMarkingBehavior=AntColonyConfiguration::MARKINGBEHAVIOR_EDGEDRAWING;
}

void CDlgACConfig::OnBnClickedRadioFillingandhatching()
{
	// TODO: Add your control notification handler code here
	m_iMarkingBehavior=AntColonyConfiguration::MARKINGBEHAVIOR_FILLINGHATCHING;
}
