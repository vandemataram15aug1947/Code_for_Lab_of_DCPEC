/*
 * Code_for_DeadBand_with_180_degree_Phase_Shift .c
 *
 *  Created on: Apr 8, 2024
 *      Author: Vande
 */


// HOW TO Genarate Complementary PWM Signals

#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "driverlib.h"
#include "device.h"


void InitPWM_1(void);

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
       //Interrupt_initModule();

       //
       // Initialize the PIE vector table with pointers to the shell Interrupt
       // Service Routines (ISR).
       //
      // Interrupt_initVectorTable();

       // Configure ePWMs
       //

      //GPIO_Init();

       // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
       //SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

       //
       // Initialize ePWM1
       //

    // Configure GPIO pins as pwms signal
        EALLOW;
        GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Disable pull-up on GPIO0 (EPWM1A)
        GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Disable pull-up on GPIO1 (EPWM1B)

        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO1= 1;   // Configure GPIO1 as EPWM1B
        EDIS;


        InitPWM_1();

        while(1)
        {

            }




 }

       //SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
       //
       // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
       //
       //EINT;
       //ERTM;



// init ePWM
void InitPWM_1(void)
{

      EALLOW;
      CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
      EDIS;

      EPwm1Regs.TBPRD = 1250;       // Set timer period 801 TBCLKs
      EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
      EPwm1Regs.TBCTR = 0x0000;

      // Set Compare values
      EPwm1Regs.CMPA.bit.CMPA = 625;    // Set compare A value
      EPwm1Regs.CMPB.bit.CMPB = 625;    // Set compare B value
/*
      // Setup counter mode
      EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
      EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
      EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
      EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
*/

      EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
      EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
      EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
      EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
      EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
      EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
      EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

      //ePWM High Pulse ePWM_1A
      EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
      EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                       // down count
      //ePWM High Pulse ePWM_1B
      EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM1B on event B, up
      EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;          // Clear PWM1B on event B,
                                                       // down count

      // Code for deadBand
      EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
      EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
      EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;           // load on CTR = Zero
      EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
      EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;

      EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
      EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;

      EPwm1Regs.DBRED.all = 20;
      EPwm1Regs.DBFED.all = 20;


      EALLOW;
      CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
      EDIS;
}
