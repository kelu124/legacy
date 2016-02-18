#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0, j = 0;
	float* buffer = NULL;

	buffer = malloc(BUFFER_SIZE*sizeof(float));

	/* Initialization */
	init_control();

	for(i = 0; i < 200; i++) {
		pulse(PULSE_PIN);
		usleep(100);
	}

	for(i = 0; i < 200; i++) {
		ramp(RAMP_PIN);
		usleep(100);
	}

	for(i = 0; i < 200; i++) {
		buffer = acquireADC(BUFFER_SIZE, buffer);
		for(j = 0; j < BUFFER_SIZE; j++)
			fprintf(stdout, "%f", buffer[j]);
		fprintf(stdout, "\n");
		usleep(100);
	}

	/* End everything */
	end_control();

	free(buffer);

	return EXIT_SUCCESS;
}
