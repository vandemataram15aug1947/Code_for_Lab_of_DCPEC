
// Included Files
#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"
//#include "board.h"
#include "math.h"

// Defines
#define EPWM1_TIMER_TBPRD  1500U // Period register


#define EPWM2_TIMER_TBPRD  1500U // Period register


#define EPWM3_TIMER_TBPRD  1500U // Period register


#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U


// Function Prototypes
void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);


// Main Loop
void main(void)
{
    // Initialize device clock and peripherals
    Device_init();

    // Disable pin locks and enable internal pull ups.
    Device_initGPIO();

    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    Interrupt_initVectorTable();

    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    //Board_init();

    // Configure GPIO0/1, GPIO2/3, and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and ePWM3A/3B respectively
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2A);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_EPWM2B);

    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3B);

    GPIO_setPadConfig(35, GPIO_PIN_TYPE_PULLUP);
    GPIO_writePin(35, 1);
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setDirectionMode(35, GPIO_DIR_MODE_OUT);


    // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initEPWM1();
    initEPWM2();
    initEPWM3();

    // Enable sync and clock to PWM
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // Enable Global Interrupt (INTM) and real-time interrupt (DBGM)
    EINT; // Enable Global interrupt INTM
    ERTM; // Enable Global real-time interrupt DBGM

    // IDLE loop. Just sit and loop forever (optional):
    for(;;)
    {
        NOP;
    }
}

// Initialize initEPWM1-Configure ePWM1
void initEPWM1()
{
    // Set-Up TBCLK
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    // Set Compare Values
    EPWM_setCounterCompareValue(EPWM1_BASE,
                                EPWM_COUNTER_COMPARE_A,
                                750);
    EPWM_setCounterCompareValue(EPWM1_BASE,
                                EPWM_COUNTER_COMPARE_B,
                                750);

    // Set-Up Counter Mode
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    // Set-Up Shadowing
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    // Set Actions Qualifier
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  //EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

}


// Initialize initEPWM2-Configure ePWM2
void initEPWM2()
{

    // Set-Up TBCLK
    EPWM_setTimeBasePeriod(EPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM2_BASE, EPWM2_TIMER_TBPRD/6);
    EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);

    // Set Compare Values
    EPWM_setCounterCompareValue(EPWM2_BASE,
                                EPWM_COUNTER_COMPARE_A,
                                750);
    EPWM_setCounterCompareValue(EPWM2_BASE,
                                EPWM_COUNTER_COMPARE_B,
                                750);

    // Set-Up Counter Mode
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_enablePhaseShiftLoad(EPWM2_BASE);
    EPWM_setClockPrescaler(EPWM2_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    // Set-Up Shadowing
    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    // Set Actions Qualifier
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

}


// Initialize initEPWM3-Configure ePWM3
void initEPWM3(void)
{

    // Set-Up TBCLK
    EPWM_setTimeBasePeriod(EPWM3_BASE, EPWM3_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM3_BASE, EPWM2_TIMER_TBPRD/1.2);
    EPWM_setTimeBaseCounter(EPWM3_BASE, 0U);

    // Set Compare Values
    EPWM_setCounterCompareValue(EPWM3_BASE,
                                EPWM_COUNTER_COMPARE_A,
                               750);
    EPWM_setCounterCompareValue(EPWM3_BASE,
                                EPWM_COUNTER_COMPARE_B,
                               750);

   // Set-Up Counter Mode
   EPWM_setTimeBaseCounterMode(EPWM3_BASE, EPWM_COUNTER_MODE_UP_DOWN);
   EPWM_enablePhaseShiftLoad(EPWM3_BASE);
   EPWM_setClockPrescaler(EPWM3_BASE,
                          EPWM_CLOCK_DIVIDER_1,
                          EPWM_HSCLOCK_DIVIDER_1);

   // Set-Up Shadowing
   EPWM_setCounterCompareShadowLoadMode(EPWM3_BASE,
                                        EPWM_COUNTER_COMPARE_A,
                                        EPWM_COMP_LOAD_ON_CNTR_ZERO);
   EPWM_setCounterCompareShadowLoadMode(EPWM3_BASE,
                                        EPWM_COUNTER_COMPARE_B,
                                        EPWM_COMP_LOAD_ON_CNTR_ZERO);

   // Set Actions Qualifier
   EPWM_setActionQualifierAction(EPWM3_BASE,
                                 EPWM_AQ_OUTPUT_A,
                                 EPWM_AQ_OUTPUT_HIGH,
                                 EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
   EPWM_setActionQualifierAction(EPWM3_BASE,
                                 EPWM_AQ_OUTPUT_A,
                                 EPWM_AQ_OUTPUT_LOW,
                                 EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
   EPWM_setActionQualifierAction(EPWM3_BASE,
                                 EPWM_AQ_OUTPUT_B,
                                 EPWM_AQ_OUTPUT_LOW,
                                 EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
   EPWM_setActionQualifierAction(EPWM3_BASE,
                                 EPWM_AQ_OUTPUT_B,
                                 EPWM_AQ_OUTPUT_HIGH,
                                 EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

}
