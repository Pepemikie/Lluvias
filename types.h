#ifndef TYPES_H
#define TYPES_H

typedef enum {FALSE, TRUE} Bool;

typedef enum {ERROR, OK} Status;

typedef enum {UNKNOWN_PHASE, NEW, CRESCENT, QUARTER, GIBBOUS, FULL} Phases;

typedef enum {UNKNOWN_CYCLE, WAXING, WANING} Cycle;

#endif