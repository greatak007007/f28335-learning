#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
static Uint16 key_event = 0;

void KEY_Scan(void)
{
    static Uint16 last = 1;
    static Uint16 key_stable = 1;
    static Uint16 debounce_cnt = 0;
    Uint16 now = GpioDataRegs.GPADAT.bit.GPIO12;

    if (now == last)
    {
        if (debounce_cnt < 2)
        {
            debounce_cnt++;
        }
        if (debounce_cnt == 2)
        {
            if(key_stable != now)
            {
                key_stable = now;
                
                if(key_stable == 0)
                {
                    key_event = 1;
                }
            }
        }
    }
    else 
    {
        debounce_cnt = 0;
    }
    
    last = now;
}

Uint16 KEY_GetEvent(void)
{
    Uint16 temp = key_event;
    key_event = 0;

    return temp;
}


