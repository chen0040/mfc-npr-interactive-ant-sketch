#pragma once
#include "afx.h"
#include <list>

class SketcherEngine;
class AntColonyConfiguration;

class AntColony :
	public CObject
{
public:
	AntColony(void);
	~AntColony(void);
	
public:
	void DispatchAnt(SketcherEngine* pSketcher, AntColonyConfiguration*  pConfig);
	int GetRemainedAnts() const { return m_iRemainedAnts; }
	void SetRemainedAnts(int iVal) { m_iRemainedAnts=iVal; }
	int GetDeadAnts() const { return m_iDeadAnts; }

protected:
	int m_iRemainedAnts;
	int m_iDeadAnts;
public:
	void Reset(AntColonyConfiguration* pConfig);
	bool IsNull(void) const;
};

