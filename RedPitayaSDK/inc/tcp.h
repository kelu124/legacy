#ifndef TCP_H
#define TCP_H

#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

/* Mandatory variable which represent the trigger state */
pthread_t tcp_server_thread;
pthread_cond_t new_data;
pthread_mutex_t mutex;

void init_tcp();

void end_tcp();

int init_connection(void);

void end_connection(int sock);

void *tcp_server (void *p_data);

void send_data(char* data_to_send, SOCKET client_sock);

#endif
