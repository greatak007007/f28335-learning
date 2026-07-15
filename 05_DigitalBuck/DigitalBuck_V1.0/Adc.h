#ifndef ADC_H
#define ADC_H

// 原来的所有内容

#include "control.h"

#define ADC_CH_VOUT 0x0
#define ADC_CH_IOUT 0x1
#define ADC_CH_VIN 0x2
#define ADC_MAX 4096

#define VREF 1.5
#define R_UP 0.0f
#define R_DOWN 10e3f

#define TB_PERIOD 1000
#define PWM_FRQ SYSCLK_FRQ / TB_PERIOD

typedef struct
{
    float vin;
    float vout;

}Feedback_Voltage_TypeDef;

typedef struct 
{
    float iout;

}Feedback_Current_TypeDef;

typedef struct
{
    Feedback_Voltage_TypeDef voltage;

    Feedback_Current_TypeDef current;
    
}Feedback_TypeDef;

typedef struct
{
    Uint16 vin;
    Uint16 vout;
    Uint16 iout;

}ADC_ResultTypeDef;

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

extern Feedback_TypeDef Feedback;

void InitEPwm1Soc(void);
void InitAdcSoc(void);
__interrupt void  adc_isr(void);
float AdcToVoltage(Uint16 adc_value);
void ADCResultRead(ADC_ResultTypeDef *AdcResult);
void FeedbackRun(Feedback_TypeDef *feedback, ADC_ResultTypeDef *adc_result);


#endif








