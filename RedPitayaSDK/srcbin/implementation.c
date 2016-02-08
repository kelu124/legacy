#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
//	int i = 0;
	float *buffer = NULL;
	char *pixel_buffer = NULL;

	/* Memory Allocation */
	if((buffer = malloc(BUFFER_SIZE * sizeof(float))) == NULL)
		exit(-1);
#if(!DECIMATE8)
	if((pixel_buffer = malloc((BUFFER_SIZE/PIXEL_SIZE + 1) * sizeof(char))) == NULL)
		exit(-1);
#elif(DECIMATE8)
	if((pixel_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))) == NULL)
		exit(-1);
#endif

	/* Initialization */
	init();

	/* Main routine */
	//for(i = 0; i < 2000; i++) {
	while(1){
		routine(buffer, pixel_buffer);
	}

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	/* End everything */
	end();

	return EXIT_SUCCESS;
}
