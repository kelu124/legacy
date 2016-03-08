#include "../inc/implementer.h"

/* Initialize everything */
void init() {
	/* RP Initialization */
	if (rp_Init() != RP_OK) {
		perror("Red Pitaya API init failed!");
		exit(EXIT_FAILURE);
	}

	init_control();
	init_tcp();

	stop = 0;
}

/* End everything */
void end(){
	stop = 1;

	end_control();
	end_tcp();
	rp_Release();
}

/* Main routine */
void routine(float* buffer, char* pixel_buffer){
	int i = 0;
	int j = 0;
	for(j = 0; j < BUFFER_SIZE; j++)
		buffer[j] = 0.33;

//	FILE* file = fopen("/tmp/capture_1_0.txt", "w");

	/***
	 * For each shot:
	 * Pulse
	 * Wait 66us
	 * Send a ramp
	 * Acquire the data
	 * Calculate the Pixel
	 * Send it to the TCP Server
	***/
	while(i < 10) {
		/* Waiting for the firing command */
/*		pulse(PULSE_PIN);
		usleep(66);
		ramp(RAMP_PIN);
		usleep(100);*/
/*		buffer = acquireADC(BUFFER_SIZE, buffer);
		for(j = 0; j < BUFFER_SIZE; j++)
			fprintf(file, "%f\n", buffer[j]);
		fflush(file);*/
		pixel_buffer = calcul_pixel(buffer, i, pixel_buffer);
		pthread_mutex_lock(&mutex);
		sprintf(data_to_send, "%s", pixel_buffer);
//		fprintf(file, "%s\n", pixel_buffer);
//		fflush(file);
		pthread_cond_signal(&new_data);
		pthread_mutex_unlock(&mutex);
		i++;
	}

//	fclose(file);
}
