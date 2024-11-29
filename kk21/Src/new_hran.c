/**
 ******************************************************************************
 * File Name          : new_hran.c
 * Description        : This file provides storage movements functions.
 ******************************************************************************
 */
#include "structs.h"

extern Settings Sets;

/*------------------------ NEW HRAN--------------------------------    */
enum ErrorCode revolvCalibration(void) {
    // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) != 1) return ECRevNoTube;
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
    uint32_t stops = 0;
    int allstp = 0;
    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 1) {
        while (allstp <= 500) {
            DWT_Delay_us(1250);
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
            DWT_Delay_us(1250);
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
            allstp++;
        }
    }
    allstp = 0;
    while (stops <= Sets.rev_max_stp_calibration) {
        DWT_Delay_us(1250);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
        DWT_Delay_us(1250);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 1)
            stops++;
        else
            stops = 0;
        if (allstp++ > 10000) return ECTimeout;
    }

    return ECOK;
}

enum ErrorCode revolvZOpen(void) {
    // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) != 1) return ECRevNoTube;
    uint8_t stops = 0;
    int st = 0;
    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) != 1) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
        while (stops <= 15) {
            DWT_Delay_us(400);
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
            DWT_Delay_us(400);
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
            if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 1)
                stops++;
            else
                stops = 0;
            if (st++ > 5000) return ECTimeout;
        }
    }
    return ECOK;
}

enum ErrorCode revolvZClose(void) {
    // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) != 1) return ECRevNoTube;
    uint8_t stops = 0;
    int st = 0;
    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) != 1) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
        while (stops <= 10) {
            DWT_Delay_us(400);
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
            DWT_Delay_us(400);
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
            if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == 1)
                stops++;
            else
                stops = 0;
            if (st++ > 5000) return ECTimeout;
        }
    }
    return ECOK;
}

enum ErrorCode revolvZStp(int a) {
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
    int stops = 0;

    while (stops <= a * 160) {
        DWT_Delay_us(1250);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
        DWT_Delay_us(1250);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
        stops++;
        /*	if (allstp++ >10000)return ECTimeout ;*/
    }
    return ECOK;
}

enum ErrorCode revolvCheckCartridge(void) { return ECOK; }

/*---------------------------------------------------- END NEW HRAN
 * ------------------------------------------------------------    */
