#include "../inc/implementer.h"

/* Initialize everything */
void init() {
	/* RP Initialization */
	if (rp_Init() != RP_OK) {
		perror("Red Pitaya API init failed!");
		exit(EXIT_FAILURE);
	}

	init_control();
	//init_udp();

	stop = 0;
}

/* End everything */
void end(){
	stop = 1;
	end_control();
	//end_udp();
}

void routine(float* buffer, char* pixel_buffer){
	int i = 1, j = 0;
	struct timeval init_time, end_time;
	float position = 0;
	for(j = 0; j < BUFFER_SIZE; j++)
		buffer[j] = 2.34;

	while(i < NB_TIRS+1) {
		gettimeofday(&init_time,NULL);
		pulse();
		usleep(66);
		ramp();
		usleep(100);
		//buffer = acquireADC(BUFFER_SIZE, buffer);
		//pixel_buffer = calcul_pixel(buffer, pixel_buffer);
		position = position_interpolation(i, NB_TIRS);
		//pthread_mutex_lock(&mutex);
		sprintf(data_to_send, "%f %s", position, pixel_buffer);
		//pthread_cond_signal(&new_data);
		//pthread_mutex_unlock(&mutex);
		i++;
		gettimeofday(&end_time,NULL);
		printf("%d\n", (int)end_time.tv_usec-init_time.tv_usec);
	}
}
