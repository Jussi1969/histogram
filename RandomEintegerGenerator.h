#pragma once

#include "Histogram.h"

class RandomEintegerGenerator : public Hist::RandomEintegerGeneratorBase
{
public:
    RandomEintegerGenerator() {}
    // Returns a pseudo-random EInteger value
    Hist::EInteger operator()();
};
