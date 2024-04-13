/*
 * LAB_Exp_a.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Vande
 */


#include "F28x_Project.h"
void Gpio_select(void);
void Setup_ePWM(void);
void main(void)
{
    InitSysCtrl();
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
    DINT;
    Gpio_select();
    Setup_ePWM();

    while(1){
    }
}

void Gpio_select(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // ePWM4A active
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1; // ePWM4B active
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1; // ePWM5A active
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1; // ePWM5B active
    EDIS;
}

void Setup_ePWM(void)
{
    EPwm4Regs.TBCTL.bit.CLKDIV = 2;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 2;
    EPwm4Regs.TBCTL.bit.CTRMODE = 0;
    EPwm4Regs.AQCTLA.all = 0x0060; // set ePWM1A on CMPA up

    // clear ePWM1A on CMPA down
    EPwm4Regs.AQCTLB.all = 0x0090; // clear ePWM1B on CMPA up

    // set ePWM1B on CMPA down
    EPwm4Regs.TBPRD = 500;
    EPwm4Regs.CMPA.bit.CMPA = 450;
    EPwm5Regs.TBCTL.bit.CLKDIV = 2;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = 2;
    EPwm5Regs.TBCTL.bit.CTRMODE = 0; // up - down mode
    EPwm5Regs.AQCTLA.all = 0x0060;
    EPwm5Regs.AQCTLB.all = 0x0090;
    EPwm5Regs.TBPRD = 500;
    EPwm5Regs.CMPA.bit.CMPA=450;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 1; // generate a syncout if CTR = 0
    EPwm5Regs.TBCTL.bit.PHSEN = 1; // enable phase shift
    EPwm5Regs.TBPHS.bit.TBPHS = 3125;
}



