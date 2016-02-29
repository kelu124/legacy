#include "../inc/transmition.h"

/* Initialize everything (The RP and all the configurations) */
void init_transmition(){
	pthread_cond_init(&new_data,NULL);
	pthread_mutex_init(&mutex,NULL);

	if((data_to_send = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);

	/* Launch the transmission protocol */
	pthread_create(&transmition_thread, NULL, transmition, NULL);
}

/* End the transmition */
void end_transmition() {
	pthread_join(transmition_thread, NULL);
	pthread_cond_destroy(&new_data);
    	pthread_mutex_destroy(&mutex);
	free(data_to_send);
}

void *transmition(void *p_data) {
	char* filename = "/tmp/Capture.txt";
	FILE* file = NULL;

	file = fopen(filename, "w");
	if(file == NULL) {
		fprintf(stderr, "Error opening %s\n", filename);
		exit(-1);
	}

	while(!stop) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&new_data, &mutex);
		fprintf(file, "%s\n", data_to_send);
		pthread_mutex_unlock(&mutex);
	}

	fclose(file);

	pthread_exit(NULL);
}
