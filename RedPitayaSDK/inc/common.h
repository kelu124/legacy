#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "rp.h"
#include "configuration.h"

#define BUFFER_SIZE 16384
#define NB_TIRS 128
#define PIXEL_SIZE 32
#define IPHOST "192.168.1.36"
#define PORT 7538   //The port on which to listen for incoming data
#define MAX_CLIENTS 1

extern int stop;
char *data_to_send;

#endif
