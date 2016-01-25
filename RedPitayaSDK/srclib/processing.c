#include "../inc/processing.h"

float* calcul_pixel(char* buffer) {
	float* pixel_buffer[BUFFER_SIZE/PIXEL_SIZE];
	int i = 0, j = 0;

	for(i = 0; i < BUFFER_SIZE / PIXEL_SIZE; i++) {
		for(j = 0; j < PIXEL_SIZE; j++) {
			pixel_buffer[i] += buffer[i*PIXEL_SIZE+j];
		}
	}

	return(*pixel_buffer);
}
