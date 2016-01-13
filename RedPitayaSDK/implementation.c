#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/rp.h"

/* Define the Pin for pulse and the size of the buffer */
#define PULSE_PIN RP_DIO1_P
#define BUFFER_SIZE 16384

/* Mandatory variable which represent the trigger state */
rp_acq_trig_state_t state;

/* Reset everyhting to down/low state */
void reset() {
	rp_DpinReset();
	rp_GenReset();
	rp_AcqReset();
}

/* Configure the Channel 2 for generating a ramp with a 10 kHz frequency */
void configure_ramp() {
	rp_GenWaveform(RP_CH_2, RP_WAVEFORM_RAMP_UP);
	rp_GenMode(RP_CH_2, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RP_CH_2, 1);
	rp_GenAmp(RP_CH_2, 1.0);
	rp_GenFreq(RP_CH_2, 10000.0);
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
	configure_ADC();
}

/* End everything (Stop Acquisition and RP resources) */
void end() {
	rp_AcqStop();
	rp_Release();
}

/* Generate a pulse */
void pulse() {
	rp_DpinSetState(PULSE_PIN, RP_HIGH);
	rp_DpinSetState(PULSE_PIN, RP_LOW);
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
	rp_AcqGetOldestDataV(RP_CH_1, &buff_size, temp);

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
		rp_GenOutEnable(RP_CH_2);
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
