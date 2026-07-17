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
    Moon *moon = NULL; /* Para saber la luna que habrá en el evento */
    Moon *moon_now = NULL; /* Para saber la luna que habrá hoy */
    time_t now = (time_t) - 1;
    struct tm local;
    time_t fecha_evento = (time_t) - 1;
    int boton = -1;

    #pragma region Inicialización de módulos
    /* Moon de evento */
    moon = moon_create();
    if(!moon) {
        printf("-- ERROR de memoria: Módulo Moon --\n");
        return -1;
    }

    /* Moon de hoy */
    moon_now = moon_create();
    if(!moon_now) {
        printf("-- ERROR de memoria: Módulo Moon --\n");
        moon_destroy(moon);
        return -1;
    }

    /* Shower */
    shower = shower_create();
    if(!shower) {
        printf("-- ERROR de memoria: Módulo Shower --\n");
        moon_destroy(moon);
        moon_destroy(moon_now);
        return -1;
    }

    #pragma endregion

    #pragma region Carga de datos
    /* Carga de datos del fichero shower.dat */
    if(shower_load(shower) == ERROR) {
        printf("-- ERROR al cargar el fichero de datos --\n");
        moon_destroy(moon);
        moon_destroy(moon_now);
        shower_destroy(shower);
        return -1;
    }

    /* Consigue la hora actual */
    now = clock_now();
    if(now == ((time_t) - 1)) {
        printf("-- ERROR al conseguir los segundos actuales: Módulo Clock --\n");
        moon_destroy(moon);
        moon_destroy(moon_now);
        shower_destroy(shower);
        return -1;
    }

    /* Convierte la hora actual en una estructura tm para desglosarla */
    local = clock_get_local(now);

    #pragma endregion

    do{   
        #pragma region Menú
        printf("\n- - - - - - - - - - - - - - - - - -\n");
        printf("Que evento prefiere:\n");
        printf("    1. Proximo evento\n");
        printf("    2. Luna de hoy\n");
        printf("    3. Salir\n> ");
        scanf(" %d", &boton);
        #pragma endregion

        switch(boton) {
            case 1: {
                if(shower_update(shower, local) == ERROR) {
                    printf("-- ERROR al buscar fecha inicial: Módulo Shower --\n");
                    moon_destroy(moon);
                    moon_destroy(moon_now);
                    shower_destroy(shower);
                    return -1;
                }
                do {
                    fecha_evento = shower_get_event_time(shower);
                    if(moon_update(moon, fecha_evento) == ERROR) {
                        printf("-- ERROR al cargar la moon: Módulo Moon --\n");
                        moon_destroy(moon);
                        moon_destroy(moon_now);
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

                printf("\n---------------------------------\n");
                printf("- SHOWER -\n\n");
                printf("Name: %s\n", shower_get_name(shower));
                printf("Intensity: ");
                    switch(shower_get_intensity(shower)) {
                        case UNKNOWN_INTENSITY:
                            printf("UNKNOWN_INTENSITY\n");
                            break;
                        case NO_SHOWER:
                            printf("NO_SHOWER\n");
                            break;
                        case MINOR:     
                            printf("MINOR\n");
                            break;
                        case MODERATE:
                            printf("MODERATE\n");
                            break;
                        case MAJOR:
                            printf("MAJOR\n");
                            break;
                        default:
                            printf("???\n");
                            break;
                }
                printf("Visibility: %s\n", shower_get_visible(shower) ? "TRUE" : "FALSE");
                printf("Peak hour: 0%d\n", shower_get_peak_hour(shower));
                printf("Event time: %s", ctime(&fecha_evento));
                printf("Days until: %d\n", shower_get_days_until(shower));
                printf("Total num of showers: %d\n", shower_get_num_showers(shower));
                printf("Shower index: %d/%d\n\n", shower_get_next_index(shower), shower_get_num_showers(shower));

                printf("---------------------------------\n");
                printf("- MOON AT THE EVENT -\n\n");
                printf("Phase: ");
                    switch(moon_get_phase(moon)) {
                        case UNKNOWN_PHASE:
                            printf("UNKNOWN_PHASE\n");
                            break;
                        case NEW:
                            printf("NEW\n");
                            break;
                        case CRESCENT:
                            printf("CRESCENT\n");
                            break;
                        case QUARTER:
                            printf("QUARTER\n");
                            break;
                        case GIBBOUS:
                            printf("GIBBOUS\n");
                            break;
                        case FULL:
                            printf("FULL\n");
                            break;
                        default:
                            printf("???\n");
                            break;
                }
                printf("Cycle: ");
                    switch(moon_get_cycle(moon)) {
                        case UNKNOWN_CYCLE:
                            printf("UNKNOWN_CYCLE\n");
                            break;
                        case WAXING:
                            printf("WAXING\n");
                            break;
                        case WANING:
                            printf("WANING\n");
                            break;
                        default:
                            printf("???\n");
                            break;
                }
                break;
            }
            case 2: {
                if(moon_update(moon_now, now) == ERROR) {
                    printf("-- ERROR al cargar la moon_now: Módulo Moon --\n");
                    moon_destroy(moon);
                    moon_destroy(moon_now);
                    shower_destroy(shower);
                    return -1;
                }       

                printf("---------------------------------\n");
                printf("- MOON -\n\n");  
                printf("Phase now: ");
                    switch(moon_get_phase(moon_now)) {
                        case UNKNOWN_PHASE:
                            printf("UNKNOWN_PHASE\n");
                            break;
                        case NEW:
                            printf("NEW\n");
                            break;
                        case CRESCENT:
                            printf("CRESCENT\n");
                            break;
                        case QUARTER:
                            printf("QUARTER\n");
                            break;
                        case GIBBOUS:
                            printf("GIBBOUS\n");
                            break;
                        case FULL:
                            printf("FULL\n");
                            break;
                        default:
                            printf("???\n");
                            break;
                }
                printf("Cycle now: ");
                    switch(moon_get_cycle(moon_now)) {
                        case UNKNOWN_CYCLE:
                            printf("UNKNOWN_CYCLE\n");
                            break;
                        case WAXING:
                            printf("WAXING\n");
                            break;
                        case WANING:
                            printf("WANING\n");
                            break;
                        default:
                            printf("???\n");
                            break;
                }
                printf("Days until full: %d\n", moon_get_days_until_full(moon_now));
                printf("Days until new: %d\n", moon_get_days_until_new(moon_now));
            
                break;
            }
            case 3: {
                moon_destroy(moon);
                moon_destroy(moon_now);
                shower_destroy(shower);

                break;
            }
            default: {
                printf("Escoge un valor correcto\n");
                break;
            }
        }
    }while(boton != 3);

    return 0;
}