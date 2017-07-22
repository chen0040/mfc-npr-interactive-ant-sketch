#pragma once
#include "afx.h"
#include "Vec2f.h"

class AntColonyConfiguration;
class SketcherEngine;

class Ant :
	public CObject
{
public:
	Ant(void);
	~Ant(void);

public:
	Ant(const Ant& rhs);
	Ant& operator=(const Ant& rhs);

public:
	int GetStepsCounter() const { return m_iStepsCounter; }
	int GetJumpsCounter() const { return m_iJumpsCounter; }
	int GetStepSize() const { return m_iStepSize; }
	void SetStepSize(int val) { m_iStepSize=val; }

public:
	void Start(AntColonyConfiguration* pConfig, SketcherEngine* pSketcher);

public:
	void Update();

protected:
	void Mark();
	void Move();
	bool GradientTrackVanished(void);

protected:
	Vec2f m_position;
	Vec2f m_prev_position;
	Vec2f m_orientation;
	Vec2f m_P0;
	float m_memory[3];
	int m_iStepsCounter;
	int m_iJumpsCounter;
	int m_iStepSize;
	bool m_bDead;
	float m_L0;
	float m_fAlpha;
	float m_Lgap;
	float m_Gnorm;
	AntColonyConfiguration* m_pConfig;
	SketcherEngine* m_pSketcher;
	int m_iTurnCounter;

	void Jump2LocalMaximum(void);
public:
	float GetCurrentTurn(void);
protected:
	bool Continue(void);
	bool IsOutsideCanvas(int x, int y);
	bool IsOutsideCanvas(const Vec2f& pos);
	void ComputeGap(void);
	bool WithinJumpRegion(const Vec2f& origin, int x, int y);
	void Fill_Hatch_Update(void);
	bool Fill_Hatch_Continue(void);
	void ComputeGnorm(void);
	void Fill_Hatch_Mark(void);
	void Fill_Hatch_Move(void);
};
