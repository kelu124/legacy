#include "../inc/processing.h"

/* Calculate the Pixel */
char* calcul_pixel(float* buffer, char* pixel_tab) {
	int i = 0;

#if(!DECIMATE8)
	int j = 0;
	float total;

	for(i = 0; i < PIXEL_BUFFER_SIZE; i++) {
		total = 0;
		for(j = 0; j < PIXEL_SIZE; j++) {
			total += buffer[i * PIXEL_SIZE + j];
		}
		pixel_tab[i] = total*255;
	}
#elif(DECIMATE8)
	for(i = 0; i < PIXEL_BUFFER_SIZE; i++) {
		pixel_tab[i] = buffer[i]*255;
	}
#endif

	return(pixel_tab);
}
