#include "StdAfx.h"
#include "Ant.h"
#include "AntColonyConfiguration.h"
#include "SketcherEngine.h"
#include "RandomGenerator.h"
#include "SketchElement.h"
#include "Display.h"
#include <cmath>

Ant::Ant(void)
:m_iStepsCounter(10)
, m_iJumpsCounter(10)
, m_iStepSize(10)
, m_bDead(true)
, m_pConfig(NULL)
, m_pSketcher(NULL)
, m_Lgap(0.0f)
, m_L0(0.0f)
, m_fAlpha(45)
, m_iTurnCounter(0)
{
	m_memory[0]=0;
	m_memory[1]=0;
	m_memory[2]=0;	
}

Ant::~Ant(void)
{
}

Ant::Ant(const Ant& rhs)
{
	m_position=rhs.m_position;
	m_orientation=rhs.m_orientation;
	
	for(int i=0; i<3; i++)
	{
		m_memory[i]=rhs.m_memory[i];
	}

	m_iStepsCounter=rhs.m_iStepsCounter;
	m_iJumpsCounter=rhs.m_iJumpsCounter;
	m_iStepSize=rhs.m_iStepSize;

	m_bDead=rhs.m_bDead;
}

Ant& Ant::operator=(const Ant& rhs)
{
	m_position=rhs.m_position;
	m_orientation=rhs.m_orientation;
	
	for(int i=0; i<3; i++)
	{
		m_memory[i]=rhs.m_memory[i];
	}

	m_iStepsCounter=rhs.m_iStepsCounter;
	m_iJumpsCounter=rhs.m_iJumpsCounter;
	m_iStepSize=rhs.m_iStepSize;

	m_bDead=rhs.m_bDead;

	return *this;
}

void Ant::Update()
{
	if(m_bDead)
	{
		return;
	}

	if(Continue())
	{
		Mark();
		Move();
	}
	else
	{
		if(GradientTrackVanished())
		{
			Jump2LocalMaximum();
			m_iJumpsCounter++;
		}
		if(m_iJumpsCounter > m_pConfig->GetMaxJumps())
		{
			m_bDead=true;
		}
	}
}

void Ant::Mark()
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	SketchElement* pElement=m_pConfig->GetSketchElement();

	if(pElement==NULL)
	{
		AfxMessageBox(_T("Failed to find a matched Sketch Elemetn"));
		return;
	}

	int canvas_width=m_pSketcher->GetWidth();
	int canvas_height=m_pSketcher->GetHeight();

	pElement->SetDrawConstraint(canvas_width, canvas_height);

	if(m_pConfig->GetColorCopy()==AntColonyConfiguration::COLORCOPY_RGB)
	{
		pElement->SetColor(m_pSketcher->SampleColor(x, y));
	}
	else if(m_pConfig->GetColorCopy() == AntColonyConfiguration::COLORCOPY_LUMINANCE)
	{
		int l=m_pSketcher->GetLuminance(x, y);
		pElement->SetColor(RGB(l, l, l));
	}
	pElement->SetPosition(x, y);
	pElement->SetOrientation(m_orientation);

	m_pSketcher->Draw(pElement);

	delete pElement;
	pElement=NULL;
}

void Ant::Move()
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	float prev_angle=m_orientation.GetAngle();

	m_orientation=m_pSketcher->GetDirection(x, y).Normalize();

	float curr_angle=m_orientation.GetAngle();

	m_prev_position=m_position;
	m_position += (m_orientation * m_iStepSize);

	m_iStepsCounter++;

	m_memory[0]=m_memory[1];
	m_memory[1]=m_memory[2];

	m_memory[2]=curr_angle - prev_angle;
}

