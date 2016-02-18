#include "../inc/processing.h"

/* Calculate the Pixel */
char* calcul_pixel(float* buffer, char* pixel_tab) {
	int i = 0;

#if(!DECIMATE8)
	int j = 0;
	float total;
	int nmb_pixels = BUFFER_SIZE/PIXEL_SIZE;

	for(i = 0; i < nmb_pixels; i++) {
		total = 0;
		for(j = 0; j < PIXEL_SIZE; j++) {
			total += buffer[i * PIXEL_SIZE + j];
		}
		pixel_tab[i] = total;
	}
#elif(DECIMATE8)
	for(i = 0; i < BUFFER_SIZE; i++) {
		pixel_tab[i] = buffer[i];
	}
#endif

	return(pixel_tab);
}
