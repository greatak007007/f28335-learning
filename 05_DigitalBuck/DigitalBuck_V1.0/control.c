#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "control.h"
#include "Adc.h"
#include "epwm.h"
#include "global.h"

static PI_TypeDef VoltageLoop;
Buck_Typedef Buck;
static Bool_e softstart_finished;
static SoftStartType softstart;

void StateMachine_Run(void)
{
    switch (Buck.state) 
    {
        case INIT:
            PI_Init(&VoltageLoop);
            Buck.duty = 0;
            Buck.fault_flag.all = 0x0;
            Buck.state = WAIT_ENABLE;
            break;
        case WAIT_ENABLE:
            if(Buck.enable)
            {
                SoftStart_Init(&softstart);
                Buck.state = SOFTSTART;
            }    
            break;
        case SOFTSTART:
            softstart_finished = SoftStart_Run();
            Control_Run();
            if(softstart_finished)
            {
                Buck.state = RUN;
            }
            break;
        case RUN:
            Control_Run();
            if(Buck.fault_flag.all != 0)
                Buck.state = FAULT;
            break;
        case FAULT:
            Buck.state = INIT;
            break;
        default:
            break;
    }
}

void Control_Run(void)
{

    VoltageLoop.state.feedback = Feedback.voltage.vout;
    VoltageLoop.state.error = VoltageLoop.state.Controlref - VoltageLoop.state.feedback;

    PI_Run(&VoltageLoop);

    Buck.request_duty = VoltageLoop.state.output_unlimit;
    DutyLimit(&Buck);
    //-----------------------
    // Update PWM
    //-----------------------
    UpdatePWM(Buck.duty);
}

void PI_Run(PI_TypeDef * pi)
{
    float delta_cmpa;

    if(pi->state.is_initialized == BOOL_NO)
    {
        pi->state.is_initialized = BOOL_YES;
        pi->state.error_last = pi->state.error;
    }
    
    delta_cmpa = pi->param.kp * (pi->state.error - pi->state.error_last) + pi->param.ki * pi->state.error;

    pi->state.output_unlimit += delta_cmpa;

    pi->state.error_last = pi->state.error;

}

void PI_Init(PI_TypeDef *pi)
{
    pi->param.kp = 20;
    pi->param.ki = 1;
    pi->param.TargetRef = 1.5;

    pi->state.output_unlimit = 500;
    pi->state.Controlref = 0;
    pi->state.is_initialized = BOOL_NO;
}

void DutyLimit(Buck_Typedef *buck)
{
    if (buck->request_duty > 1000)
        buck->duty = 1000;

    if (buck->request_duty < 0)
        buck->duty = 0;
}
void UpdatePWM(float duty)
{
    EPwm1Regs.CMPA.half.CMPA = (Uint16) duty;
}
Bool_e SoftStart_Run(void)
{
    float step_num;

    if(softstart.state.is_initialized == BOOL_NO)
    {
        //calculate step
        step_num = softstart.param.start_time * PWM_FRQ;
        softstart.param.step = VoltageLoop.param.TargetRef / step_num;

        softstart.state.is_initialized = BOOL_YES;
    }
    VoltageLoop.state.Controlref += softstart.param.step;

    if(VoltageLoop.state.Controlref >= VoltageLoop.param.TargetRef)
    {
        VoltageLoop.state.Controlref = VoltageLoop.param.TargetRef;

        return BOOL_YES;
    }
    else 
    {
        return BOOL_NO;
    }
    
}

void SoftStart_Init(SoftStartType *ss)
{
    ss->state.is_initialized = BOOL_NO;

    ss->param.start_time = 20e-3;
}

