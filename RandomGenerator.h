#pragma once
#include "afx.h"

class RandomGenerator :
	public CObject
{
private:
	RandomGenerator(void);
	RandomGenerator(const RandomGenerator& rhs) { }
	RandomGenerator& operator=(const RandomGenerator& rhs) { return *this; }

public:
	static RandomGenerator* Instance();
	~RandomGenerator(void);

public:
	double NextDouble() const;
	float NextFloat() const;
};

#define RandomEngine RandomGenerator::Instance()
