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
    
    /**********************************/
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO67 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO65 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO64 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    /**********************************/
    
    /**********************************/
    GpioCtrlRegs.GPCPUD.bit.GPIO68 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO67 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO66 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO65 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO64 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
    /**********************************/
    

    EDIS;
}

void LED_Alloff(void)
{
    GpioDataRegs.GPCSET.bit.GPIO68 = 1;
    GpioDataRegs.GPCSET.bit.GPIO67 = 1;
    GpioDataRegs.GPCSET.bit.GPIO66 = 1;
    GpioDataRegs.GPCSET.bit.GPIO65 = 1;
    GpioDataRegs.GPCSET.bit.GPIO64 = 1;
    GpioDataRegs.GPASET.bit.GPIO10 = 1;
    GpioDataRegs.GPASET.bit.GPIO11 = 1;
}

void LED_ON(Uint16 led_no)
{
    switch (led_no) 
    {
        case 1:
            GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
            break;
        case 2:
            GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
            break;
        case 3:
            GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
            break;
        case 4:
            GpioDataRegs.GPCCLEAR.bit.GPIO65 = 1;
            break;
        case 5:
            GpioDataRegs.GPCCLEAR.bit.GPIO64 = 1;
            break;
        case 6:
            GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
            break;
        case 7:
            GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
            break;
        default: 
            LED_Alloff();
            break;
    }
}