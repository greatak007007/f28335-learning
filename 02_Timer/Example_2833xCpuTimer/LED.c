#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
static Uint16 led = 1;


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

void LED_Run(void)
{
    LED_Alloff();
    LED_ON(led);
    led++;
    if(led > 7)
        led = 1;
}
