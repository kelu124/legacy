#include "../inc/control.h"

int main(int argc, char* argv[]) {
	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	int buffer_size = 2048;
	int decimation = 2;
	if(argc != 1) {
		buffer_size = atoi(argv[1]);
		decimation = atoi(argv[2]);
	}
#if(RAW == ON)
	int16_t* buffer = NULL;
	buffer = malloc(buffer_size*sizeof(int16_t));
#else
	float* buffer = NULL;
	buffer = malloc(buffer_size*sizeof(float));
#endif

	/* Initialization */
	init_control(decimation);

	for(i = 0; i < 200; i++) {
		pulse(PULSE_PIN);
		buffer = acquireADC(buffer_size, buffer);
		for(j = 0; j < buffer_size; j++)
#if(RAW == ON)
			fprintf(stdout, "%d", buffer[j]);
#else
			fprintf(stdout, "%f", buffer[j]);
#endif
		fprintf(stdout, "\n");
		fflush(stdout);
		usleep(300);
	}

	/* End everything */
	end_control();

	free(buffer);

	return EXIT_SUCCESS;
}
