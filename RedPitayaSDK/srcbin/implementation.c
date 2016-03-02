#include "../inc/implementer.h"

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

	/* Initialization */
	init();

	/* Main routine */
	for(i = 0; i < 1; i++) {
	//while(1){
		routine(buffer, pixel_buffer);
	}

	/* End everything */
	end();

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	return EXIT_SUCCESS;
}
