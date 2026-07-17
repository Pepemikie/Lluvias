/**
 * @file clock.h
 * @author José Miguel Romero Oubiña
 * @brief Funciones para obtener la hora actual y convertirla a hora local
 * @version 0.1
 * @date 2026-07-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef CLOCK_H
#define CLOCK_H

#include "types.h"
#include <time.h>

/**
 * @brief Obtiene la hora actual en formato time_t
 * 
 * @return time_t con la hora actual, o (time_t)-1 si hay un error
 */
time_t clock_now();

/**
 * @brief Convierte una hora en formato time_t a hora local
 * 
 * @param now hora en formato time_t
 * @return struct tm con la hora local
 */
struct tm clock_get_local(time_t now);

#endif