#ifndef UDP_H
#define UDP_H

#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> /* gethostbyname */

#include "common.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct {
	SOCKADDR_IN sin;
}Client;

/* Mandatory variable which represent the trigger state */
pthread_t udp_server_thread;
pthread_cond_t new_data;
pthread_mutex_t mutex;
char data_to_send[BUFFER_SIZE];

static int init_connection(void);

static void end_connection(int sock);

static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actual);

static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actual);

static void read_client(SOCKET sock, SOCKADDR_IN *sin);

static void write_client(SOCKET sock, SOCKADDR_IN *sin, const char *data_to_send);

static void send_message_to_all_clients(int sock, Client *clients, int actual, const char *data_to_send);

static void *udp_server (void *p_data);

void init_udp();

void end_udp();

#endif
