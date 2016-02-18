#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	float *buffer = NULL;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((buffer = malloc(BUFFER_SIZE * sizeof(float))) == NULL)
		exit(-1);
#if(!DECIMATE8)
	if((pixel_buffer = malloc((BUFFER_SIZE/PIXEL_SIZE) * sizeof(char))) == NULL)
		exit(-1);
#elif(DECIMATE8)
	if((pixel_buffer = malloc((BUFFER_SIZE) * sizeof(char))) == NULL)
		exit(-1);
#endif
	for(i = 0; i < BUFFER_SIZE; i++)
		buffer[j] = 66.2;

	/* Convert the floats in char */
	pixel_buffer = calcul_pixel(buffer, pixel_buffer);
	/* We should have a string like "BBB...BBB */
	fprintf(stdout, "%s", pixel_buffer);

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
