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
#include <time.h>
#include "clock.h"

time_t clock_now() {
    time_t now = time(NULL);
    if(now == ((time_t) - 1)) return (time_t) - 1;

    return now;
}

struct tm clock_get_local(time_t now) {
    struct tm resultado;

    localtime_r(&now, &resultado);
    return resultado;
}
