#pragma once
#include "afx.h"
#include "SketchElement.h"

class Ant;

class AntColonyConfiguration :
	public CObject
{
public:
	AntColonyConfiguration(void);
	~AntColonyConfiguration(void);

	int GetColonySize() const { return m_iColonySize; }
	int GetStepSize() const { return m_iStepSize; }
	float GetT0() const { return m_T0; }
	float GetT1() const { return m_T1; }
	float GetTgap() const { return m_Tgap; }
	float GetThatch() const { return m_Thatch; }
	int GetJumpRadius() const { return m_iJumpRadius; }
	int GetMaxSteps() const { return m_iMaxSteps; }
	int GetMaxJumps() const { return m_iMaxJumps; }
	float GetSharpTurnThreshold() const { return m_fSharpTurnThreshold; }
	int GetMarkLength() const { return m_iMarkLength; }
	int GetMarkThickness() const { return m_iMarkThickness; }
	float GetMarkAngle() const { return m_fMarkAngle; }
	int GetMarkShape() const { return m_iMarkShape; }
	int GetAntsPerExecution() const { return m_iAntsPerExecution; }
	bool GetDirectedDraw() const { return m_bDirectedDraw; }
	int GetColorCopy() const { return m_iColorCopy; }
	int GetAntsPerRefresh() const { return m_iAntsPerRefresh; }
	int GetMarkingBehavior() const { return m_iMarkingBehavior; }

	void SetColonySize(int iColonySize) { m_iColonySize = iColonySize; }
	void SetStepSize(int iStepSize) { m_iStepSize = iStepSize; }
	void SetT0(float T0) { m_T0 = T0; }
	void SetT1(float T1) { m_T1 = T1; }
	void SetTgap(float Tgap) { m_Tgap = Tgap; }
	void SetThatch(float Thatch) { m_Thatch = Thatch; }
	void SetJumpRadius(int iJumpRadius) { m_iJumpRadius = iJumpRadius; }
	void SetMaxSteps(int iMaxSteps) { m_iMaxSteps = iMaxSteps; }
	void SetMaxJumps(int iMaxJumps) { m_iMaxJumps = iMaxJumps; }
	void SetSharpTurnThreshold(float fSharpTurnThreshold) { m_fSharpTurnThreshold = fSharpTurnThreshold; }
	void SetMarkAngle(float angle) { m_fMarkAngle=angle; }
	void SetMarkLength(int len) { m_iMarkLength=len; }
	void SetMarkThickness(int t) { m_iMarkThickness = t; }
	void SetMarkShape(int iShape) { m_iMarkShape=iShape; }
	void SetAntsPerExecution(int iVal) { m_iAntsPerExecution=iVal; }
	void SetDirectedDraw(bool bDirected) { m_bDirectedDraw=bDirected; }
	void SetColorCopy(int iVal) { m_iColorCopy=iVal; }
	void SetAntsPerRefresh(int iVal) { m_iAntsPerRefresh=iVal; }
	void SetMarkingBehavior(int iVal) { m_iMarkingBehavior=iVal; }


public:
	static const int MARKSHAPE_LINE=0;
	static const int MARKSHAPE_CIRCLE=1;
	static const int MARKSHAPE_CROSS=2;

public:
	static const int COLORCOPY_RGB=0;
	static const int COLORCOPY_LUMINANCE=1;

public:
	static const int MARKINGBEHAVIOR_EDGEDRAWING=0;
	static const int MARKINGBEHAVIOR_FILLINGHATCHING=1;

public:
	int m_iMarkingBehavior;
	int m_iColorCopy;
	int m_iColonySize;
	int m_iStepSize;
	float m_T0;
	float m_T1;
	float m_Tgap;
	float m_Thatch;
	int m_iJumpRadius;
	int m_iMaxSteps;
	int m_iMaxJumps;
	float m_fSharpTurnThreshold;
	float m_fMarkAngle;
	int m_iMarkThickness;
	int m_iMarkShape;
	int m_iMarkLength;
	int m_iAntsPerExecution;
	int m_iAntsPerRefresh;
	bool m_bDirectedDraw;

public:
	bool Load(LPCTSTR pFilename);
	SketchElement* GetSketchElement();
};
