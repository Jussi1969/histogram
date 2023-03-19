#include "RandomEintegerGenerator.h"
#include <random>

Hist::EInteger RandomEintegerGenerator::operator()()
{
	int iRnd = rand() % 4 + 1;
	return (Hist::EInteger)iRnd;
}
