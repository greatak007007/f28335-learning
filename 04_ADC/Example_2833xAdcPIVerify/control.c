#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "control.h"
#include "Adc.h"
#include "general.h"

PI_TypeDef pi;

float PI_Cal(float error)
{
    float delta_cmpa;

    if(!pi.initialized)
    {
        pi.initialized = 1;
        pi.error_last = error;
    }
    
    delta_cmpa = pi.kp * (error - pi.error_last) + pi.ki * error;

    pi.output += delta_cmpa;

    Out_Limit(pi.output);

    pi.error_last = error;

    return pi.output;
}

void PI_Init(void)
{
    pi.kp = 20;
    pi.ki = 1;
    pi.output = 500;
    pi.initialized = 0;
}

