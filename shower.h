/**
 * @file shower.h
 * @author José Miguel Romero Oubiña
 * @brief Cabecera del modulo shower.c
 * @version 0.1
 * @date 2026-07-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef SHOWER_H
#define SHOWER_H

#include <stdio.h>
#include <time.h>

#include "types.h"

/** @brief Estructura para representar una lluvia de estrellas */
typedef struct _Shower Shower;

/**
 * @brief Crea una nueva instancia de lluvia de estrellas
 * 
 * @return Puntero a la estructura Shower
 */
Shower* shower_create();

/**
 * @brief Destruye una instancia de lluvia de estrellas
 * 
 * @param shower puntero a la estructura Shower
 */
void shower_destroy(Shower *shower);

/**
 * @brief Carga los datos de las lluvias en el array
 * 
 * @param shower puntero a la estructura Shower
 * @return OK si sale bien, ERROR si algo sale mal 
 */
Status shower_load(Shower *shower);

/**
 * @brief Actualiza la información de la próxima lluvia
 * 
 * @param shower puntero a la estructura Shower 
 * @param now estructura tm, de la libreria time
 * @param moon_phase fase lunar
 * @return OK si sale bien, ERROR si algo sale mal 
 */
Status shower_update(Shower *shower, struct tm now, Phases moon_phase);

/**
 * @brief Obtiene el nombre de la lluvia
 * 
 * @param shower puntero a la estructura Shower 
 * @return El nombre de la lluvia
 */
char* shower_get_name(Shower *shower);

/**
 * @brief Obtiene la intensidad de la lluvia
 * 
 * @param shower puntero a la estructura Shower 
 * @return La intensidad de la lluvia
 */
ShowerIntensity shower_get_intensity(Shower *shower);

/**
 * @brief Obtiene si la lluvia es visible
 * 
 * @param shower puntero a la estructura Shower 
 * @return FALSE si no es visible, TRUE si es visible 
 */
Bool shower_get_visible(Shower *shower);

/**
 * @brief Obtiene la hora del pico de la lluvia
 * 
 * @param shower puntero a la estructura Shower 
 * @return La hora pico de la lluvia 
 */
int shower_get_peak_hour(Shower *shower);

/**
 * @brief Obtiene los días restantes hasta la próxima lluvia
 * 
 * @param shower puntero a la estructura Shower 
 * @return Los días restantes hasta la próxima lluvia 
 */
int shower_get_days_until(Shower *shower);

/**
 * @brief Obtiene el número de lluvias cargadas
 * 
 * @param shower puntero a la estructura Shower 
 * @return El número de lluvias cargadas 
 */
int shower_get_num_showers(Shower *shower);

#ifdef DEBUG
/** @brief Imprime la información de la lluvia
 * 
 * @param shower puntero a la estructura Shower 
 */
void shower_print(Shower *shower);
#endif
#endif /* SHOWER_H */