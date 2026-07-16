#ifndef PROTECTION_H
#define PROTECTION_H

#include "Adc.h"
#include "global.h"
#include "buck.h"

#define OUT_OVP_DELAY_TIME 20e-3

struct OVP_Param_TypeDef
{  
    float threshold;
    Uint16 delay;
};

struct OVP_State_TypeDef
{
    Uint16 cnt;
};

typedef struct
{
    struct OVP_Param_TypeDef param;
    struct OVP_State_TypeDef state;

}OVP_TypeDef;

typedef struct
{
    OVP_TypeDef OutOVP;   
}Protection;

extern Protection protection;


void Protection_Run(Feedback_TypeDef *feedback, Buck_Typedef *buck, Protection *protect0);
void OUT_OVP_Check(Feedback_TypeDef *feedback, Buck_Typedef *buck, Protection *protect0);
void OUT_OCP_Check(void);
void IN_OVP_Check(void);
void IN_OCP_Check(void);
void Protection_Init(Protection *protection);
#endif
