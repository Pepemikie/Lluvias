#ifndef TYPES_H
#define TYPES_H

#define MAX_CHAR 32

typedef enum {FALSE, TRUE} Bool;

typedef enum {ERROR, OK} Status;

typedef enum {UNKNOWN_PHASE, NEW, CRESCENT, QUARTER, GIBBOUS, FULL} Phases;

typedef enum {UNKNOWN_CYCLE, WAXING, WANING} Cycle;

typedef enum {UNKNOWN_INTENSITY, NO_SHOWER, MINOR, MODERATE, MAJOR} ShowerIntensity;

#endif