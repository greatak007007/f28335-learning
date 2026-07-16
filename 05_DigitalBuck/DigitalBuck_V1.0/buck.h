#ifndef BUCK_H
#define BUCK_H

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File


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

void Buck_Init(Buck_Typedef *buck);

#endif
