#define ADC_CH_VOUT 0x0
#define ADC_CH_IOUT 0x1
#define ADC_CH_VIN 0x2
#define ADC_MAX 4096

#define VREF 1.5
#define R_UP 0.0f
#define R_DOWN 10e3f

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

extern Feedback_TypeDef Feedback;


void InitEPwm1Soc(void);
void InitAdcSoc(void);
__interrupt void  adc_isr(void);
float AdcToVoltage(Uint16 adc_value);
float VoutScale(Uint16 adc_value);
void ADC_Read(void);






