#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "epwm.h"
#include "Adc.h"
#include "control.h"
#include "Protection.h"
#include "buck.h"
//
// Globals
//
Uint16 LoopCount;
Uint16 ConversionCount;
Uint16 Voltage1[10];
Uint16 Voltage2[10];

//
// Main
//
void main(void)
{
    InitSysCtrl();

    DINT;

    InitPieCtrl();

    IER = 0;
    IFR = 0;

    InitPieVectTable();

    EALLOW;
    PieVectTable.ADCINT = &adc_isr;
    EDIS;


    InitAdc();
    
    InitAdcSoc();

    InitEPwm1Soc();


    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;

    IER |= M_INT1;

    EINT;
    ERTM;
    
    //open adc interrupt
    Buck_Init(&Buck);
    PI_Init(&VoltageLoop);

    //Protection_Init(&protection);
    while (1) 
    {
    
    }
}


