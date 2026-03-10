#include "../include/utils.h"

#include <stdlib.h>

float random_uniform(float min, float max)
{
    float minimum, maximum;

    if (min < max) {
        minimum = min;
        maximum = max;
    } else if (max < min) {
        minimum = max;
        maximum = min;
    } else
        return min;

    return ((minimum) + ((float)rand() / RAND_MAX) * (maximum - minimum));
}
