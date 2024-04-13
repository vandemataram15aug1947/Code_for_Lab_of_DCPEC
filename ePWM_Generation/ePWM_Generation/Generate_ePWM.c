
#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "driverlib.h"
#include "device.h"
//
// Function Prototypes
//
void initEPWM1(void);
void PinMux_init();

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

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
//    Interrupt_register(INT_EPWM1_TZ, &epwm1TZISR);


    //
    // Configure ePWM1, ePWM2, and TZ GPIOs
    //
    PinMux_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize ePWM1 and ePWM2
    //
    initEPWM1();


    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
//    for(;;)

    while(1){
//        NOP;
    }
}

//
// initEPWM1 - Configure ePWM1
//
void initEPWM1()
{

        EPwm1Regs.TBPRD = 625;       // Set timer period 801 TBCLKs
        EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
        EPwm1Regs.TBCTR = 0x0000;

        // Set Compare values
        EPwm1Regs.CMPA.bit.CMPA = 1000;    // Set compare A value

        // Setup counter mode
       EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
       EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
       EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
       EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

       EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
      // Count
       EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                     // down count



}


void PinMux_init()
{
    EALLOW;
    //EPWM1 -> myEPWM1 Pinmux
    GpioCtrlRegs.GPAMUX1.all=0;// gpio 15 to gpio 0 a;; general purpouse I/O
    GpioCtrlRegs.GPAMUX1.bit.GPIO0=1;// epwm active
    EDIS;

}

