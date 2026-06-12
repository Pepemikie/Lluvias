#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "shower.h"

struct _Shower {
    ShowerIntensity intensity;
    char shower_name[MAX_CHAR];
    int peak_hour;
};

Shower* shower_create() {
    Shower* shower = NULL;

    shower = (Shower*) calloc (1, sizeof(Shower));
    if(!shower) return NULL;

    shower->intensity = UNKNOWN_INTENSITY;
    shower->peak_hour = -1;
    shower->shower_name[0] = '\0';

    return shower;
}

void shower_destroy(Shower *shower) {
    if(!shower) return;

    free(shower);
    shower = NULL;
}

ShowerIntensity shower_get_intensity(Shower *shower) {
    if(!shower) return UNKNOWN_INTENSITY;

    return shower->intensity;
}

char* shower_get_name(Shower *shower) {
    if(!shower) return NULL;

    return shower->shower_name;
}

int shower_get_peak_hour(Shower *shower) {
    if(!shower) return -1;

    return shower->peak_hour;
}

#ifdef DEBUG
void shower_print(Shower *shower) {
    char intensity[MAX_CHAR];
    char name[MAX_CHAR];

    if(shower->intensity == UNKNOWN_INTENSITY) strcpy(intensity, "UNKNOWN_INTENSITY");
    if(shower->intensity == NO_SHOWER) strcpy(intensity, "NO_SHOWER");
    if(shower->intensity == MINOR) strcpy(intensity, "MINOR");
    if(shower->intensity == MODERATE) strcpy(intensity, "MODERATE");
    if(shower->intensity == MAJOR) strcpy(intensity, "MAJOR");

    if(shower->shower_name[0] == '\0') strcpy(name, "UNKNOWN_SHOWER");
    else strcpy(name, shower->shower_name);

    printf("Shower intensity: %s\n", intensity);
    printf("Shower name: %s\n", name);
    printf("Shower peak hour: %d hr\n", shower->peak_hour);
}
#endif