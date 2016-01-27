#ifndef CONTROL_H
#define CONTROL_H

#include "common.h"

/* Define the Pin for signals and acquisitions and the size of the buffer */
#define PULSE_PIN RP_DIO1_P
#define PWM_PIN RP_DIO2_P
#define ACQUISITION_PIN RP_CH_1
#define RAMP_PIN RP_CH_2

/* Mandatory variable which represent the trigger state */
rp_acq_trig_state_t state;
pthread_t control_motor_thread;

void *control_motor (void *p_data);

void init_control();

void end_control();

void reset();

void configure_ramp();

void configure_pwm();

void configure_pulse();

void configure_ADC();

void pulse();

void ramp();

float* acquireADC(uint32_t buff_size, float* temp);

#endif
