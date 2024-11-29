#include "dwt_stm32_delay.h"

/**
 * @brief  Initializes DWT_Clock_Cycle_Count for DWT_Delay_us function
 * @return Error DWT counter
 *         1: clock cycle counter not started
 *         0: clock cycle counter works
 */

uint32_t DWT_Delay_Init(void) {
    volatile unsigned int *DWT_CYCCNT = (volatile unsigned int *) 0xE0001004;   // address of the register
    volatile unsigned int *DWT_CONTROL = (volatile unsigned int *) 0xE0001000;  // address of the register
    volatile unsigned int *DWT_LAR = (volatile unsigned int *) 0xE0001FB0;      // address of the register
    volatile unsigned int *SCB_DEMCR = (volatile unsigned int *) 0xE000EDFC;    // address of the register

    *SCB_DEMCR |= 0x01000000;
    *DWT_LAR = 0xC5ACCE55;  // enable access
    *DWT_CYCCNT = 0;        // reset the counter
    *DWT_CONTROL |= 1;      // enable the counter

    /*

      CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;

      CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

     DWT->LAR = 0xC5ACCE55;

        DWT->CYCCNT = 0;



      DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;

      DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;


      DWT->CYCCNT = 0;


         __ASM volatile ("NOP");
         __ASM volatile ("NOP");
      __ASM volatile ("NOP");
    */
    /* Check if clock cycle counter has started */
    if (DWT->CYCCNT) {
        return 0; /*clock cycle counter started*/
    } else {
        return 1; /*clock cycle counter not started*/
    }
}

/* Use DWT_Delay_Init (); and DWT_Delay_us (microseconds) in the main */
