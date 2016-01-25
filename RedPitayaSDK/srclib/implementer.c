#include "../inc/implementer.h"

/* Initialize everything */
void init() {
	/* RP Initialization */
	if (rp_Init() != RP_OK) {
		perror("Red Pitaya API init failed!");
		exit(EXIT_FAILURE);
	}

	init_control();
	init_udp();

	stop = 0;
}

/* End everything */
void end(){
	stop = 1;
	end_control();
	end_udp();
}
