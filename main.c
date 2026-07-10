#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "clock.h"
#include "moon.h"
#include "shower.h"
#include "arduino.h"

int main() {
    Moon *moon = NULL;
    Shower *shower = NULL;
    time_t now;

    moon = moon_create();
    if(!moon) return -1;

    shower = shower_create();
    if(!shower) {
        moon_destroy(moon);
        return -2;
    }



    return 0;
}