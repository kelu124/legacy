#ifndef TRANSMITION_H
#define TRANSMITION_H

#include "common.h"

pthread_t transmition_thread;
pthread_cond_t new_data;
pthread_mutex_t mutex;
char *data_to_send;

void init_transmition();

void end_transmition();

void *transmition(void *p_data);

#endif
