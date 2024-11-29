/**
 ******************************************************************************
 * File Name          : water.c
 * Description        : This file provides water pomp control functions.
 ******************************************************************************
 */
#include "structs.h"

extern Settings Sets;
extern volatile _Bool waterAlarm;

/*-----------------------------------------------------------    Water   Start  -------------------------------------*/

// Stop pump water
enum ErrorCode pomUSto(void) {
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_Delay(100);
    waterAlarm = 1;
    return ECOK;
}

// Start pump water
enum ErrorCode pomUSta(void) {
    uint16_t time = 0;  // WATER_PUMPUP_DELAY
    uint8_t count = 0;

    waterAlarm = 0;
    HAL_Delay(100);
    if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6)) {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
        while (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6) && count < 7) {
            while (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6) && time++ < Sets.timeToPompUpWater) {
                HAL_Delay(1);
            }  // 15 sec
            count++;
            time = 0;
        }
        HAL_Delay(3);
        pomUSto();
        HAL_Delay(100);
        waterAlarm = 1;
        if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6) && count <= 7) return ECNoWaterSensor;
    }
    return ECOK;
}

// stop to flush water
enum ErrorCode pomDSto(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_Delay(100);
    waterAlarm = 1;
    return ECOK;
}

// start to flush water
enum ErrorCode pomDSta(void) {
    waterAlarm = 0;
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_Delay(Sets.timeToFlushWater);  ///  WATER_FLUSH_DELAY
    pomDSto();

    return ECOK;
}

/*-----------------------------------------------    Water   End  -------------------------------------*/
