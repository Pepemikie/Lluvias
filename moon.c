
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "moon.h"

struct _Moon {
   Phases phase;
   Cycle cycle;
};

Moon* moon_create() {
    Moon *moon = NULL;

    moon = (Moon*) calloc (1, sizeof(Moon));
    if(!moon) return NULL;

    moon->phase = UNKNOWN_PHASE;
    moon->cycle = UNKNOWN_CYCLE;

    return moon;
}

void moon_destroy(Moon *moon) {
    if(!moon) return;

    free(moon);
    moon = NULL;
}

Status moon_update(Moon *moon, time_t now) {
    
}

Phases moon_get_phase(Moon *moon) {
    if(!moon) return UNKNOWN_PHASE;

    return moon->phase;
}

Cycle  moon_get_cycle(Moon *moon) {
    if(!moon) return UNKNOWN_CYCLE;

    return moon->cycle;
}

#ifdef DEBUG
void moon_print(Moon *moon) {
    char phase[MAX_CHAR];
    char cycle[MAX_CHAR];
    
    if(moon->phase == UNKNOWN_PHASE) strcpy(phase, "UNKNOWN_PHASE");
    if(moon->phase == NEW) strcpy(phase, "NEW");
    if(moon->phase == CRESCENT) strcpy(phase, "CRESCENT");
    if(moon->phase == QUARTER) strcpy(phase, "QUARTER");
    if(moon->phase == GIBBOUS) strcpy(phase, "GIBBOUS");
    if(moon->phase == FULL) strcpy(phase, "FULL");

    if(moon->cycle == UNKNOWN_CYCLE) strcpy(cycle, "UNKNOWN_CYCLE");
    if(moon->cycle == WAXING) strcpy(cycle, "WAXING");
    if(moon->cycle == WANING) strcpy(cycle, "WANING");

    printf("Moon phase: %s\n", phase);
    printf("Moon cycle: %s\n", cycle);

}
#endif