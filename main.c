#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "shower.h"
#include "moon.h"
/*#include "clock.h"
#include "arduino.h"*/

int main() {
    Shower *shower = NULL;
    Moon *moon = NULL;
    struct tm now;
    time_t t;

    moon = moon_create();
    if(!moon) {
        printf("ERROR de memoria Moon\n");
        return -1;
    }

    shower = shower_create();
    if(!shower) {
        printf("ERROR de memoria Shower\n");
        moon_destroy(moon);
        return -1;
    }

    if(shower_load(shower) == ERROR) {
        printf("ERROR al cargar el fichero de datos\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }

    t = time(NULL);
    localtime_r(&t, &now);

    if(moon_update(moon, t) == ERROR) {
        printf("ERROR en la Moon\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }

    if(shower_update(shower, now, moon_get_phase(moon)) == ERROR) {
        printf("ERROR al buscar fecha\n");
        moon_destroy(moon);
        shower_destroy(shower);
        return -1;
    }

    

    printf("%s\n", shower_get_name(shower));
    printf("%d\n", shower_get_intensity(shower));
    printf("%d\n", shower_get_visible(shower));
    printf("%d\n", shower_get_peak_hour(shower));
    printf("%d\n", shower_get_days_until(shower));
    printf("%d\n----------", shower_get_num_showers(shower));
    printf("%d\n", moon_get_phase(moon));
    printf("%d\n", moon_get_cycle(moon));
    printf("%d\n", moon_get_days_until_full(moon));
    printf("%d\n", moon_get_days_until_new(moon));

    moon_destroy(moon);
    shower_destroy(shower);

    return 0;
}