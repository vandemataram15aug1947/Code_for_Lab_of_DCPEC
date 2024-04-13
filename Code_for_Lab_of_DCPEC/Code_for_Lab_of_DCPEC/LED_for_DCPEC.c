
#include "F28x_Project.h"
void delay_loop();
void main(void)
{
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    EDIS;

    while(1)
    {
        GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
        delay_loop();

        GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
        delay_loop();
    }
    }

void delay_loop()
{
   long int i;
   for(i = 0; i<=1666666; i++){}

}


/*
Fow RAM or FLASH = 12 clock cycles; i = 0 to 1;
System clock 200MHz; 1/200MHz=5ns; (1ns=10^-9s)
12*5= 60ns
For i=1..............60ns
For i=x..............1/60ns
                     = 1666666

 */
