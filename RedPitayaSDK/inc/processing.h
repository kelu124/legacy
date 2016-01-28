#ifndef PROCESSING_H
#define PROCESSING_H

#include <math.h>

#include "common.h"

float* position_array;

/* The function calculating the pixels */
char* calcul_pixel(float* buffer, char* pixel_tab);

/* Allocate memory for the position_array and fill it with right values */
void initiate_position_array(int nb_shots);

/* Desallocate memory for the position_array */
void end_position_array();

/* The function returning the position of the transducer */
float position_interpolation(int fire_id);

#endif
