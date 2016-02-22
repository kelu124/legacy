#include "../inc/processing.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	float *buffer = NULL;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((buffer = malloc(BUFFER_SIZE * sizeof(float))) == NULL)
		exit(-1);
	if((pixel_buffer = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);
	for(i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = 0.26;

	/* Convert the floats in char */
	pixel_buffer = calcul_pixel(buffer, 65, pixel_buffer);
	/* We should have a string like "ABBB...BBB */
	fprintf(stdout, "%s\n", pixel_buffer);

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
