#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_EPwm_defines.h"

void InitEPwm1Simple(void)
{
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm1Regs.TBPRD = 1000;
    EPwm1Regs.TBCTR = 0;

    //undivided frequency
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV =TB_DIV1;

    //shawdow load on zero
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_IMMEDIATE;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;

    EPwm1Regs.CMPA.half.CMPA = 600;

    //action
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
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
