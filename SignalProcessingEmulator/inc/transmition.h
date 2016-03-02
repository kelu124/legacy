#ifndef TRANSMITION_H
#define TRANSMITION_H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "common.h"

pthread_t transmition_thread;
pthread_cond_t new_data;
pthread_mutex_t mutex;
char *data_to_send;

void init_transmition();

void end_transmition();

void init_fifos(int* fifo_configuration_fd, int* fifo_datasender_fd);

void end_fifos(int fifo_configuration_fd, int fifo_datasender_fd);

void *transmition(void *p_data);

#endif
