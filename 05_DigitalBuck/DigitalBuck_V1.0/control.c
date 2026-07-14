#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "control.h"
#include "Adc.h"
#include "epwm.h"

static PI_TypeDef VoltageLoop;

void Control_Run(void)
{

    VoltageLoop.feedback = Feedback.vout;
    VoltageLoop.error = VoltageLoop.ref - VoltageLoop.feedback;

    PI_Run(&VoltageLoop);
    //-----------------------
    // Update PWM
    //-----------------------
    UpdatePWM((Uint16) VoltageLoop.output);
}

void PI_Run(PI_TypeDef * pi)
{
    float delta_cmpa;

    if(!pi->initialized)
    {
        pi->initialized = 1;
        pi->error_last = pi->error;
    }
    
    delta_cmpa = pi->kp * (pi->error - pi->error_last) + pi->ki * pi->error;

    pi->output += delta_cmpa;

    pi->output = Out_Limit(pi->output);

    pi->error_last = pi->error;

}

void PI_Init(void)
{
    VoltageLoop.kp = 20;
    VoltageLoop.ki = 1;
    VoltageLoop.output = 500;
    VoltageLoop.ref = 1.5;

    VoltageLoop.initialized = 0;
}

float Out_Limit(float out)
{
    if (out > 1000)
        out = 1000;

    if (out < 0)
        out = 0;

    return out;
}


