#include "../inc/tcp.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((pixel_buffer = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);
	for(i = 0; i < PIXEL_BUFFER_SIZE; i++)
		pixel_buffer[i] = 66;

	/* Initialization */
	init_tcp();

	/* Main routine */
	for(i = 0; i < 2000; i++) {
		pthread_mutex_lock(&mutex);
		sprintf(data_to_send, "%d %s", i, pixel_buffer);
		pthread_cond_signal(&new_data);
		pthread_mutex_unlock(&mutex);
	}

	/* RP and Variables Release */
	free(pixel_buffer);

	/* End everything */
	end_tcp();

	return EXIT_SUCCESS;
}
