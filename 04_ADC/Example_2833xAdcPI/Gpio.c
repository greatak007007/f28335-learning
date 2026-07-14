#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

void Gpio_init(void)
{
    EALLOW;
    
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    /**********************************/
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    /**********************************/
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO67 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO65 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO64 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    /**********************************/
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;
    /**********************************/
    GpioCtrlRegs.GPCPUD.bit.GPIO68 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO67 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO66 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO65 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO64 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
    /**********************************/
    GpioCtrlRegs.GPBPUD.bit.GPIO48 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;
    /**********************************/
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;
    
    EDIS;
}






