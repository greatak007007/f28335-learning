//###########################################################################
//
// FILE:	Example_2833xGpioToggle.c
//
// TITLE:	GPIO Toggle Example
//
//! \addtogroup f2833x_example_list
//!
//! <h1>GPIO Toggle (gpio_toggle)</h1>
//!
//!  \note ALL OF THE I/O'S TOGGLE IN THIS PROGRAM.  MAKE SURE
//!  THIS WILL NOT DAMAGE YOUR HARDWARE BEFORE RUNNING THIS
//!  EXAMPLE.
//!
//!  Three different examples are included. Select the example
//!  (data, set/clear or toggle) to execute before compiling using
//!  the macros found at the top of the code.
//!
//!  Each example toggles all the GPIOs in a different way, the first
//!  through writing values to the GPIO DATA registers, the second through
//!  the SET/CLEAR registers and finally the last through the TOGGLE register
//!
//!  The pins can be observed using Oscilloscope.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2026 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines that select the example to compile in.  
// Only one example should be set as 1 the rest should be set as 0.
//
#define EXAMPLE1 0  // Use DATA registers to toggle I/O's
#define EXAMPLE2 0  // Use SET/CLEAR registers to toggle I/O's
#define EXAMPLE3 1  // Use TOGGLE registers to toggle I/O's

#define N 7
//
// Function Prototypes 
//
void delay_loop(void);
void Gpio_init(void);
void Gpio_example1(void);
void Gpio_example2(void);
void Gpio_example3(void);
void LED_Alloff(void);
void led_seq_init(Uint16 *arr, Uint16 len, Uint16 nmax);
void LED_ON(Uint16 led_no);


//
// Main
//

void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this example use the following configuration
    //
    

    //
    // Step 3. Clear all interrupts and initialize PIE vector table
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code:
    //
    Gpio_init();
    LED_Alloff();
#if EXAMPLE1
    //
    // This example uses DATA registers to toggle I/O's
    //
    Gpio_example1();
#endif  // - EXAMPLE1

#if EXAMPLE2
    //
    // This example uses SET/CLEAR registers to toggle I/O's
    //
    Gpio_example2();
#endif

#if EXAMPLE3
    //
    // This example uses TOGGLE registers to toggle I/O's
    //
    Gpio_example3();
#endif
}

//
// delay_loop - 
//
void 
delay_loop()
{
    volatile long i;
    for (i = 0; i < 1000000; i++) 
    {
        
    }
}

//
// Gpio_example1 -
//
void 
Gpio_example1(void)
{
    //
    // Example 1: Toggle I/Os using DATA registers
    //
    volatile Uint16 key_last = 1;
    volatile Uint16 key_now = 1;
    volatile Uint16 led_state = 1; // 1 off, 0 on

    GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
    
    for(;;)
    {
        key_now = GpioDataRegs.GPADAT.bit.GPIO12;
        if(key_now == 0 && key_last == 1)
        {
            DELAY_US(20000);
            if (GpioDataRegs.GPADAT.bit.GPIO12 == 0)
            {
                led_state = !led_state;
                if(led_state)
                {
                    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1;
                }
                else 
                {
                    GpioDataRegs.GPCSET.bit.GPIO68 = 1;
                }
            }
        }
        key_last = key_now;
        
    }
}

//
// led running
//
void 
Gpio_example2(void)
{
    Uint16 led_seq[2 * N - 2] = {0};
    Uint16 i = 0;

    led_seq_init(led_seq, 2*N-2, N);

    LED_Alloff();
    for(;;)
    {
        for(i = 0; i < 2 * N - 2; i++)
        {
            LED_ON(led_seq[i]);
            DELAY_US(1000000);
            LED_Alloff();
            DELAY_US(100000);
        }
    }
    
}

//
// Gpio_example3 -
//
void 
Gpio_example3(void)
{
    volatile Uint16 key_last = 1;
    volatile Uint16 key_now = 1;
    Uint16 run_flag = 0;
    Uint16 led = 1;

    GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
    
    for(;;)
    {
        /*push button detect*/
        key_now = GpioDataRegs.GPADAT.bit.GPIO12;
        if(key_now == 0 && key_last == 1)
        {
            DELAY_US(20000);
            if (GpioDataRegs.GPADAT.bit.GPIO12 == 0)
            {
                run_flag = !run_flag;
            }
        }
        key_last = key_now;
        if(run_flag)
        {
            LED_Alloff();
            
            LED_ON(led);
            DELAY_US(100000);
            led++;
            
            if(led > 7)
                led = 1;
        }
        else 
        {
            LED_Alloff();
            
        }
    }
}

//
// Gpio_init -
//
void 
Gpio_init(void)
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

//
// End of File
//
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
void led_seq_init(Uint16 *arr, Uint16 len, Uint16 nmax)
{
    Uint16 i;

    for(i = 0; i < nmax; i++)
    {
        arr[i] = i + 1;
    }
    for(i = nmax; i < len; i++)
    {
        arr[i] = len + 1 - i;
    }
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
