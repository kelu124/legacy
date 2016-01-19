#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "inc/rp.h"

/* Define the Pin for signals and acquisitions and the size of the buffer */
#define PULSE_PIN RP_DIO1_P
#define PWM_PIN RP_DIO2_P
#define ACQUISITION_PIN RP_CH_1
#define RAMP_PIN RP_CH_2
#define BUFFER_SIZE 16384

/* Mandatory variable which represent the trigger state */
rp_acq_trig_state_t state;
pthread_t control_motor_thread;
int stop = 0;

static void *control_motor (void *p_data) {
	struct timeval init_time, end_time;
	int percentage_fluctuation = 0;

	/* While the program isn't ending */
	while(!stop) {
		/* For the motor slavering */
/*		gettimeofday(&init_time,NULL);
		gettimeofday(&end_time,NULL);
		percentage_fluctuation = (end_time-init_time)*100/2740*/

		/* Switch to High state then wait the right time before completing the period with Low state */
		rp_DpinSetState(PWM_PIN, RP_HIGH);
		usleep(2666*(55-percentage_fluctuation)/100);
		rp_DpinSetState(PWM_PIN, RP_LOW);
		usleep(2666*(45-percentage_fluctuation)/100);
	}

	return NULL;
}

/* Reset everyhting to down/low state */
void reset() {
	rp_DpinReset();
	rp_ApinReset();
	rp_GenReset();
	rp_AcqReset();
}

/* Configure the RAMP_PIN for generating a ramp with a 10 kHz frequency */
void configure_ramp() {
	rp_GenWaveform(RAMP_PIN, RP_WAVEFORM_RAMP_UP);
	rp_GenMode(RAMP_PIN, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RAMP_PIN, 1);
	rp_GenAmp(RAMP_PIN, 1.0);
	rp_GenFreq(RAMP_PIN, 10000.0);
}

/* Configure the PWM_PIN as an output */
void configure_pwm() {
	rp_DpinSetDirection(PWM_PIN, RP_OUT);
}

/* Configure the PULSE_PIN as an output */
void configure_pulse() {
	rp_DpinSetDirection(PULSE_PIN, RP_OUT);
}

/* Configure the ADC at 125MHz with an external trigger */
void configure_ADC() {
	rp_DpinSetDirection(RP_TRIG_SRC_EXT_PE, RP_IN);

	/* decimation n (=1,8,64...) : frequency = 125 MHz*/
	rp_AcqSetDecimation(RP_DEC_1);

	/*start acquisition must be set before trigger initiation*/
	rp_AcqStart();

	/*trigger source, external, positif*/ 
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_EXT_PE);

	/*acquisition trigger delay*/
	rp_AcqSetTriggerDelay(7000);
}

/* Initialize everything (The RP and all the configurations) */
void init(){
	/* RP Initialization */
	if (rp_Init() != RP_OK) {
		perror("Red Pitaya API init failed!");
		exit(EXIT_FAILURE);
	}

	reset();

	/* Configuration */
	configure_pulse();
	configure_ramp();
	configure_pwm();
	configure_ADC();

	/* Launch the motor routine */
	pthread_create(&control_motor_thread, NULL, control_motor, NULL);
}

/* End everything (Stop Acquisition, motor and RP resources) */
void end() {
	stop = 1;
	pthread_join(control_motor_thread, NULL);
	rp_DpinSetState(PULSE_PIN, RP_LOW);
	rp_DpinSetState(PWM_PIN, RP_LOW);
	rp_AcqStop();
	rp_Release();
}

/* Generate a pulse */
void pulse() {
	rp_DpinSetState(PULSE_PIN, RP_HIGH);
	rp_DpinSetState(PULSE_PIN, RP_LOW);
}

/* Generate a ramp */
void ramp() {
	rp_GenOutEnable(RAMP_PIN);
}

/* Acquire one ray with the ADC */
float* acquireADC(int buff_size, float* temp) {

	/*waiting for trigger*/
	while(1){
		rp_AcqGetTriggerState(&state);
		if(state == RP_TRIG_STATE_TRIGGERED){
			break;
		}
	}

	/*put acquisition data in the temporary buffer*/
	rp_AcqGetOldestDataV(ACQUISITION_PIN, &buff_size, temp);

	return(temp);
}

int main(int argc, char *argv[]) {
	/* Variable Declaration and Initialization */
	int buff_size = BUFFER_SIZE, i = 0;
	float *temp = NULL, *buffer = NULL;

	/* Memory Allocation */
	temp = malloc(buff_size * sizeof(float));
	buffer = malloc(buff_size * sizeof(float));

	/* Initialization */
	init();

	/* Main routine:
	 * Pulse
	 * Wait 66us
	 * Generate one ramp
	 * Do an acquisition (wait 100 us for simulation without acquisition)
	 */
	for(i = 0; i < 20000; i++) {
		pulse();
		usleep(66);
		ramp();
		usleep(100);
//		buffer = acquireADC(buff_size, temp);
	}

	/* RP and Variables Release */
	free(temp);
	free(buffer);

	/* End everything */
	end();

	return EXIT_SUCCESS;
}
