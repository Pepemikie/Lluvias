#ifndef CLOCK_H
#define CLOCK_H

#include "types.h"
#include <time.h>

time_t clock_now();

struct tm clock_get_local(time_t now);

#endif