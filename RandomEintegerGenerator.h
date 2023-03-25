#pragma once

#include "Histogram.h"

/**
   *    RandomEintegerGenerator class to generate random EInteger values
   */
class RandomEintegerGenerator : public Hist::RandomEintegerGeneratorBase
{
public:
    RandomEintegerGenerator() {}
    // Returns a pseudo-random EInteger value
    Hist::EInteger operator()() override;
};
