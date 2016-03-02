#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/*** Base Definitions ***/
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

/*** Pre-compiling Options ***/
#define DECIMATE8 ON
#define EXTERNAL_TRIGGER ON

/*** Global Variables impacted by the options ***/
#if(!DECIMATE8)
#define BUFFER_SIZE 2048
//#define BUFFER_SIZE 16384
#define PIXEL_SIZE 4
#elif(DECIMATE8)
#define BUFFER_SIZE 16384
//#define BUFFER_SIZE 2048
#define PIXEL_SIZE 1
#endif

/*** Final Global Variables ***/
#define PIXEL_BUFFER_SIZE (BUFFER_SIZE/PIXEL_SIZE)+1
#define NB_TIRS 128

#endif
