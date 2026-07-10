#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

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
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 4;
    //----------------------------------
    // 2. ADC Mode
    //----------------------------------

    //----------------------------------
    // 3. Sample Window
    //----------------------------------

    //----------------------------------
    // 4. Sequencer
    //----------------------------------

    //----------------------------------
    // 5. Trigger Source
    //----------------------------------

    //----------------------------------
    // 6. ADC Interrupt
    //----------------------------------
}
