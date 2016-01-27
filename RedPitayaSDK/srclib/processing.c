#include "../inc/processing.h"

char* calcul_pixel(float* buffer, char* pixel_tab) {

#if(!DECIMATE8)
	int i = 0, j = 0;
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
	int i = 0;

	for(i = 0; i < BUFFER_SIZE; i++) {
		pixel_tab[i] = buffer[i];
	}
#endif

	return(pixel_tab);
}

float position_interpolation(int fire_id, int nb_fire) {
	return((float)asin((float)(2*(fire_id-1)-nb_fire)/nb_fire));
}
