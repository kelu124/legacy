#include "../inc/processing.h"

int main(int argc, char* argv[]) {
	/* Variable Declaration and Initialization */
	int i = 0;
	int buffer_size = 2048;
	if(argc != 1) {
		buffer_size = atoi(argv[1]);
	}
	int pixel_buffer_size = buffer_size+1;

	data.buffer_size = buffer_size;
	data.pixel_buffer_size = pixel_buffer_size;

	/* Memory Allocation */
	if((data.buffer = malloc(buffer_size * sizeof(float))) == NULL)
		exit(-1);
	if((data.pixel_tab = malloc(pixel_buffer_size * sizeof(char))) == NULL)
		exit(-1);

	init_processing();
	usleep(100);

	for(int j = 0; j < 10; j++) {
		pthread_mutex_lock(&process_mutex);
		for(i = 0; i < buffer_size; i++)
			data.buffer[i] = 0.26;
		data.position = 65;
		pthread_cond_signal(&new_data_to_process);
		pthread_mutex_unlock(&process_mutex);
		/* Temps de Capture (100us parcequ'on gère!) */
		usleep(100);
	}

	end_processing();

	/* RP and Variables Release */
	free(data.pixel_tab);
	free(data.buffer);

	return EXIT_SUCCESS;
}
