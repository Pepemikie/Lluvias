#ifndef MOON_H
#define MOON_H

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "types.h"

typedef struct _Moon Moon;

Moon* moon_create();

void moon_destroy(Moon *moon);

Status moon_update(Moon *moon, time_t now);

Phases moon_get_phase(Moon *moon);

Cycle moon_get_cycle(Moon *moon);

int moon_get_days_until_full(Moon *moon);

int moon_get_days_until_new(Moon *moon);

#ifdef DEBUG
void moon_print(Moon *moon);
#endif
#endif /* MOON_H */