#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
//	int i = 0;
	int decimation = 2;
	float *buffer = NULL;
	int buffer_size = 2048;
	int pixel_buffer_size = buffer_size+1;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((buffer = malloc(buffer_size * sizeof(float))) == NULL)
		exit(-1);
	if((pixel_buffer = malloc(pixel_buffer_size * sizeof(char))) == NULL)
		exit(-1);

	/* Initialization */
	init(decimation, pixel_buffer_size);

	/* Main routine */
//	for(i = 0; i < 1; i++) {
	//while(1){
		routine(buffer, buffer_size, pixel_buffer, pixel_buffer_size);
//	}

	/* End everything */
	end();

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
