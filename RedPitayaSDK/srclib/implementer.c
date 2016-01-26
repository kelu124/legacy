#include "../inc/implementer.h"

/* Initialize everything */
void init() {
	/* RP Initialization */
	if (rp_Init() != RP_OK) {
		perror("Red Pitaya API init failed!");
		exit(EXIT_FAILURE);
	}

	init_control();
	init_udp();

	stop = 0;
}

/* End everything */
void end(){
	stop = 1;
	end_control();
	end_udp();
}

void routine(float* buffer, int* pixel_buffer){
	int i = 1;
	float position = 0;

	while(i < NB_TIRS) {
		pulse();
		usleep(66);
		ramp();
		usleep(100);
		//buffer = acquireADC(BUFFER_SIZE, buffer);
		pixel_buffer = calcul_pixel(buffer, pixel_buffer);
		position = position_interpolation(i, NB_TIRS);
		pthread_mutex_lock(&mutex);
		/* Waiting for a new data to arrive */
		sprintf(data_to_send, "%f%s", position, (char*)pixel_buffer);
		pthread_cond_signal(&new_data);
		pthread_mutex_unlock(&mutex);
		i++;
	}
}
