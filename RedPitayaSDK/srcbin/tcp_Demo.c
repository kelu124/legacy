#include "../inc/tcp.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
#if(!DECIMATE8)
	if((pixel_buffer = malloc((BUFFER_SIZE/PIXEL_SIZE) * sizeof(char))) == NULL)
		exit(-1);
	for (i = 0; i < BUFFER_SIZE/PIXEL_SIZE; i++) {
		pixel_buffer[i] = 66;
	}
#elif(DECIMATE8)
	if((pixel_buffer = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);
	for(i = 0; i < BUFFER_SIZE; i++)
		pixel_buffer[i] = 66;
#endif

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