void Ant::Start(AntColonyConfiguration* pConfig, SketcherEngine* pSketcher)
{
	m_pConfig=pConfig;
	m_pSketcher=pSketcher;
	m_bDead=false;

	int canvas_width=pSketcher->GetWidth();
	int canvas_height=pSketcher->GetHeight();

	float T0=m_pConfig->GetT0();
	float norm=0;
	do{
		m_position.SetX(canvas_width * RandomEngine->NextFloat());
		m_position.SetY(canvas_height * RandomEngine->NextFloat());

		int x=static_cast<int>(m_position.GetX());
		int y=static_cast<int>(m_position.GetY());

		norm=m_pSketcher->GetGradientNorm(x, y);
	}while(norm > T0);

	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	m_P0=m_position;

	m_L0=static_cast<float>(m_pSketcher->GetLuminance(x, y));

	m_iStepSize=m_pConfig->GetStepSize();
	int iMarkingBehavior=m_pConfig->GetMarkingBehavior();

	m_fAlpha=m_pConfig->GetMarkAngle();

	ComputeGap();
	ComputeGnorm();

	m_iTurnCounter=0;

	while(!m_bDead)
	{
		switch(iMarkingBehavior)
		{
		case AntColonyConfiguration::MARKINGBEHAVIOR_EDGEDRAWING:
			Update();
			break;
		case AntColonyConfiguration::MARKINGBEHAVIOR_FILLINGHATCHING:
			Fill_Hatch_Update();
			break;
		default:
			Update();
			break;
		}
	}
}

bool Ant::GradientTrackVanished(void)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	float norm=m_pSketcher->GetGradientNorm(x, y);

	return norm < m_pConfig->GetT1();
}

void Ant::Jump2LocalMaximum(void)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	int canvas_width=m_pSketcher->GetWidth();
	int canvas_height=m_pSketcher->GetHeight();

	float max_norm=m_pConfig->GetT1();

	bool bLocalPeakFound=false;

	Vec2f pos=m_position;
	for(int i=-5; i<=5; i++)
	{
		int xx=x + i;
		if(xx < 0)
		{
			continue;
		}
		else if(xx >= canvas_width)
		{
			break;
		}
		for(int j=-5; j<5; j++)
		{
			int yy=y + j;
			if(yy < 0)
			{
				continue;
			}
			else if(yy >= canvas_height)
			{
				break;
			}
			if(!WithinJumpRegion(m_position, xx, yy))
			{
				continue;
			}
			float norm=m_pSketcher->GetGradientNorm(xx, yy);
			if(norm > max_norm)
			{
				bLocalPeakFound=true;
				max_norm=norm;
				pos.SetX(static_cast<float>(xx));
				pos.SetY(static_cast<float>(yy));				
			}
		}
	}

	if(bLocalPeakFound)
	{
		m_position=pos;
		//gDisplay << "Local Peak Found" << std::endl;
	}
}

float Ant::GetCurrentTurn(void)
{
	return m_memory[3];
}

bool Ant::Continue(void)
{
	int iMaxSteps=m_pConfig->GetMaxSteps();
	if(m_iStepsCounter >= iMaxSteps)
	{
		return false;
	}

	float fSharpTurnThreshold=m_pConfig->GetSharpTurnThreshold();
	if(m_memory[3] >= fSharpTurnThreshold)
	{
		return false;
	}

	if(IsOutsideCanvas(m_position))
	{
		return false;
	}

	bool bContinue=!GradientTrackVanished();

	return bContinue;
}

bool Ant::IsOutsideCanvas(int x, int y)
{
	int canvas_width=m_pSketcher->GetWidth();
	int canvas_height=m_pSketcher->GetHeight();

	if((x < 0) || (x >= canvas_width) || (y < 0) ||  (y >= canvas_height))
	{
		return true;
	}
	return false;
}

bool Ant::IsOutsideCanvas(const Vec2f& pos)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());
	
	return IsOutsideCanvas(x, y);
}

void Ant::ComputeGap(void)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	if(IsOutsideCanvas(x, y))
	{
		return;
	}

	float Llocal=static_cast<float>(m_pSketcher->GetLuminance(x, y));
	m_Lgap=Llocal - m_L0;
}

