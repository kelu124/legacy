#include "../inc/udp.h"

static int init_connection(void) {
	/* UDP so SOCK_DGRAM */
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN sin = { 0 };

	if(sock == INVALID_SOCKET) {
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = inet_addr(IPHOST);
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;

	if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR) {
		perror("bind()");
		exit(errno);
	}

	return sock;
}

static void end_connection(int sock) {
	closesocket(sock);
}

static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actual) {
	int i = 0;
	for(i = 0; i < actual; i++)
		if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr && clients[i].sin.sin_port == csin->sin_port)
			return 1;

	return 0;
}

static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actual) {
	int i = 0;

	for(i = 0; i < actual; i++)
		if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr && clients[i].sin.sin_port == csin->sin_port)
			return &clients[i];

	return NULL;
}

static void read_client(SOCKET sock, SOCKADDR_IN *sin) {
   size_t sinsize = sizeof *sin;

   if(recvfrom(sock, NULL, 0, 0, (SOCKADDR *) sin, &sinsize) < 0) {
      perror("recvfrom()");
      exit(errno);
   }
}

static void write_client(SOCKET sock, SOCKADDR_IN *sin, const char *data_to_send) {
	if(sendto(sock, data_to_send, strlen(data_to_send), 0, (SOCKADDR *) sin, sizeof *sin) < 0) {
		perror("send()");
		exit(errno);
	}
}

static void send_message_to_all_clients(int sock, Client *clients, int actual, const char *data_to_send) {
	int i = 0;
	char message[BUFFER_SIZE];
	message[0] = 0;
	for(i = 0; i < actual; i++) {
			sprintf(message, "%s", data_to_send);
			write_client(sock, &clients[i].sin, message);
	}
}

static void *udp_server (void *p_data) {
	/* Render this Thread autonomous */
	pthread_detach(pthread_self());

	SOCKET sock = init_connection();
	/* the index for the array */
	int actual = 0;
	int max = sock;
	/* an array for all clients */
	Client clients[MAX_CLIENTS];
	Client *client;

	fd_set rdfs;

	while(!stop) {
		FD_ZERO(&rdfs);

		/* add STDOUT_FILENO */
		FD_SET(STDOUT_FILENO, &rdfs);

		/* add the connection socket */
		FD_SET(sock, &rdfs);

		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1) {
			perror("select()");
			exit(errno);
		}

		if(FD_ISSET(sock, &rdfs)) {
			/* new client */
			SOCKADDR_IN csin = { 0 };

			/* a client is talking */
			read_client(sock, &csin);

			if(check_if_client_exists(clients, &csin, actual) == 0) {
				if(actual != MAX_CLIENTS) {
					Client c = { csin };
					clients[actual] = c;
					actual++;
				}
			} else {
				client = get_client(clients, &csin, actual);
				if(client == NULL)
					continue;
			}
			pthread_mutex_lock(&mutex);
			/* Waiting for a new data to arrive */
			pthread_cond_wait(&new_data,&mutex);
			send_message_to_all_clients(sock, clients, actual, data_to_send);
			fprintf(stdout, "Data sent!\n");
			pthread_mutex_unlock(&mutex);
		}
	}

	end_connection(sock);

	pthread_exit(NULL);
}

/* Initialize everything (The RP and all the configurations) */
void init_udp(){
	pthread_cond_init(&new_data,NULL);
	pthread_mutex_init(&mutex,NULL);

	/* Launch the UDP protocol */
	pthread_create(&udp_server_thread, NULL, udp_server, NULL);
}

/* End everything (Stop Acquisition, motor and RP resources) */
void end_udp() {
	pthread_cond_destroy(&new_data);
    	pthread_mutex_destroy(&mutex);
}
