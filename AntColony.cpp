#include "StdAfx.h"
#include "AntColony.h"
#include "Ant.h"
#include "SketcherEngine.h"
#include "AntColonyConfiguration.h"
#include "Display.h"

AntColony::AntColony(void)
: m_iRemainedAnts(0)
{
}

AntColony::~AntColony(void)
{
}

void AntColony::DispatchAnt(SketcherEngine* pSketcher, AntColonyConfiguration*  pConfig)
{
	if(m_iRemainedAnts <= 0)
	{
		return;
	}

	int iAntsPerExecution=pConfig->GetAntsPerExecution();
	int iAntsPerRefresh=pConfig->GetAntsPerRefresh();

	for(int i=0; i<iAntsPerExecution; i++)
	{
		Ant ant;
		ant.Start(pConfig, pSketcher);
		m_iRemainedAnts --;
		m_iDeadAnts++;
		if(m_iDeadAnts % iAntsPerRefresh == 0)
		{
			gDisplay.InvalidateView(FALSE);
		}
		if(m_iRemainedAnts <=0)
		{
			break;
		}
	}
}

void AntColony::Reset(AntColonyConfiguration* pConfig)
{
	m_iRemainedAnts=pConfig->GetColonySize();
	m_iDeadAnts=0;
}

bool AntColony::IsNull(void) const
{
	return m_iRemainedAnts <=0 ;
}
