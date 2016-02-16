#include "../inc/control.h"

/* Initialize everything (The RP and all the configurations) */
void init_control(){
	/* Configuration */
	configure_pulse();
	configure_ramp();
	configure_fire_control();
	configure_ADC();
}

/* End everything (Stop Acquisition, motor and RP resources) */
void end_control() {
#if(EXTERNAL_TRIGGER)
	rp_DpinSetState(TRIGGER_SOURCE, RP_LOW);
#endif
	rp_DpinSetState(PULSE_PIN, RP_LOW);
	rp_DpinSetState(FIRE_CONTROL_PIN, RP_LOW);
	rp_AcqStop();
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

/* Configure the FIRE_CONTROL_PIN as an input */
void configure_fire_control() {
	rp_DpinSetDirection(FIRE_CONTROL_PIN, RP_IN);
}

/* Configure the PULSE_PIN as an output */
void configure_pulse() {
#if(EXTERNAL_TRIGGER)
	rp_DpinSetDirection(TRIGGER_SOURCE, RP_OUT);
#endif
	rp_DpinSetDirection(PULSE_PIN, RP_OUT);
}

/* Configure the ADC at 125MHz with an external trigger */
void configure_ADC() {
#if(!DECIMATE8)
	/* decimation n (=1,8,64...) : frequency = 125 MHz*/
	rp_AcqSetDecimation(RP_DEC_1);
#elif(DECIMATE8)
	/* decimation n (=1,8,64...) : frequency = 125 MHz*/
	rp_AcqSetDecimation(RP_DEC_8);
	/* Enable the averaging on the ADC */
	rp_AcqSetAveraging(TRUE);
#endif

	/*acquisition trigger delay and level activation*/
	rp_AcqSetTriggerLevel(0.1); //Trig level is set in Volts while in SCPI
        rp_AcqSetTriggerDelay(7000);

	/*start acquisition must be set before trigger initiation*/
	rp_AcqStart();

	/*trigger source, external, positif*/
#if(EXTERNAL_TRIGGER)
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_EXT_PE);
#else
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_PE);
#endif
	state = RP_TRIG_STATE_TRIGGERED;
}

/* Generate a pulse */
void pulse(rp_dpin_t pin) {
	rp_DpinSetState(pin, RP_HIGH);
	rp_DpinSetState(pin, RP_LOW);
}

/* Generate a ramp */
void ramp(rp_channel_t channel) {
	rp_GenOutEnable(channel);
}

/* Acquire one ray with the ADC */
float* acquireADC(uint32_t buff_size, float* temp) {
#if(EXTERNAL_TRIGGER)
	pulse(TRIGGER_SOURCE);
#endif
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
