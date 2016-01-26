#include "../inc/processing.h"

int* calcul_pixel(float* buffer, int* pixel_tab) {
	int i = 0, j = 0;
	float pixel_buffer[BUFFER_SIZE / PIXEL_SIZE] = {0};

	for(i = 0; i < BUFFER_SIZE / PIXEL_SIZE; i++) {
		for(j = 0; j < PIXEL_SIZE; j++) {
			pixel_buffer[i] += buffer[i*PIXEL_SIZE+j];
		}
		pixel_tab[i] = (int)pixel_buffer[i];
	}

	return(pixel_tab);
}

float position_interpolation(int fire_id, int nb_fire) {
	return((float)asin((2*(fire_id-1)-nb_fire)/nb_fire));
}
