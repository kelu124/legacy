#include "../inc/control.h"

int main(int argc, char* argv[]) {
	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	float* buffer = NULL;
	int buffer_size = 2048;
	int decimation = 2;
	if(argc != 1) {
		buffer_size = atoi(argv[1]);
		decimation = atoi(argv[2]);
	}

	buffer = malloc(buffer_size*sizeof(float));

	/* Initialization */
	init_control(decimation);

	for(i = 0; i < 200; i++) {
		pulse(PULSE_PIN);
		buffer = acquireADC(buffer_size, buffer);
		for(j = 0; j < buffer_size; j++)
			fprintf(stdout, "%f", buffer[j]);
		fprintf(stdout, "\n");
		fflush(stdout);
		usleep(300);
	}

	/* End everything */
	end_control();

	free(buffer);

	return EXIT_SUCCESS;
}
