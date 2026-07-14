#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Adc.h"
#include "control.h"
#include "epwm.h"
#include "general.h"

static volatile Uint16 adc_vin = 0, adc_vout = 0, adc_iout = 0;

void InitEPwm1Soc(void)
{
    //---------------------------------------
    //time-base
    //---------------------------------------
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBPRD = 1000;
    EPwm1Regs.TBCTR = 0;

    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    //---------------------------------------
    //compare
    //---------------------------------------
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    //---------------------------------------
    //action-qualifier
    //---------------------------------------
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    //---------------------------------------
    //event-trigger
    //---------------------------------------
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
    EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;
    EPwm1Regs.ETCLR.bit.SOCA = 1;

}

void InitAdcSoc(void)
{
    //----------------------------------
    // 1. ADC Clock
    //----------------------------------
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;//adc clock = 12.5M
    AdcRegs.ADCTRL1.bit.CPS = 0;
    //----------------------------------
    // 2. ADC Mode
    //----------------------------------
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
    //----------------------------------
    // 3. Sample Window
    //----------------------------------
    AdcRegs.ADCTRL1.bit.ACQ_PS = 6;
    //----------------------------------
    // 4. Sequencer
    //----------------------------------
    AdcRegs.ADCMAXCONV.all = 2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ADC_CH_VOUT;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ADC_CH_IOUT;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ADC_CH_VIN;
    //----------------------------------
    // 5. Trigger Source
    //----------------------------------
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    //----------------------------------
    // 6. ADC Interrupt
    //----------------------------------
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
}

__interrupt void  adc_isr(void)
{
    Uint16 cmpa;
    static float vin, iout, error;
    float vout_pin, vout;
    //----------------------------------
    // 1. Read ADC 
    //----------------------------------
    ADC_Read();
    //-----------------------
    // Calculate Error
    //-----------------------
    vout_pin = AdcToVol(adc_vout);
    vout = VoltageScale(vout_pin, R_UP, R_DOWN);
    error = VREF - vout;
    //-----------------------
    // Incremental PI
    //-----------------------
    cmpa = (Uint16) PI_Cal(error);
    //-----------------------
    // Update PWM
    //-----------------------
    UpdatePWM(cmpa);
    //-----------------------
    // Save History
    //-----------------------

    //----------------------------------
    // 3. Prepare Next Conversion
    //----------------------------------
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    //----------------------------------
    // 4. Clear ADC Interrupt Flag
    //----------------------------------
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    //----------------------------------
    // 5. Acknowledge PIE
    //----------------------------------    
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

float AdcToVol(Uint16 adc_value)
{
    return (float) adc_value / ADC_MAX * 3.0f ;
}
float VoltageScale(float vout_pin, float r_up, float r_down)
{
    return vout_pin * (1 + r_up / r_down);
}

void ADC_Read(void)
{
    adc_vout = AdcRegs.ADCRESULT0 >> 4;
    adc_iout = AdcRegs.ADCRESULT1 >> 4;
    adc_vin = AdcRegs.ADCRESULT2 >> 4;
}
