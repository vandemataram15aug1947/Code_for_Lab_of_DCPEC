
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "F2837xD_device.h"
#include "F28x_Project.h"
#include "F2837xD_Examples.h"

#include "driverlib.h"
#include "device.h"

#define     EX_ADC_RESOLUTION       12

void gpio_init();
void ConfigADC(uint32_t ADC_BASE);
void initADC_SOC(void);


void PinMux_init();
void initEPWM1();

uint16_t Adc_Result_1,Adc_Result_2;
int ref_i,ref_h,ref_l;
void main(void)



{

    Adc_Result_1=0;
    Adc_Result_2 =0;

    Device_init();
    Device_initGPIO();
    PinMux_init();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    IER = 0x0000;
          IFR = 0x0000;
          SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    ConfigADC(ADCA_BASE);
    initADC_SOC();

    EINT;
    ERTM;

    while(1)
       {

        // Convert, wait for completion, and store results
           ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);




            while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
                {

                }
            ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

            ////           // Store results
              Adc_Result_1= ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
//            Adc_Result_2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);

              initEPWM1();
              DEVICE_DELAY_US(10000);




       }


}


void initEPWM1()
{

        EPwm1Regs.TBPRD = 4000;       // Set timer period 801 TBCLKs
        EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
        EPwm1Regs.TBCTR = 0x0000;
       // Set Compare values
        EPwm1Regs.CMPA.bit.CMPA = Adc_Result_1;    // Set compare A value
      // Setup counter mode
       EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
       EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
       EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
       EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

       EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
      // count
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


void ConfigADC(uint32_t ADC_BASE)
{
    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE=4;  // 200/4 50 MHz
//    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

#if(EX_ADC_RESOLUTION == 12)
    {
        ADC_setMode(ADC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    }
#elif(EX_ADC_RESOLUTION == 16)
    {
      ADC_setMode(ADCA_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
    }
#endif
    ADC_setInterruptPulseMode(ADC_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableConverter(ADC_BASE);
    DEVICE_DELAY_US(1000);
    EDIS;
}



void initADC_SOC(void)
{
#if(EX_ADC_RESOLUTION == 12)
    {
        ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 15);


    }
#elif(EX_ADC_RESOLUTION == 16)
    {
        ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0,64);
    }
#endif
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);


    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);


}



//
// End of File
//
