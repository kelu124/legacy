#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

#define DECIMATE8 ON

#if(!DECIMATE8)
#define BUFFER_SIZE 16384
#define PIXEL_SIZE 32
#elif(DECIMATE8)
#define BUFFER_SIZE 2048
#endif

#define NB_TIRS 128
#define IPHOST "192.168.1.36"
#define PORT 7538   //The port on which to listen for incoming data
#define MAX_CLIENTS 1

#endif
