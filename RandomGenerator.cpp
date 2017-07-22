#include "StdAfx.h"
#include "RandomGenerator.h"
#include <ctime>
#include <cstdlib>

RandomGenerator::RandomGenerator(void)
{
	srand(static_cast<time_t>(time(NULL)));
}

RandomGenerator::~RandomGenerator(void)
{
}

RandomGenerator* RandomGenerator::Instance()
{
	static RandomGenerator theInstance;
	return &theInstance;
}

double RandomGenerator::NextDouble() const
{
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX+1);
}

float RandomGenerator::NextFloat() const
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX+1);
}