#ifndef PROCESSING_H
#define PROCESSING_H

#include <math.h>

#include "common.h"

pthread_t processor_thread;
pthread_cond_t new_data_to_process;
pthread_mutex_t process_mutex;

typedef struct data_to_process_ {
	float* buffer;
	int buffer_size;
	int position;
	char* pixel_tab;
	int pixel_buffer_size;
}data_to_process;

data_to_process data;
int process_stop;

/* The function calculating the pixels */
char* calcul_pixel(float* buffer, int buffer_size, int position, char* pixel_tab, int pixel_buffer_size);

/* The function setting processing up */
void init_processing();

/* The function setting processing down */
void end_processing();

/* The Thread controlling the Processing system */
void *process_server (void *p_data);

#endif
