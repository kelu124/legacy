#include "../inc/processing.h"

/* Calculate the Pixel */
char* calcul_pixel(float* buffer, int position, char* pixel_tab) {
	int i = 0;

#if(!DECIMATE8)
	int j = 0;
	float total;

	for(i = 0; i < PIXEL_BUFFER_SIZE; i++) {
		total = 0;
		for(j = 0; j < PIXEL_SIZE; j++) {
			total += buffer[i * PIXEL_SIZE + j];
		}
		pixel_tab[i+1] = total*255;
	}
#elif(DECIMATE8)
	for(i = 0; i < PIXEL_BUFFER_SIZE; i++) {
		pixel_tab[i+1] = buffer[i]*255;
	}
#endif

	pixel_tab[0] = position;

	return(pixel_tab);
}
