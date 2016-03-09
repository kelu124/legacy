#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	float *buffer = NULL;
	char *pixel_buffer = NULL;
	int decimation = 2;
	int buffer_size = 2048;
	int nb_images = 1;
	if(argc != 1) {
		nb_images = argv[1]
		buffer_size = arv[2];
		decimation = argv[3];
	}
	int pixel_buffer_size = buffer_size+1;

	/* Memory Allocation */
	if((buffer = malloc(buffer_size * sizeof(float))) == NULL)
		exit(-1);
	if((pixel_buffer = malloc(pixel_buffer_size * sizeof(char))) == NULL)
		exit(-1);

	/* Initialization */
	init(decimation, pixel_buffer_size);

	/* Main routine */
	for(i = 0; i < nb_images; i++) {
		routine(buffer, buffer_size, pixel_buffer, pixel_buffer_size);
	}

	/* End everything */
	end();

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
