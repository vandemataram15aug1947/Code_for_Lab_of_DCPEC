#include "F28x_Project.h"
// Function Prototypes
void ConfigureADC(void);
void ConfigureEPWM(void);
void SetupADCEpwm(Uint16 channel);
interrupt void adca1_isr(void);
Uint16 ADCvalue;
void main(void)
{
 InitSysCtrl();
 DINT;
 InitPieCtrl();
 IER = 0x0000;
 IFR = 0x0000;
 InitPieVectTable();
//
// Map ISR functions
//
 EALLOW;
 PieVectTable.ADCA1_INT = &adca1_isr; //function for ADCA interrupt 1
 EDIS;
//
// Configure the ADC and power it up
//
 ConfigureADC();
//
// Configure the ePWM
//
 ConfigureEPWM();
//
// Setup the ADC for ePWM triggered conversions on channel 0
//
 SetupADCEpwm(0);
// Enable global Interrupts and higher priority real-time debug events:
//
 IER |= M_INT1; //Enable group 1 interrupts
 EINT; // Enable Global interrupt INTM
//
// enable PIE interrupt
//
 PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
//
// sync ePWM
//
 EALLOW;
 CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
 EPwm1Regs.ETSEL.bit.SOCAEN = 1; //enable SOCA
 EPwm1Regs.TBCTL.bit.CTRMODE = 0;
//
//take conversions indefinitely in loop
//
 while(1)
{
}
}
//
// ConfigureADC - Write ADC configurations and power up the ADC for both
// ADC A and ADC B
//
void ConfigureADC(void)
{
 EALLOW;
 //
 //write configurations
 //
 AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
 AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
 //
 //power up the ADC
 //
 AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
 //
 //delay for 1ms to allow ADC time to power up
 //
 DELAY_US(1000);
 EDIS;
}
//
// ConfigureEPWM - Configure EPWM SOC and compare values
//
void ConfigureEPWM(void)
{
 EALLOW;
 // Assumes ePWM clock is already enabled
 EPwm1Regs.ETSEL.bit.SOCASEL = 1; // Select SOC on up-count
 EPwm1Regs.ETPS.bit.SOCAPRD = 1; // Generate pulse on 1st event
 EPwm1Regs.CMPA.bit.CMPA = 0x0800; // Set compare A value to 2048 counts
 EPwm1Regs.TBPRD = 0x1000; // Set period to 4096 counts
 EDIS;
}
//
// SetupADCEpwm - Setup ADC EPWM acquisition window
//
void SetupADCEpwm(Uint16 channel)
{
 Uint16 acqps;
 //
 // Determine minimum acquisition window (in SYSCLKS) based on resolution
 //
 if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
 {
 acqps = 14; //75ns
 }
 else //resolution is 16-bit
 {
 acqps = 63; //320ns
 }
 //
 //Select the channels to convert and end of conversion flag
 //
 EALLOW;
 AdcaRegs.ADCSOC0CTL.bit.CHSEL = channel; //SOC0 will convert pin A0
 AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
 AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
 AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; //end of SOC0 will set INT1 flag
 AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1; //enable INT1 flag
 AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
 EDIS;
}
// adca1_isr - Read ADC Buffer in ISR
//
interrupt void adca1_isr(void)
{
 ADCvalue = AdcaResultRegs.ADCRESULT0;
 AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
 // Check if overflow has occurred

 if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
 {
 AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
 AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
 }
 PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
