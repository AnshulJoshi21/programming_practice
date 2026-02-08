#include "utils.h"

#include <cassert>
#include <random>

float random_uniform(float min, float max)
{
    assert(min < max);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(min, max);

    return distr(gen);
}
