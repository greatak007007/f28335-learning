#ifndef CONTROL_H
#define CONTROL_H

// 原来的所有内容
#include "DSP28x_Project.h"
#include "buck.h"
#include "Adc.h"
#include "epwm.h"
#include "global.h"



typedef struct 
{
    float TargetRef;

    float kp;
    float ki;

}PI_ParamDef;


struct SoftStartParam
{
    float step;
    float start_time;
};


struct SoftStartState
{
    Uint16 is_initialized;
};

typedef struct 
{
    struct SoftStartParam param;
    struct SoftStartState state;
    
}SoftStartType;

typedef struct
{
    float Controlref;

    float feedback;

    float error;
    float error_last;

    float output_unlimit;
    float control_output;
    

    Uint16 is_initialized;
}PI_StateDef;



typedef struct
{
    
    PI_ParamDef param;

    PI_StateDef state;

}PI_TypeDef;

extern PI_TypeDef VoltageLoop;

void PI_Run(PI_TypeDef * pi);
void PI_Init(PI_TypeDef *pi);
void DutyLimit(Buck_Typedef *buck);
void Control_Run(PI_TypeDef *voltageloop, Feedback_TypeDef *feedback, Buck_Typedef *buck);
void UpdatePWM(Buck_Typedef *buck);
void StateMachine_Run(void);
Uint16 SoftStart_Run(void);
void SoftStart_Init(SoftStartType *softstart);
#endif




