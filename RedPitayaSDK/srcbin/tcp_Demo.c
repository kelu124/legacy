#include "../inc/tcp.h"

int main() {

	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	char *pixel_buffer = NULL;
	int pixel_buffer_size = 2049;

	/* Memory Allocation */
	if((pixel_buffer = malloc(pixel_buffer_size * sizeof(char))) == NULL)
		exit(-1);


	for(i = 0; i < pixel_buffer_size; i++)
		pixel_buffer[i] = 120;

	/* Initialization */
	init_tcp(pixel_buffer_size);

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

	/* End everything */
	end_tcp();

	/* RP and Variables Release */
	free(pixel_buffer);

	return EXIT_SUCCESS;
}
