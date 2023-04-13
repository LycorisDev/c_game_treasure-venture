#include "../headers/rng.h"

int get_random_number_minmax(const int min, const int max)
{
    int seed = time(NULL);
    return ((((seed << 13) ^ seed) * (((seed << 13) ^ seed) * ((seed << 13) ^ seed) * 15731 + 789221) + 1376312589) & 0x7fffffff) % (max - min + 1) + min;
}

