#include "control.h"
#include "global.h"

PI_TypeDef VoltageLoop;
static Uint16 softstart_finished;
static SoftStartType softstart;

void StateMachine_Run(void)
{
    switch (Buck.state) 
    {
        case INIT:
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
            Control_Run(&VoltageLoop, &Feedback, &Buck);
            if(softstart_finished)
            {
                Buck.state = RUN;
            }
            break;
        case RUN:
            Control_Run(&VoltageLoop, &Feedback, &Buck);
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

void Control_Run(PI_TypeDef *voltageloop, Feedback_TypeDef *feedback, Buck_Typedef *buck)
{

    voltageloop->state.feedback = feedback->voltage.vout;
    voltageloop->state.error = voltageloop->state.Controlref - voltageloop->state.feedback;

    PI_Run(voltageloop, buck);

    buck->request_duty = voltageloop->state.output_unlimit;
    buck->duty = buck->request_duty;
    DutyLimit(buck);
    //-----------------------
    // Update PWM
    //-----------------------
    UpdatePWM(buck);
}

void PI_Run(PI_TypeDef * pi)
{
    float proportional_delta, integral_delta;
    float predict_duty;
    Uint16 allow_integral;

    if(pi->state.is_initialized == BOOL_NO)
    {
        pi->state.is_initialized = BOOL_YES;
        pi->state.error_last = pi->state.error;
    }

    proportional_delta = pi->param.kp * (pi->state.error - pi->state.error_last);
    integral_delta = pi->param.ki * pi->state.error;

    predict_duty = pi->state.output_unlimit;

    predict_duty += (proportional_delta + integral_delta);

    // judge integral saturation
    if((predict_duty >= DUTY_MAX && pi->state.error > 0) ||
       (predict_duty <= DUTY_MIN && pi->state.error < 0) )
    {
        allow_integral = BOOL_NO;
    }
    else 
        allow_integral = BOOL_YES;

    if(allow_integral)
    {
        pi->state.output_unlimit += (proportional_delta + integral_delta);
    }
    else 
        pi->state.output_unlimit += proportional_delta;    

    pi->state.error_last = pi->state.error;

}

void PI_Init(PI_TypeDef *pi)
{
    pi->param.kp = 20;
    pi->param.ki = 1;
    pi->param.TargetRef = 1.5;

    pi->state.output_unlimit = 500;
    pi->state.Controlref = 1.5;
    pi->state.is_initialized = BOOL_NO;
}

void DutyLimit(Buck_Typedef *buck)
{
    if (buck->request_duty > 1000)
        buck->duty = 1000;

    if (buck->request_duty < 0)
        buck->duty = 0;
}
void UpdatePWM(Buck_Typedef *buck)
{
    EPwm1Regs.CMPA.half.CMPA = (Uint16) buck->duty;
}
Uint16 SoftStart_Run(void)
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

