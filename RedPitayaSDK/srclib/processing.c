#include "../inc/processing.h"

/* Calculate the Pixel */
char* calcul_pixel(float* buffer, int position, char* pixel_tab) {
	int i = 0;

#if(!DECIMATE8)
	int j = 0;
	float total;
	int nmb_pixels = BUFFER_SIZE/PIXEL_SIZE;

	pixel_tab[0] = position;

	for(i = 0; i < nmb_pixels; i++) {
		total = 0;
		for(j = 0; j < PIXEL_SIZE; j++) {
			total += buffer[i * PIXEL_SIZE + j];
		}
		pixel_tab[i+1] = total*255;
	}
#elif(DECIMATE8)
	for(i = 0; i < BUFFER_SIZE; i++) {
		pixel_tab[i+1] = buffer[i]*255;
	}
#endif

	return(pixel_tab);
}
