/*
 * LED for DCPEC_Timer_2.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Vande
 */


#include "F28x_Project.h"
void delay_loop(void);
__interrupt void kkk(void);
__interrupt void kkm(void);
void main(void)
{
InitSysCtrl();
DINT;
InitCpuTimers();
InitPieCtrl();
InitPieVectTable();
//
EALLOW; // This is needed to write to EALLOW protected registers PieVectTable.TIMER0_INT = &kkk;
PieVectTable.TIMER2_INT = &kkm;
EDIS; // This is needed to disable write to EALLOW protected registers
InitCpuTimers(); // For this example, only initialize the Cpu Timers
ConfigCpuTimer(&CpuTimer0, 25,100000); // (t=100*300000*10-8=0.025 seconds)
ConfigCpuTimer(&CpuTimer2, 75,500000); // (t=150*500000*10-8=0.75 seconds)
CpuTimer0Regs.TCR.all = 0x4000;
CpuTimer2Regs.TCR.all = 0x4000;
EALLOW;
GpioCtrlRegs.GPBMUX1.bit.GPIO34=0;;
GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
EDIS;
IER |= M_INT1;
IER |= M_INT14;
//
// Enable TINT0 in the PIE: Group 1 __interrupt 7
//
PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
EINT; // Enable Global __interrupt INTM
while(1)
{
}
} __interrupt void kkk(void)
{
GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
__interrupt void kkm(void)
{
GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
