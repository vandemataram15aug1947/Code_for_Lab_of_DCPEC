

// HOW TO Genarate multiple PWM Signals

#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "driverlib.h"
#include "device.h"


void GPIO_Init();
void PWM_Init_1();
void PWM_Init_2();

void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
       // Initialize PIE and clear PIE registers. Disables CPU interrupts.
       //
       Interrupt_initModule();

       //
       // Initialize the PIE vector table with pointers to the shell Interrupt
       // Service Routines (ISR).
       //
       Interrupt_initVectorTable();

       // Configure ePWMs
       //

       GPIO_Init();

       // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
       SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

       //
       // Initialize ePWM1
       //

       PWM_Init_1();
       PWM_Init_2();

       SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
       //
       // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
       //
       EINT;
       ERTM;

       while(1)
       {

       }

}


void PWM_Init_1()
{
      EPwm1Regs.TBPRD = 3000;       // Set timer period 801 TBCLKs
      EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
      EPwm1Regs.TBCTR = 0x0000;

      // Set Compare values
      EPwm1Regs.CMPA.bit.CMPA = 1500;    // Set compare A value

      // Setup counter mode
      EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
      EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
      EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
      EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
      //
      EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
      EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

}


void PWM_Init_2()
{


    EPwm2Regs.TBPRD = 5000;       // Set timer period 801 TBCLKs
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;
   // Set Compare values
//    EPwm1Regs.CMPB.bit.CMPB=1000;    // Set compare A value
    EPwm2Regs.CMPA.bit.CMPA = 3500;    // Set compare A value
  // Setup counter mode
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM2A on Zero
   EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;



}

void GPIO_Init()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO1 as EPWM1B
    EDIS;
}



