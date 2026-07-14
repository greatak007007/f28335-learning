#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "control.h"
#include "Adc.h"
#include "epwm.h"

static PI_TypeDef VoltageLoop;
static Buck_Typedef Buck;

void Control_Run(void)
{

    VoltageLoop.state.feedback = Feedback.voltage.vout;
    VoltageLoop.state.error = VoltageLoop.state.ref - VoltageLoop.state.feedback;

    PI_Run(&VoltageLoop);

    Buck.duty = VoltageLoop.state.output_unlimit;
    DutyLimit(&Buck);
    //-----------------------
    // Update PWM
    //-----------------------
    UpdatePWM(Buck.duty);
}

void PI_Run(PI_TypeDef * pi)
{
    float delta_cmpa;

    if(pi->state.is_initialized == NO)
    {
        pi->state.is_initialized = YES;
        pi->state.error_last = pi->state.error;
    }
    
    delta_cmpa = pi->param.kp * (pi->state.error - pi->state.error_last) + pi->param.ki * pi->state.error;

    pi->state.output_unlimit += delta_cmpa;

    pi->state.error_last = pi->state.error;

}

void PI_Init(void)
{
    VoltageLoop.param.kp = 20;
    VoltageLoop.param.ki = 1;

    VoltageLoop.state.output_unlimit = 500;
    VoltageLoop.state.ref = 1.5;
    VoltageLoop.state.is_initialized = NO;
}

void DutyLimit(Buck_Typedef *buck)
{
    if (buck->duty > 1000)
        buck->duty = 1000;

    if (buck->duty < 0)
        buck->duty = 0;
}


