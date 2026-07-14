#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "shower.h"
#include "moon.h"
#include "clock.h"
/*#include "arduino.h"*/

int main() {
    Shower *shower = NULL;
    Moon *moon = NULL;
    time_t now = (time_t) - 1;
    struct tm local;
    time_t fecha_evento = (time_t) - 1;

    printf("\n::ATHMOSPHERE::\n\n");

    moon = moon_create();
    if(!moon) {
        printf("-- ERROR de memoria: Módulo Moon --\n");
        return -1;
    }

    shower = shower_create();
    if(!shower) {
        printf("-- ERROR de memoria: Módulo Shower --\n");
        moon_destroy(moon);
        return -1;
    }

    if(shower_load(shower) == ERROR) {
        printf("-- ERROR al cargar el fichero de datos --\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }

    now = clock_now();
    if(now == ((time_t) - 1)) {
        printf("-- ERROR al conseguir los segundos actuales: Módulo Clock --\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }
    local = clock_get_local(now);

    if(shower_update(shower, local) == ERROR) {
        printf("-- ERROR al buscar fecha inicial: Módulo Shower --\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }

    /* Aqui, shower va a tener la fecha del primero si o si, y cuando entre en el
    do while, el primero que comprobara sera el de dentro del shower, que es el primero*/

    do {
        fecha_evento = shower_get_event_time(shower);
        if(moon_update(moon, fecha_evento) == ERROR) {
            printf("-- ERROR al cargar la moon: Módulo Moon --\n");
            moon_destroy(moon);
            shower_destroy(shower);
            return -1;
        }

        shower_update_visibility(shower, moon_get_phase(moon));

        if(shower_get_visible(shower) == FALSE) {
            if(shower_next(shower, local) == ERROR) {
                break;
            }
        }

    }while(shower_get_visible(shower) == FALSE);

    printf("- SHOWER -\n\n");
    printf("\nName: %s\n", shower_get_name(shower));
    printf("Intensity: %d\n", shower_get_intensity(shower));
    printf("Visibility: %d\n", shower_get_visible(shower));
    printf("Peak hour: 0%d\n", shower_get_peak_hour(shower));
    printf("Days until: %d\n", shower_get_days_until(shower));
    printf("Total num of showers: %d\n", shower_get_num_showers(shower));
    printf("- MOON -\n\n");
    printf("Phase: %d\n", moon_get_phase(moon));
    printf("Cycle: %d\n", moon_get_cycle(moon));
    printf("Days until full: %d\n", moon_get_days_until_full(moon));
    printf("Days until new: %d\n", moon_get_days_until_new(moon));

    moon_destroy(moon);
    shower_destroy(shower);

    return 0;
}