void InitEPwm1Soc(void);
void InitAdcSoc(void);
__interrupt void  adc_isr(void);
float AdcToVol(Uint16 adc_value);
float VoltageScale(float vout_pin, float r_up, float r_down);
void ADC_Read(void);

#define ADC_CH_VOUT 0x0
#define ADC_CH_IOUT 0x1
#define ADC_CH_VIN 0x2
#define ADC_MAX 4096


