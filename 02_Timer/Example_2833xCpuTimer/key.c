#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
static Uint16 key_event = 0;

void KEY_Scan(void)
{
    static Uint16 last = 1;
    Uint16 now;

    now = GpioDataRegs.GPADAT.bit.GPIO12;
    if (last == 1 && now == 0)
    {
        key_event = 1;
    }

    last = now;
}

Uint16 KEY_GetEvent(void)
{
    Uint16 temp = key_event;
    key_event = 0;

    return temp;
}


