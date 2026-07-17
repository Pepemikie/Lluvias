/**
 * @file moon.h
 * @author José Miguel Romero Oubiña
 * @brief Funciones para obtener la información de la luna
 * @version 0.1
 * @date 2026-07-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef MOON_H
#define MOON_H

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "types.h"

/** @brief Estructura para representar la luna */
typedef struct _Moon Moon;

/**
 * @brief Crea una nueva instancia de la luna
 * 
 * @return Puntero a la estructura Moon
 */
Moon* moon_create();

/**
 * @brief Destruye una instancia de la luna
 * 
 * @param moon puntero a la estructura Moon
 */
void moon_destroy(Moon *moon);

/**
 * @brief Actualiza la información de la luna
 * 
 * @param moon puntero a la estructura Moon
 * @param now hora en formato time_t
 * @return OK si sale bien, ERROR si algo sale mal
 */
Status moon_update(Moon *moon, time_t now);

/**
 * @brief Obtiene la fase de la luna
 * 
 * @param moon puntero a la estructura Moon
 * @return Fase de la luna
 */
Phases moon_get_phase(Moon *moon);

/**
 * @brief Obtiene el ciclo de la luna
 * 
 * @param moon puntero a la estructura Moon
 * @return Ciclo de la luna
 */
Cycle moon_get_cycle(Moon *moon);

/**
 * @brief Obtiene el número de días hasta el pleno de la luna
 * 
 * @param moon puntero a la estructura Moon
 * @return Número de días hasta el pleno
 */
int moon_get_days_until_full(Moon *moon);

/**
 * @brief Obtiene el número de días hasta el nuevo de la luna
 * 
 * @param moon puntero a la estructura Moon
 * @return Número de días hasta el nuevo
 */
int moon_get_days_until_new(Moon *moon);

#ifdef DEBUG
/** @brief Imprime la información de la luna
 * 
 * @param moon puntero a la estructura Moon
 */
void moon_print(Moon *moon);
#endif
#endif /* MOON_H */