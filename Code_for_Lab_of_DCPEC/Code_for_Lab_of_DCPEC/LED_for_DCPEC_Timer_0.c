
/*
 * LED for DCPEC_Timer_0.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Vande
 */

#include "F28x_Project.h"
__interrupt void cpu_timer0_isr(void);
void main(void)
{
InitSysCtrl();
DINT;
InitPieCtrl();
IER = 0x0000;
IFR = 0x0000;
InitPieVectTable();
EALLOW;
PieVectTable.TIMER0_INT = &cpu_timer0_isr;
EDIS;
InitCpuTimers();
ConfigCpuTimer(&CpuTimer0, 60, 500000);
CpuTimer0Regs.TCR.all = 0x4001;
EALLOW;
GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
EDIS;
IER |= M_INT1;
PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
EINT; // Enable Global __interrupt INTM
ERTM; // Enable Global realtime __interrupt DBGM
for(;;);
}
__interrupt void cpu_timer0_isr(void)
{
CpuTimer0.InterruptCount++;
GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
