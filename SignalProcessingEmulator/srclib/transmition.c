#include "../inc/transmition.h"

/* Initialize everything (The RP and all the configurations) */
void init_transmition(){
	pthread_cond_init(&new_data,NULL);
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&arrived_configuration,NULL);
	pthread_mutex_init(&mutex_configuration,NULL);

	if((data_to_send = malloc(PIXEL_BUFFER_SIZE * sizeof(char))) == NULL)
		exit(-1);

	/* Launch the transmission protocol */
	pthread_create(&transmition_thread, NULL, transmition, NULL);
}

/* Init the fifos */
void init_fifos(int* fifo_configuration_fd, int* fifo_datasender_fd) {
	if (mkfifo("/tmp/FIFOSENDER", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP) != 0) {
		if (errno != EEXIST) {
			perror("Creating the fifo FIFOSENDER. Error");
			exit(1);
		}
	}
	if (mkfifo("/tmp/FIFOCONFIGURATION", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP) != 0) {
		if (errno != EEXIST) {
			perror("Creating the fifo FIFOCONFIGURATION. Error");
			exit(1);
		}
	}

	// Open the fifo for writing
	if ((*fifo_datasender_fd = open("/tmp/FIFOSENDER", O_WRONLY)) < 0) {
		perror("Opening the fifo for writing. Error");
		exit(2);
	}

	// Open the fifo configuration for reading
	if ((*fifo_configuration_fd = open("/tmp/FIFOCONFIGURATION", O_RDONLY)) < 0) {
		perror("Opening the fifo for reading. Error");
		exit(2);
	}
}

/* Close the fifos */
void end_fifos(int fifo_configuration_fd, int fifo_datasender_fd) {
	close(fifo_configuration_fd);
	close(fifo_datasender_fd);
}

/* End the transmition */
void end_transmition() {
	pthread_join(transmition_thread, NULL);
	pthread_cond_destroy(&new_data);
    	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&arrived_configuration);
    	pthread_mutex_destroy(&mutex_configuration);
	free(data_to_send);
}

void *transmition(void *p_data) {
	int fifo_configuration_fd = 0, fifo_datasender_fd = 0;
	char buffer = '0';
	int bufferRead[5] = {0};

	init_fifos(&fifo_configuration_fd, &fifo_datasender_fd);
	fprintf(stdout, "%d and %d\n", fifo_configuration_fd, fifo_datasender_fd);
	fflush(stdout);

	pthread_mutex_lock(&mutex_configuration);
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			bufferRead[i] *= 10;
			if(!read(fifo_configuration_fd, &buffer, sizeof(char))) {
				fprintf(stdout, "Couldn't read\n");
				fflush(stdout);
			}
			bufferRead[i] += buffer-48;
		}
	}
	fprintf(stdout, "%d %d %d %d %d\n", bufferRead[0], bufferRead[1], bufferRead[2], bufferRead[3], bufferRead[4]);
	pthread_cond_signal(&arrived_configuration);
	pthread_mutex_unlock(&mutex_configuration);

	while(!stop) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&new_data, &mutex);
		if(!write(fifo_datasender_fd, data_to_send, strlen(data_to_send))) {
			fprintf(stdout, "FIFO closed\n");
			fflush(stdout);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}

	end_fifos(fifo_configuration_fd, fifo_datasender_fd);
	fprintf(stdout, "Everything was closed\n");
	fflush(stdout);

	pthread_exit(NULL);
}
