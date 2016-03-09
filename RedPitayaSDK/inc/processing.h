#ifndef PROCESSING_H
#define PROCESSING_H

#include <math.h>

#include "common.h"

/* The function calculating the pixels */
char* calcul_pixel(float* buffer, int buffer_size, int position, char* pixel_tab, int pixel_buffer_size);

#endif
