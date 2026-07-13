/**
 * @file shower.c
 * @author José Miguel Romero Oubiña
 * @brief Implementación del modulo shower.c
 * @version 0.1
 * @date 2026-07-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "shower.h"

#define MAX_SHOWERS 1000
#define SHOWER_FILE "shower.dat"

typedef struct { /* Estructura para almacenar información de cada lluvia de estrellas sin procesar */
    char name[MAX_CHAR];
    int num_comets;
    int day;
    int month;
    int year;
    int peak_hour;
}ShowerArray;

/* Estructura para representar una lluvia de estrellas */
struct _Shower { /* Estructura con la informacion que se pasará a otros modulos */
    char shower_name[MAX_CHAR];
    ShowerIntensity intensity;
    Bool visible;
    int peak_hour;
    int days_until;
    ShowerArray showers[MAX_SHOWERS];
    int num_showers;
    //int next_index; /* Para futuro, poder ver las siguientes lluvias de estrellas */
};

/* PRIVADAS */
/**
 * @brief Convierte el numero de cometas a un rango de intensidad
 * 
 * @param num_comets numero de cometas
 * @return El rango de intensidad de la propia lluvia de estrellas 
 */
static ShowerIntensity num_comets_to_intensity(int num_comets) { /* Pasa el número de cometas a una intensidad definida */
    if(num_comets <= 10) return NO_SHOWER;
    else if(num_comets <= 50) return MINOR;
    else if(num_comets <= 100) return MODERATE;

    return MAJOR;
}

/*
Moon: UNKNOWN_PHASE, NEW, CRESCENT, QUARTER, GIBBOUS, FULL
Intensity: UNKNOWN_INTENSITY, NO_SHOWER, MINOR, MODERATE, MAJOR
*/

/**
 * @brief Determina si la lluvia es visible o no dependiendo de la fase lunar y la intensidad
 * 
 * @param intensity la intensidad de la lluvia
 * @param moon_phase la fase lunar
 * @return FALSE si no vale la pensa salir a verla, TRUE si vale la pena 
 */
static Bool shower_is_visible(ShowerIntensity intensity, Phases moon_phase) { /* Segun la fase lunar se decide si es visible o no, teniendo en cuenta su intensidad*/
    if(intensity == UNKNOWN_INTENSITY) return FALSE;
    if(moon_phase == UNKNOWN_PHASE) return FALSE;

    switch(intensity) {
        case MAJOR:
            if(moon_phase == FULL) return FALSE;
            return TRUE;
        case MODERATE:
            if(moon_phase == FULL) return FALSE;
            return TRUE;
        case MINOR:
            if(moon_phase == NEW || moon_phase == CRESCENT) return TRUE;
            return FALSE;
        case NO_SHOWER:
            return FALSE;
        default:
            return FALSE;
    }
}

/*
La estructura contiene los siguientes campos enteros:
tm_sec: Segundos después del minuto [0, 61] (hasta 61 para incluir segundos intercalares).
tm_min: Minutos después de la hora [0, 59].


tm_hour: Horas desde la medianoche [0, 23].
tm_mday: Día del mes [1, 31].
tm_mon: Meses desde enero [0, 11]. ¡Ojo! Enero es 0 y Diciembre es 11.
tm_year: Años desde 1900. Por ejemplo, para el año 2026, este campo almacena 126.


tm_wday: Días desde el domingo [0, 6] (siendo Domingo = 0).
tm_yday: Días desde el 1 de enero [0, 365].
tm_isdst: Indicador de horario de verano. 
Es >0 si está activo, 0 si no, y <0 si la información no está disponible
*/

/**
 * @brief Calcula el numero de dias que faltan para la lluvia de estrellas que recibe por argumento
 * 
 * @param now el fecha exacta
 * @param day el dia de la lluvia de estrellas
 * @param month el mes de la lluvia de estrellas
 * @param year el año de la lluvia de estrellas
 * @return El número de dias entre ambas fechas 
 */
static int days_between(struct tm *now, int day, int month, int year) { /* Calcula los dias que quedan para la lluvia mas cercana */
    struct tm event = {0};

    if(!now) return -1;

    event.tm_mday = day;
    event.tm_mon = month - 1;
    event.tm_year = year - 1900;
    event.tm_hour = 0;
    event.tm_isdst = -1;

    time_t t_event = mktime(&event);
    time_t t_now = mktime(now);

    if(t_event == ((time_t) - 1) || t_now == ((time_t) - 1)) return -1;
    double diff = difftime(t_event, t_now);

    return (int)(diff / DAY_IN_SEC);
}

/*
Cuadrántidas#110#03#01#2027#05
*/

/**
 * @brief Carga y lee los datos del fichero para guardarlos en el array interno de Shower
 * 
 * @param shower puntero a la estructura Shower
 * @return OK si sale bien, ERROR si algo sale mal 
 */
static Status shower_load_array(Shower *shower) { /* Carga los datos de las lluvias en el array */
    FILE *f = NULL;
    char linea[128];
    ShowerArray *s = NULL;
    char *token;

    if(!shower) return ERROR;
    
    if(!(f = fopen(SHOWER_FILE, "r"))) return ERROR;

    shower->num_showers = 0;

    while(fgets(linea, sizeof(linea), f) && shower->num_showers < MAX_SHOWERS) {
        s = &shower->showers[shower->num_showers];

        token = strtok(linea, "#");
        if(!token) continue;
        strncpy(s->name, token, MAX_CHAR - 1); /* Cuadrántidas */
        s->name[MAX_CHAR - 1] = '\0';

        token = strtok(NULL, "#");
        if(!token) continue;
        s->num_comets = atoi(token); /* 110 */

        token = strtok(NULL, "#");
        if(!token) continue;
        s->day = atoi(token); /* 03 */

        token = strtok(NULL, "#");
        if(!token) continue;
        s->month = atoi(token); /* 01 */

        token = strtok(NULL, "#");
        if(!token) continue;
        s->year = atoi(token); /* 2027 */

        token = strtok(NULL, "#");
        if(!token) continue;
        s->peak_hour = atoi(token); /* 05 */

        shower->num_showers ++;
    }

    fclose(f);
    return OK;
}

