/*
Funciones que pueden interesar:

https://algoritmos9511.gitlab.io/_downloads/e1ac04d57c11925f0283040c533417bb/tiempo.pdf

asctime ()- Convertir hora en serie de caracteres
    char *asctime(const struct tm *time);

ctime ()- Convertir hora en serie de caracteres
    char *ctime(const time_t *time);

time ()- Determinar hora actual
    time_t time(time_t *timeptr);

time_t

struct tm
    tiene todo de segudnos min horas dia etc separado

https://www.ibm.com/docs/es/i/7.5.0?topic=functions-localtime-r-convert-time-restartable

*/

/**
 * @file clock.c
 * @author José Miguel Romero Oubiña
 * @brief Funciones para obtener la hora actual y convertirla a hora local
 * @version 0.1
 * @date 2026-07-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <time.h>
#include "clock.h"

/* Obtiene la hora actual en formato time_t */
time_t clock_now() {
    time_t now = time(NULL);
    if(now == ((time_t) - 1)) return (time_t) - 1;

    return now;
}

/* Convierte una hora en formato time_t a hora local */
struct tm clock_get_local(time_t now) {
    struct tm resultado;

    localtime_r(&now, &resultado);
    return resultado;
}