bool Ant::WithinJumpRegion(const Vec2f& origin, int x, int y)
{
	float fSharpTurnThreshold=m_pConfig->GetSharpTurnThreshold() * 3;
	if(fSharpTurnThreshold > 90)
	{
		fSharpTurnThreshold=90;
	}

	float iJumpRadius=static_cast<float>(m_pConfig->GetJumpRadius());

	Vec2f v((float)x, (float)y);

	Vec2f disp=v - origin;

	if(disp.Length() <= iJumpRadius)
	{
		float fAngle=abs(disp.GetAngle(Vec2f::ANGLERANGE_FROM_M180_TO_P180));
		if(fAngle<= fSharpTurnThreshold)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void Ant::Fill_Hatch_Update(void)
{
	if(m_bDead)
	{
		return;
	}

	if(Fill_Hatch_Continue())
	{
		Fill_Hatch_Mark();
		Fill_Hatch_Move();
		ComputeGap();
		ComputeGnorm();

		m_iStepsCounter++;
	}
	else
	{
		float Thatch=m_pConfig->GetThatch();
		m_iTurnCounter++;
		if(m_iTurnCounter==1)
		{
			m_position=m_P0;
			m_fAlpha= - m_pConfig->GetMarkAngle();
			ComputeGap();
			ComputeGnorm();
		}
		else if(m_iTurnCounter==2)
		{
			if(m_L0 < Thatch)
			{
				m_position=m_P0;
				m_fAlpha = m_pConfig->GetMarkAngle() + 90;
				ComputeGap();
				ComputeGnorm();
			}
		}
		else if(m_iTurnCounter==3)
		{
			if(m_L0 < Thatch)
			{
				m_position=m_P0;
				m_fAlpha = - (m_pConfig->GetMarkAngle() + 90);
				ComputeGap();
				ComputeGnorm();
			}
		}
		else
		{
			m_bDead=true;
		}
	}
}

bool Ant::Fill_Hatch_Continue(void)
{
	float Tgap=m_pConfig->GetTgap();
	float T0=m_pConfig->GetT0();
	int iMaxSteps=m_pConfig->GetMaxSteps();

	if(m_Lgap < Tgap && m_Gnorm < T0 && m_iStepsCounter < iMaxSteps)
	{
		return true;
	}

	return false;
}

void Ant::ComputeGnorm(void)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	if(IsOutsideCanvas(x, y))
	{
		return;
	}

	m_Gnorm=m_pSketcher->GetGradientNorm(x, y);
}

void Ant::Fill_Hatch_Mark(void)
{
	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	SketchElement* pElement=m_pConfig->GetSketchElement();

	if(pElement==NULL)
	{
		AfxMessageBox(_T("Failed to find a matched Sketch Elemetn"));
		return;
	}

	pElement->SetMarkAngle(m_fAlpha);
	pElement->SetDirectedDraw(false);

	int canvas_width=m_pSketcher->GetWidth();
	int canvas_height=m_pSketcher->GetHeight();

	pElement->SetDrawConstraint(canvas_width, canvas_height);

	if(m_pConfig->GetColorCopy()==AntColonyConfiguration::COLORCOPY_RGB)
	{
		pElement->SetColor(m_pSketcher->SampleColor(x, y));
	}
	else if(m_pConfig->GetColorCopy() == AntColonyConfiguration::COLORCOPY_LUMINANCE)
	{
		int l=m_pSketcher->GetLuminance(x, y);
		pElement->SetColor(RGB(l, l, l));
	}
	pElement->SetPosition(x, y);

	m_pSketcher->Draw(pElement);

	delete pElement;
	pElement=NULL;
}

void Ant::Fill_Hatch_Move(void)
{
	const float PI=3.1415926f;
	float fStepSize=static_cast<float>(m_iStepSize);

	m_prev_position=m_position;

	float rad=PI * RandomEngine->NextFloat();
	Vec2f v(fStepSize * cos(rad), fStepSize * sin(rad));
	m_position+=v;
}
