#include "../inc/tcp.h"

int main() {

	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((pixel_buffer = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);


	for(i = 0; i < PIXEL_BUFFER_SIZE; i++)
		pixel_buffer[i] = 120;

	/* Initialization */
	init_tcp();

	/* Main routine */
	for(j = 0; j < 2000; j++)
		for(i = 0; i < NB_TIRS; i++) {
			pixel_buffer[0] = i;
			pthread_mutex_lock(&mutex);
			sprintf(data_to_send, "%s", pixel_buffer);
			pthread_cond_signal(&new_data);
			pthread_mutex_unlock(&mutex);
			usleep(300);
		}

	stop = 1;

	/* End everything */
	end_tcp();

	/* RP and Variables Release */
	free(pixel_buffer);

	return EXIT_SUCCESS;
}
