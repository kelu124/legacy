#include "../inc/processing.h"

/* Calculate the Pixel */
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

/* Initiate and fill the position_array */
void initiate_position_array(int nb_shots){
	int i = 0;

	position_array = malloc(nb_shots*sizeof(float));
	for(i = 0; i < nb_shots; i++)
		position_array[i] = (float)asin((float)(2*i-nb_shots)/nb_shots);
}

/* Free the position_array */
void end_position_array(){
	free(position_array);
}

/* Return the position correlated to the shot_id */
float position_interpolation(int fire_id) {
	return(position_array[fire_id]);
}
