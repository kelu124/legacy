#include "../inc/processing.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	int buffer_size = 2048;
	int pixel_buffer_size = buffer_size+1;
	float *buffer = NULL;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((buffer = malloc(buffer_size * sizeof(float))) == NULL)
		exit(-1);
	if((pixel_buffer = malloc(pixel_buffer_size * sizeof(char))) == NULL)
		exit(-1);
	for(i = 0; i < buffer_size; i++)
		buffer[i] = 0.26;

	/* Convert the floats in char */
	pixel_buffer = calcul_pixel(buffer, buffer_size, 65, pixel_buffer, pixel_buffer_size);
	/* We should have a string like "ABBB...BBB */
	fprintf(stdout, "%s\n", pixel_buffer);

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
