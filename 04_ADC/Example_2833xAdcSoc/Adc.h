extern volatile Uint16 adc_value;

void InitEPwm1Soc(void);
void InitAdcSoc(void);
__interrupt void  adc_isr(void);

