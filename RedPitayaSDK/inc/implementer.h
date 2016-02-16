#ifndef IMPLEMENTER_H
#define IMPLEMENTER_H

#include "common.h"
#include "control.h"
#include "tcp.h"
#include "processing.h"

#define NB_TIRS 128

int stop;

/* The function setting everything up, calling all the init_X functions */
void init();

/* The function setting everything down, calling all the end_X functions */
void end();

/* The main routine, sending a pulse, waiting 66us, sending a ramp, acquiring datas through ADC, then calculating the pixels and sending them to the TCP Thread */
void routine(float* buffer, char* pixel_buffer);

#endif
