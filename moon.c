
/**
 * @file moon.c
 * @author José Miguel Romero Oubiña
 * @brief Implementación de las funciones para obtener la información de la luna
 * @version 0.1
 * @date 2026-07-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "moon.h"

/** @brief Número de días en un ciclo lunar */
#define MOON_CYCLE_DAYS 29.53058867
/** @brief Referencia para luna nueva */
#define REF_NEW_MOON 947182440

struct _Moon {
   Phases phase;
   Cycle cycle;
   int days_until_full;
   int days_until_new;
};

/* PRIVADAS */
/**
 * @brief Calcula la fase de la luna en función de la fecha actual
 * 
 * @param now hora en formato time_t
 * @return Fase de la luna 
 */
static Phases moon_calculate_phase(time_t now) {
    double days_since_ref_new_moon = 0;
    double phase =  0;

    days_since_ref_new_moon = (difftime(now, (time_t)REF_NEW_MOON) / DAY_IN_SEC);
    phase = fmod(days_since_ref_new_moon, MOON_CYCLE_DAYS);

    if(phase < 0) phase += MOON_CYCLE_DAYS;

    if(phase < 1.84566) return NEW;
    else if(phase < 5.53699) return CRESCENT;
    else if(phase < 9.22831) return QUARTER;
    else if(phase < 12.91963) return GIBBOUS;
    else if(phase < 16.61096) return FULL;
    else if(phase < 20.30228) return GIBBOUS;
    else if(phase < 23.99361) return QUARTER;
    else if(phase < 27.68493) return CRESCENT;

    return NEW;
}

/** 
 * @brief Calcula el ciclo de la luna en función de la fecha actual
 * 
 * @param now hora en formato time_t
 * @return Ciclo de la luna
 */
static Cycle moon_calculate_cycle(time_t now) {
    double days_since_ref_new_moon = 0;
    double position = 0;

    days_since_ref_new_moon = (difftime(now, (time_t)REF_NEW_MOON) / DAY_IN_SEC);
    position = fmod(days_since_ref_new_moon, MOON_CYCLE_DAYS);
    
    if(position < 0) position += MOON_CYCLE_DAYS;

    if(position < MOON_CYCLE_DAYS / 2.0) return WAXING;
    return WANING;
}

/** 
 * @brief Calcula el número de días hasta el pleno de la luna
 * 
 * @param now hora en formato time_t
 * @return Número de días hasta el pleno
 */
static int moon_calculate_days_until_full(time_t now) {
    double days_since_ref_new_moon = 0;
    double position = 0;
    double half = 0;

    days_since_ref_new_moon = (difftime(now, (time_t)REF_NEW_MOON) / DAY_IN_SEC);
    position = fmod(days_since_ref_new_moon, MOON_CYCLE_DAYS);

    if(position < 0) position += MOON_CYCLE_DAYS;

    half = MOON_CYCLE_DAYS / 2.0;

    if(position < half) return (int)(half - position);
    return (int)((half + MOON_CYCLE_DAYS) - position);
}

/** 
 * @brief Calcula el número de días hasta el nuevo de la luna
 * 
 * @param now hora en formato time_t
 * @return Número de días hasta el nuevo
 */
static int moon_calculate_days_until_new(time_t now) {
    double days_since_ref_new_moon = 0;
    double position = 0;

    days_since_ref_new_moon = (difftime(now, (time_t)REF_NEW_MOON) / DAY_IN_SEC);
    position = fmod(days_since_ref_new_moon, MOON_CYCLE_DAYS);

    if(position < 0) position += MOON_CYCLE_DAYS;

    return (int)(MOON_CYCLE_DAYS - position);
}

/* PÚBLICAS */
/* Crea una nueva instancia de la luna */
Moon* moon_create() {
    Moon *moon = NULL;

    moon = (Moon*) calloc (1, sizeof(Moon));
    if(!moon) return NULL;

    moon->phase = UNKNOWN_PHASE;
    moon->cycle = UNKNOWN_CYCLE;
    moon->days_until_full = -1;
    moon->days_until_new = -1;

    return moon;
}

/* Destruye una instancia de la luna */
void moon_destroy(Moon *moon) {
    if(!moon) return;

    free(moon);
    moon = NULL;
}

/* Actualiza la información de la luna */
Status moon_update(Moon *moon, time_t now) {
    if(!moon) return ERROR;
    if(now == (time_t)-1) return ERROR;

    moon->phase = moon_calculate_phase(now);
    moon->cycle = moon_calculate_cycle(now);
    if(moon->phase == UNKNOWN_PHASE || moon->phase == NEW || moon->phase == FULL) {
        moon->cycle = UNKNOWN_CYCLE;
    }
    moon->days_until_full = moon_calculate_days_until_full(now);
    moon->days_until_new = moon_calculate_days_until_new(now);

    return OK;
}

/* Obtiene la fase de la luna */
Phases moon_get_phase(Moon *moon) {
    if(!moon) return UNKNOWN_PHASE;

    return moon->phase;
}

/* Obtiene el ciclo de la luna */
Cycle  moon_get_cycle(Moon *moon) {
    if(!moon) return UNKNOWN_CYCLE;

    return moon->cycle;
}

/* Obtiene el número de días hasta el pleno de la luna */
int moon_get_days_until_full(Moon *moon) {
    if(!moon) return -1;

    return moon->days_until_full;
}

/* Obtiene el número de días hasta el nuevo de la luna */
int moon_get_days_until_new(Moon *moon) {
    if(!moon) return -1;

    return moon->days_until_new;
}

#ifdef DEBUG
/* Imprime la información de la luna */
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
    printf("Days until full: %d\n", moon->days_until_full);
    printf("Days until new: %d\n", moon->days_until_new);
}
#endif