#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "shower.h"
/*#include "clock.h"
#include "moon.h"
#include "arduino.h"*/

int main() {
    Shower *shower = NULL;
    struct tm now;
    time_t t;

    shower = shower_create();
    if(!shower) {
        printf("ERROR de memoria\n");
        return -1;
    }

    if(shower_load(shower) == ERROR) {
        printf("ERROR al cargar el fichero de datos\n");
        shower_destroy(shower);
        return -1;
    }

    t = time(NULL);
    localtime_r(&t, &now);

    if(shower_update(shower, now, FULL) == ERROR) {
        printf("ERROR al buscar fecha\n");
        shower_destroy(shower);
        return -1;
    }

    printf("%s\n", shower_get_name(shower));
    printf("%d\n", shower_get_intensity(shower));
    printf("%d\n", shower_get_visible(shower));
    printf("%d\n", shower_get_peak_hour(shower));
    printf("%d\n", shower_get_days_until(shower));
    printf("%d\n", shower_get_num_showers(shower));

    shower_destroy(shower);

    return 0;
}