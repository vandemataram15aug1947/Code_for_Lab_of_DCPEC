#include "F28x_Project.h"
#include <math.h>
#define PI 3.14156
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitCpuTimers(void);
extern void ConfigCpuTimer(struct CPUTIMER_VARS *, float, float);
interrupt void cpu_timer0_isr(void);
void Gpio_select(void);
void Setup_ePWM4(void);
unsigned int i=0,in1, out1=0;
void main(void)
{
InitSysCtrl();
DINT;
Gpio_select();
Setup_ePWM4();
InitPieCtrl();
InitPieVectTable();
EALLOW;
PieVectTable.TIMER0_INT = &cpu_timer0_isr;
EDIS;
InitCpuTimers();
ConfigCpuTimer(&CpuTimer0, 100,10);
PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
IER |=1;
EINT;
ERTM;
CpuTimer0Regs.TCR.bit.TSS = 0; // start timer0
while(1)
{
}
}
void Gpio_select(void)
{
EALLOW;
GpioCtrlRegs.GPAMUX1.all = 0;
GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // ePWM4A active
GpioCtrlRegs.GPAMUX2.all = 0;
GpioCtrlRegs.GPBMUX1.all = 0;
GpioCtrlRegs.GPBMUX2.all = 0;
GpioCtrlRegs.GPCMUX1.all = 0;
GpioCtrlRegs.GPCMUX2.all = 0;
GpioCtrlRegs.GPADIR.all = 0;
GpioCtrlRegs.GPBDIR.all = 0;
GpioCtrlRegs.GPCDIR.all = 0;
EDIS;
}
void Setup_ePWM4(void)
{EPwm4Regs.TBCTR = 0x0000;
EPwm4Regs.TBCTL.bit.CLKDIV = 0;
EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;
EPwm4Regs.TBCTL.bit.CTRMODE = 2;
EPwm4Regs.AQCTLA.all = 0x0090;
EPwm4Regs.TBPRD = 12500;
EPwm4Regs.CMPA.bit.CMPA=1000;
}
interrupt void cpu_timer0_isr(void)
{
CpuTimer0.InterruptCount++;
EPwm4Regs.CMPA.bit.CMPA =.9*((EPwm4Regs.TBPRD + EPwm4Regs.TBPRD* sin (2*PI*50*out1*.00001))/2) ;
if(out1 ==2000)
{
out1=0;
}
else
{
out1++;
}
PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
