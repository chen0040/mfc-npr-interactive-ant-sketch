#include "StdAfx.h"
#include "AntColonyConfiguration.h"
#include "Ant.h"
#include "tinyxml/tinyxml.h"
#include "SketchElement_Line.h"
#include "SketchElement_Circle.h"

AntColonyConfiguration::AntColonyConfiguration(void)
: m_fSharpTurnThreshold(45)
, m_iColonySize(500)
, m_iJumpRadius(5)
, m_iMaxJumps(5)
, m_iMaxSteps(200)
, m_iStepSize(20)
, m_T0(80.0f)
, m_T1(20.0f)
, m_Tgap(10.0f)
, m_Thatch(10.0f)
, m_iMarkShape(MARKSHAPE_LINE)
, m_iMarkLength(20)
, m_iMarkThickness(2)
, m_fMarkAngle(45)
, m_iAntsPerExecution(50)
, m_bDirectedDraw(false)
, m_iColorCopy(COLORCOPY_RGB)
, m_iAntsPerRefresh(50)
, m_iMarkingBehavior(MARKINGBEHAVIOR_EDGEDRAWING)
{
}

AntColonyConfiguration::~AntColonyConfiguration(void)
{
}



bool AntColonyConfiguration::Load(LPCTSTR pFilename)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(CT2CA(pFilename)))
	{
		CString fmt;
		fmt.Format(_T("Failed to load %s"), pFilename);
		AfxMessageBox(fmt, MB_OK);
		return false;
	}

	TiXmlElement* pRoot=doc.RootElement();

	for(TiXmlElement* pElement=pRoot->FirstChildElement(); pElement!=NULL; pElement=pElement->NextSiblingElement())
	{
		if(strcmp(pElement->Value(), "param")==0)
		{
			CString param_name(CA2CT(pElement->Attribute("name")));
			if(param_name == _T("colony size"))
			{
				pElement->QueryIntAttribute("value", &m_iColonySize);
			}
			else if(param_name==_T("step size"))
			{
				pElement->QueryIntAttribute("value", &m_iStepSize);
			}
			else if(param_name==_T("T0"))
			{
				pElement->QueryFloatAttribute("value", &m_T0);
			}
			else if(param_name==_T("T1"))
			{
				pElement->QueryFloatAttribute("value", &m_T1);
			}
			else if(param_name==_T("Tgap"))
			{
				pElement->QueryFloatAttribute("value", &m_Tgap);
			}
			else if(param_name==_T("Thatch"))
			{
				pElement->QueryFloatAttribute("value", &m_Thatch);
			}
			else if(param_name==_T("jump radius"))
			{
				pElement->QueryIntAttribute("value", &m_iJumpRadius);
			}
			else if(param_name==_T("max steps"))
			{
				pElement->QueryIntAttribute("value", &m_iMaxSteps);
			}
			else if(param_name==_T("marking behavior"))
			{
				int iMarkingBehavior=0;
				pElement->QueryIntAttribute("value", &iMarkingBehavior);
				if(iMarkingBehavior==0)
				{
					m_iMarkingBehavior=MARKINGBEHAVIOR_EDGEDRAWING;
				}
				else if(iMarkingBehavior==1)
				{
					m_iMarkingBehavior=MARKINGBEHAVIOR_FILLINGHATCHING;
				}
			}
			else if(param_name==_T("max jumps"))
			{
				pElement->QueryIntAttribute("value", &m_iMaxJumps);
			}
			else if(param_name==_T("sharp turn threshold"))
			{
				pElement->QueryFloatAttribute("value", &m_fSharpTurnThreshold);
			}
			else if(param_name==_T("mark shape"))
			{
				CString param_value(CA2CT(pElement->Attribute("value")));
				if(param_value==_T("line"))
				{
					m_iMarkShape=MARKSHAPE_LINE;
				}
				else if(param_value==_T("circle"))
				{
					m_iMarkShape=MARKSHAPE_CIRCLE;
				}
				else if(param_value==_T("cross"))
				{
					m_iMarkShape=MARKSHAPE_CROSS;
				}
			}
			else if(param_name==_T("color copy"))
			{
				int iColorCopy=0;
				pElement->QueryIntAttribute("value", &iColorCopy);

				if(iColorCopy==0)
				{
					m_iColorCopy=COLORCOPY_RGB;
				}
				else if(iColorCopy==1)
				{
					m_iColorCopy=COLORCOPY_LUMINANCE;
				}
			}
			else if(param_name==_T("directed draw"))
			{
				CString param_value(CA2CT(pElement->Attribute("value")));
				param_value=param_value.MakeLower();
				if(param_value==_T("true"))
				{
					m_bDirectedDraw=true;
				}
				else
				{
					m_bDirectedDraw=false;
				}
			}
			else if(param_name==_T("mark angle"))
			{
				pElement->QueryFloatAttribute("value", &m_fMarkAngle);
			}
			else if(param_name==_T("mark length"))
			{
				pElement->QueryIntAttribute("value", &m_iMarkLength);
			}
			else if(param_name==_T("mark thickness"))
			{
				pElement->QueryIntAttribute("value", &m_iMarkThickness);
			}
			else if(param_name==_T("ants per execution"))
			{
				pElement->QueryIntAttribute("value", &m_iAntsPerExecution);
			}
			else if(param_name==_T("ants per refresh"))
			{
				pElement->QueryIntAttribute("value", &m_iAntsPerRefresh);
			}
		}
	}

	return true;
}

SketchElement* AntColonyConfiguration::GetSketchElement()
{
	SketchElement* pElement=NULL;
	switch(m_iMarkShape)
	{
	case MARKSHAPE_LINE:
		pElement=new SketchElement_Line();
		break;
	case MARKSHAPE_CIRCLE:
		pElement=new SketchElement_Circle();
		break;
	}

	if(pElement==NULL)
	{
		return NULL;
	}

	pElement->SetMarkAngle(m_fMarkAngle);
	pElement->SetMarkLength(m_iMarkLength);
	pElement->SetMarkThickness(m_iMarkThickness);
	pElement->SetMarkShape(m_iMarkShape);
	pElement->SetDirectedDraw(m_bDirectedDraw);

	return pElement;
}
