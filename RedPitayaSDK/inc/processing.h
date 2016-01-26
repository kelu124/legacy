#ifndef PROCESSING_H
#define PROCESSING_H

#include <math.h>

#include "common.h"

int* calcul_pixel(float* buffer, int* pixel_tab);

float position_interpolation(int fire_id, int nb_fire);

#endif