/**
 * @brief Busca la lluvia de estrellas más próxima a now
 * 
 * @param shower puntero a la estructura Shower
 * @param now la fecha exacta
 * @param moon_phase la fase lunar
 * @return OK si sale bien, ERROR si algo sale mal 
 */
static Status shower_find_next(Shower *shower, struct tm now, Phases moon_phase) { /* Encuentra la próxima lluvia y calcula sus datos */
    ShowerArray *prox = NULL; /* La lluvia mas proxima (auxiliar) */
    int prox_days = -1;
    int prox_index = -1;
    int days = -1;
    int i;

    if(!shower || shower->num_showers <= 0 || moon_phase == UNKNOWN_PHASE) return ERROR;

    for(i = 0; i < shower->num_showers; i++) {
        days = days_between(&now, shower->showers[i].day, shower->showers[i].month, shower->showers[i].year);
        if(days < 0) continue;  /* Ya pasó el evento */

        /*if(shower_is_visible(num_comets_to_intensity(shower->showers[i].num_comets), moon_phase) == FALSE) continue;*/  /* luna la fastidia demasiado (pero no es error)*/

        if(prox_index == -1 || days < prox_days) { /* Para el caso base, y para cuando guardar el dia mas proximo */
            prox_days  = days;
            prox_index = i;
        }
    }

    if(prox_index == -1) return ERROR;  /* No hay mas lluvias de estrellas en el fichero */

    prox = &shower->showers[prox_index];
    /* Se pasa la info del auxiliar al principal (el publico) */
    strncpy(shower->shower_name, prox->name, MAX_CHAR - 1);
    shower->shower_name[MAX_CHAR - 1] = '\0';
    shower->intensity = num_comets_to_intensity(prox->num_comets);
    shower->visible = shower_is_visible(shower->intensity, moon_phase);
    shower->peak_hour  = prox->peak_hour;
    shower->days_until = prox_days;

    return OK;
}

/* PÚBLICAS */
/* MEMORIA */

/* Crea una nueva instancia de lluvia de estrellas */
Shower* shower_create() {
    Shower* shower = NULL;

    shower = (Shower*) calloc (1, sizeof(Shower));
    if(!shower) return NULL;

    shower->intensity = UNKNOWN_INTENSITY;
    shower->shower_name[0] = '\0';
    shower->peak_hour = -1;
    shower->days_until = -1;
    shower->num_showers = 0;

    return shower;
}

/* Destruye una instancia de lluvia de estrellas */
void shower_destroy(Shower *shower) {
    if(!shower) return;

    free(shower);
    shower = NULL;
}

/* DATOS */

/* Carga los datos de las lluvias en el array */
Status shower_load(Shower *shower) {
    if(!shower) return ERROR;

    return shower_load_array(shower);
}

/* Actualiza la información de la próxima lluvia */
Status shower_update(Shower *shower, struct tm now, Phases moon_phase) {
    if(!shower) return ERROR;
    return shower_find_next(shower, now, moon_phase);
}

/* GETTERS */

/* Obtiene el nombre de la lluvia */
char* shower_get_name(Shower *shower) {
    if(!shower) return NULL;

    return shower->shower_name;
}

/* Obtiene la intensidad de la lluvia */
ShowerIntensity shower_get_intensity(Shower *shower) {
    if(!shower) return UNKNOWN_INTENSITY;

    return shower->intensity;
}

/* Obtiene si la lluvia es visible */
Bool shower_get_visible(Shower *shower) {
    if(!shower) return FALSE;

    return shower->visible;
}

/* Obtiene la hora del pico de la lluvia */
int shower_get_peak_hour(Shower *shower) {
    if(!shower) return -1;

    return shower->peak_hour;
}

/* Obtiene los días restantes hasta la próxima lluvia */
int shower_get_days_until(Shower *shower) {
    if(!shower) return -1;

    return shower->days_until;
}

/* Obtiene el número de lluvias cargadas */
int shower_get_num_showers(Shower *shower) {
    if(!shower) return -1;

    return shower->num_showers;
}

/* DEBUG */
#ifdef DEBUG

/* Imprime la información de la lluvia */
void shower_print(Shower *shower) {
    char intensity[MAX_CHAR];
    char name [MAX_CHAR];
    if(!shower) return;

    switch(shower->intensity) {
        case NO_SHOWER:
            strcpy(intensity, "NO_SHOWER");
            break;
        case MINOR:
            strcpy(intensity, "MINOR");
            break;
        case MODERATE:
            strcpy(intensity, "MODERATE");
            break;
        case MAJOR:
            strcpy(intensity, "MAJOR");
            break;
        case UNKNOWN_INTENSITY:
            strcpy(intensity, "UNKNOWN_INTENSITY");
            break;
        default:
            strcpy(intensity, "???");
            break;
    }

    if(shower->shower_name[0] == '\0')
        strcpy(name, "UNKNOWN");
    else 
        strcpy(name, shower->shower_name);

    printf("Shower name:      %s\n", name); 
    printf("Shower intensity: %s\n", intensity);
    printf("Shower is visible: %s\n", shower->visible ? "FALSE" : "TRUE");
    printf("Shower peak hour: %d hr\n", shower->peak_hour);
    printf("Shower days until:%d days\n", shower->days_until);
    printf("Showers loaded:   %d\n", shower->num_showers);
}
#endif