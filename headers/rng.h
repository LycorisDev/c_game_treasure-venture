#ifndef RNG_H
#define RNG_H

#ifndef STANDARD_LIBRARY_TIME
#define STANDARD_LIBRARY_TIME
#include <time.h>
#endif

int get_random_number_minmax(const int min, const int max);

#endif

