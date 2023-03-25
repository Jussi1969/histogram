#include "RandomEintegerGenerator.h"
#include <random>

Hist::EInteger RandomEintegerGenerator::operator()()
{
	int iRnd = rand() % 5;
	return (Hist::EInteger)iRnd;
}
