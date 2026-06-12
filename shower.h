#ifndef SHOWER_H
#define SHOWER_H

#include <stdio.h>
#include <time.h>

#include "types.h"

typedef struct _Shower Shower;

Shower* shower_create();

void shower_destroy(Shower *shower);

ShowerIntensity shower_get_intensity(Shower *shower);

char* shower_get_name(Shower *shower);

int shower_get_peak_hour(Shower *shower);

#ifdef DEBUG
void shower_print(Shower *shower);
#endif
#endif /* SHOWER_H */