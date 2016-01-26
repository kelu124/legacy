#ifndef IMPLEMENTER_H
#define IMPLEMENTER_H

#include "common.h"
#include "control.h"
#include "udp.h"
#include "processing.h"

int stop;

void init();

void end();

void routine(float* buffer, int* pixel_buffer);

#endif
