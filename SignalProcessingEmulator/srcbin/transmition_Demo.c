#include "../inc/transmition.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	char* pixel_buffer = NULL;

	/* Memory Allocation */
	if((pixel_buffer = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);


	for(i = 0; i < PIXEL_BUFFER_SIZE; i++)
		pixel_buffer[i] = 65;

	/* Initialization */
	init_transmition();

	pthread_mutex_lock(&mutex_configuration);
	pthread_cond_wait(&arrived_configuration, &mutex_configuration);
	pthread_mutex_unlock(&mutex_configuration);

	/* Main routine */
	for(j = 0; j < 1; j++) {
		for(i = 0; i < NB_TIRS; i++) {
			pixel_buffer[0] = i;
			pthread_mutex_lock(&mutex);
			sprintf(data_to_send, "%s", pixel_buffer);
			pthread_cond_signal(&new_data);
			pthread_mutex_unlock(&mutex);
		}
	}
	stop = 1;

	end_transmition();

	free(pixel_buffer);

	return EXIT_SUCCESS;
}
