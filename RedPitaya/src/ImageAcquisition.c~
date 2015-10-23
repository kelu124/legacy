#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>

#include "rp.h"

#define PORT 7538   //The port on which to listen for incoming data
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define IPhost "192.168.1.28"  //IP of the computeur for udp

float SMAX = 0.00255;
float SMIN = -0.00255;
int Scalling_Factor=100000; //Must have SMax*Scalling_Factor=255

int tbuff, i,j  = 0;
int CheckUDP = 0;


void die(char *s)
{
    perror(s);
    exit(1);
}


// Pitaya code in itself
int main(int argc, char **argv){

	/*Acquisition parameters*/
	uint32_t buff_size = 16384; //size of the buffer for echo acquisition
	int average=16;		    //number of signal to average at each line
	uint32_t buffPWM_size = 12000;//size of the buffer for PWM acquisition
	int PWM_Position = 0;
	float PWMTriggerLevel = 0.05;
	int oldPWM=0;


	/*Initialise udp buffer*/
	float ttmp = 0;
	float MoyenneFichier = 0;
	int sampling = 16;
	int samples = 256;
	int PointsNb = buff_size/sampling;
	int MaxPointsPerPacket = 256; // (in bytes)
	int NbPackets = PointsNb/MaxPointsPerPacket;	
	int TaillerBuffer = samples+2;
	int UDPBuffer[TaillerBuffer];

	//FILE * fs;
	//fs = fopen ("signal.txt","w+");

	printf("DEBUG COMMENCE\n");
	/* Initialize UDP */
	struct sockaddr_in si_me, si_other;
	int s;
	int slen = sizeof(si_other);
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
	die("socket");
	}

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_other.sin_family = AF_INET;
	si_me.sin_port = htons(PORT); // Port
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.s_addr = inet_addr(IPhost); //specific binding to listenser
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1){die("bind");}
	/* End of UDP initialization */


	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
	}


		
	while (1){
	//for (int k=0 ; k<500 ; k++){

		float *buff = (float *)malloc(buff_size * sizeof(float));
		int *ibuff = (int *)malloc(buff_size * sizeof(int));

		/*initialise to 0 the buffer*/
		for (i=0 ; i<buff_size ; i++){buff[i]=0.0;}

		/*define PWM buffer*/		
		float *buffW = (float *)malloc(buffPWM_size * sizeof(float));

		/*set decimation*/
		rp_AcqSetDecimation(RP_DEC_64);	
		/*initiate trigger state*/
		rp_acq_trig_state_t stateW = RP_TRIG_STATE_TRIGGERED;
		/*start acquisition must be set before trigger initiation*/
		rp_AcqStart();
	
		/*trigger source -- Channel B, Negatif*/ 
		rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHB_PE);
		rp_AcqSetTriggerLevel(PWMTriggerLevel);
		/*waiting for trigger*/
		while(1){
			rp_AcqGetTriggerState(&stateW);
			if(stateW == RP_TRIG_STATE_TRIGGERED){
				break;
			}
		}		
		/*putt acquisition data in the temporary buffer*/
		rp_AcqGetOldestDataV(RP_CH_2, &buffPWM_size, buffW);
		PWM_Position=0;
		for (i=0 ; i<buffPWM_size ; i++) {
			if (buffW[i] > PWMTriggerLevel ){PWM_Position++;}
		}
		PWM_Position = PWM_Position -2000; //lowering the base, staying over max though
		PWM_Position = (int)(PWM_Position/20)-23;
		if (PWM_Position>60){PWM_Position=oldPWM;} //their is strange bug, sometimes PWM_Position>>60
		//printf("oldPWM : %i\n",oldPWM);
		printf("PWM : %i\n",PWM_Position);


		if (PWM_Position!=oldPWM){

			//printf("in\n");
			//fprintf(fs,"\n%i",PWM_Position);

			rp_AcqReset();

			/* decimation n (=1,8,64...) : frequency = 125/n MHz*/
			rp_AcqSetDecimation(RP_DEC_1);
			rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;
			for (i=0 ; i<average ; i++) {

				/*start acquisition must be set before trigger initiation*/
				rp_AcqStart();

				/*allocation of temporary buffer size in memory*/
				float *temp = (float *)malloc(buff_size * sizeof(float));

				/*trigger source -- Channel A, Negatif*/ 
				rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_NE);

				/*level of the trigger activation in volt*/
				rp_AcqSetTriggerLevel(-0.02); 

				/*acquisition trigger delay*/
				rp_AcqSetTriggerDelay(buff_size/2);
		
				/*waiting for trigger*/
				while(1){
					rp_AcqGetTriggerState(&state);
					if(state == RP_TRIG_STATE_TRIGGERED){
						break;
					}
				}
				/*putt acquisition data in the temporary buffer*/
				rp_AcqGetOldestDataV(RP_CH_1, &buff_size, temp);

				/*additionning the N signals*/
				for (j = 0; j < buff_size; j++){
					buff[j]+=temp[j]/average;
				}

				/*release memory*/
				free(temp);
				rp_AcqReset();
			}

			//for (i=0 ; i<buff_size ; i++) {fprintf(fs, "\t%f", buff[i]/average);}
	
			MoyenneFichier = 0;
			for (i=buff_size - 1024 ; i<buff_size ; i++) {
				MoyenneFichier += buff[i];	
			}
			MoyenneFichier = MoyenneFichier / 1024;


			/*Nettoyage et simplification du signal */
			ttmp = 0;
			for (i=0 ; i<buff_size ; i++) {
				ttmp = (buff[i]- MoyenneFichier);
				/* cliping */
				if(ttmp > (SMAX)){
					ttmp = SMAX;
				}
				if(ttmp < (SMIN)){
					ttmp = SMIN;
				}
				/* end cliping */
				ibuff[i] = (int)((Scalling_Factor*ttmp));  //integer value between -255 et 255
			}
			free(buff);
			/* End of cleaning*/

			//Sending the image

			int *iToBuff = (int *)malloc(PointsNb * sizeof(int));
			int *tmp = (int *)malloc(PointsNb * sizeof(int));

			for (i = 0 ; i < PointsNb ; ++i) {
				tmp[i] = 0;
				for (j = 0 ; j < sampling ; ++j) {
			   		 tmp[i] += (int)(ibuff[i*sampling+j]*ibuff[i*sampling+j]) ;
			
				}
				iToBuff[i] = (int)(abs((tmp[i] / sampling))); //integer value between -65025 and 65025
			}
			free(ibuff);
		

			for (i=0 ; i<TaillerBuffer ; i++){UDPBuffer[i]=0;}
			for (i=0 ; i < NbPackets ; i++) { // iteration sur l'ensemble des packets du buffer

				UDPBuffer[0] = i; // Position of the packet inside the line
				UDPBuffer[1] = PWM_Position; //number of the line

				for (j=0; j < samples ; j++){ // iteration par points du packet
					UDPBuffer[2+j] = iToBuff[i*samples+j];
				}

				CheckUDP = sendto(s,UDPBuffer,sizeof(UDPBuffer),0,(struct sockaddr*) &si_other,slen);
	
				usleep(2);
				if (CheckUDP==-1) {die("sendto()");}
			}
	
			free(iToBuff);
			free(tmp);
		}
		oldPWM=PWM_Position;
	}
	/* Release rp resources */
	//fclose(fs);
	rp_Release();

	return 0;
}
