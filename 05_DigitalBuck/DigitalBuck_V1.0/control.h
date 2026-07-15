#ifndef CONTROL_H
#define CONTROL_H

// 原来的所有内容
#include "DSP28x_Project.h"

//Buck State macro
typedef enum 
{
    BOOL_NO = 0,
    BOOL_YES = 1
}Bool_e;

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

typedef enum
{
    INIT,
    WAIT_ENABLE,
    SOFTSTART,
    RUN,
    FAULT

}BuckState_e;

struct BuckFaultFlag_BITS // bits   description
{
    Uint16 OUT_OVP:1;       // 0      output OVP
    Uint16 OUT_OCP:1;       // 1      output OCP
    Uint16 IN_OVP:1;        // 2      input OVP
    Uint16 IN_OCP:1;        // 3      input OCP

};

typedef union 
{
    Uint16                    all;
    struct BuckFaultFlag_BITS bit;

}BuckFaultFlag_t;

typedef struct 
{
    float duty;
    float request_duty;

    BuckState_e state;
    BuckFaultFlag_t fault_flag;

    Uint16 enable;

}Buck_Typedef;

extern Buck_Typedef Buck;

void PI_Run(PI_TypeDef * pi);
void PI_Init(PI_TypeDef *pi);
void DutyLimit(Buck_Typedef *buck);
void Control_Run(void);
void UpdatePWM(float duty);
void StateMachine_Run(void);
Bool_e SoftStart_Run(void);
void SoftStart_Init(SoftStartType *softstart);

#endif




