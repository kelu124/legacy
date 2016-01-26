#include "../inc/implementer.h"

int main() {
	/* Variable Declaration and Initialization */
	int i = 0;
	float *buffer = NULL;
	int *pixel_buffer = NULL;

	/* Memory Allocation */
	buffer = malloc(BUFFER_SIZE * sizeof(float));
	pixel_buffer = malloc(BUFFER_SIZE/PIXEL_SIZE * sizeof(int));

	/* Initialization */
	init();

	/* Main routine:
	 * Pulse
	 * Wait 66us
	 * Generate one ramp
	 * Do an acquisition (wait 100 us for simulation without acquisition)
	 */
	for(i = 0; i < 20; i++) {
		routine(buffer, pixel_buffer);
	}

	/* RP and Variables Release */
	free(pixel_buffer);
	free(buffer);

	/* End everything */
	end();

	return EXIT_SUCCESS;
}
