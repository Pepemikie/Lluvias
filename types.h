#ifndef TYPES_H
#define TYPES_H

#define MAX_CHAR 32
#define DAY_IN_SEC 86400.0

typedef enum {FALSE, TRUE} Bool;

typedef enum {ERROR, OK} Status;

/* Moon */
typedef enum {UNKNOWN_PHASE, NEW, CRESCENT, QUARTER, GIBBOUS, FULL} Phases;

typedef enum {UNKNOWN_CYCLE, WAXING, WANING} Cycle;

/* Shower */
typedef enum {UNKNOWN_INTENSITY, NO_SHOWER, MINOR, MODERATE, MAJOR} ShowerIntensity;

#endif