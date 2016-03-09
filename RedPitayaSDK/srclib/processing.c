#include "../inc/processing.h"

/* Calculate the Pixel */
char* calcul_pixel(float* buffer, int buffer_size, int position, char* pixel_tab, int pixel_buffer_size) {
	int i = 0, j = 0;
	float total;

	for(i = 0; i < pixel_buffer_size; i++) {
		total = 0;
		for(j = 0; j < PIXEL_SIZE; j++) {
			total += buffer[i * PIXEL_SIZE + j];
		}
		pixel_tab[i+1] = total*255;
	}

	pixel_tab[0] = position;

	return(pixel_tab);
}
