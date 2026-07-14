extern volatile Uint16 adc_value;

void InitEPwm1Soc(void);
void InitAdcSoc(void);
__interrupt void  adc_isr(void);

#define ADC_CH_VOUT 0x1
#define ADC_CH_IOUT 0x2
#define ADC_CH_VIN 0x0
