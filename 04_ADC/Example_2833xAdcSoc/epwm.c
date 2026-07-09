#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_EPwm_defines.h"

void InitEPwm1Simple(void)
{
    //============================================
    // time-base
    //============================================
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm1Regs.TBPRD = 1000;
    EPwm1Regs.TBCTR = 0;

    //undivided frequency
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV =TB_DIV1;

    //============================================
    // compare
    //============================================
    //shawdow load on zero
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    EPwm1Regs.CMPA.half.CMPA = 400;

    //============================================
    // action qualifier
    //============================================
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    //============================================
    // dead-band
    //============================================
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;

    EPwm1Regs.DBRED = 200;
    EPwm1Regs.DBFED = 200;
}

void InitEPwm6Simple(void)
{
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm6Regs.TBPRD = 1000;
    EPwm6Regs.TBCTR = 0;

    //undivided frequency
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV =TB_DIV1;

    EPwm6Regs.CMPA.half.CMPA = 500;

    //action
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
}

void InitEPwm1Soc(void)
{
    EALLOW;
    //
    // ADC configuration
    //
    AdcRegs.ADCMAXCONV.all = 0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;

    //
    // pwm configuration
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBPRD = 1000;
    EPwm1Regs.CMPA.half.CMPA = 500;
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPA;
    EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;

    EDIS;
}

