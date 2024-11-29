/**
 ******************************************************************************
 * File Name          : outlet.c
 * Description        : This file provides outlet movements functions.
 ******************************************************************************
 */
#include "structs.h"

extern Settings Sets;

/*-----------------------------------------------------------    Mot Vidacha Start
 * -------------------------------------*/
enum ErrorCode VidachaSolenoidUpperOpen(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    return ECOK;
}

enum ErrorCode VidachaSolenoidLowerOpen(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
    return ECOK;
}

enum ErrorCode VidachaSolenoidUpperClose(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    return ECOK;
}

enum ErrorCode VidachaSolenoidLowerClose(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
    return ECOK;
}

// open output window esli stopik zajat
enum ErrorCode viBOpen(void) {
    uint16_t i = 0;

    if (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15)) viBClos();
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
        for (; i < Sets.viBOpenMotorStp; i++) {  // OUTPUT_OPEN_STEPS 2200

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
            DWT_Delay_us(700);  // OUTPUT_OPEN_DELAY_STEPS 700
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
            DWT_Delay_us(700);  // OUTPUT_OPEN_DELAY_STEPS
        }
    }  // else return ECInvalidArg;
    return ECOK;
}

// zakritb okno vidachi.  Idem do 2250, ecli za eti shagi ne doshli do stopika, znachi cho-to zajali i nado otkritsya
// chobi ne zajat' ruku klietnta
enum ErrorCode viBClos(void) {
    uint8_t tt = 0;  // not use
    uint16_t st = 0;
    if (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15)) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
        while (tt < 10) {
            if (++st > Sets.viBClosMotorStp) {  // OUTPUT_CLOSE_STEPS 2250
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                for (uint16_t i = 0; i < 800; i++) {  // OUTPUT_CLOSE_ALARM_STEPS    800
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
                    DWT_Delay_us(700);  // OUTPUT_CLOSE_DELAY_STEPS  700
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
                    DWT_Delay_us(700);  // OUTPUT_CLOSE_DELAY_STEPS
                }
                return ECViBCloseFault;
            }
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
            DWT_Delay_us(700);  // OUTPUT_CLOSE_DELAY_STEPS
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
            DWT_Delay_us(700);  // OUTPUT_CLOSE_DELAY_STEPS
            if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15))
                tt++;
            else
                tt = 0;
        }
    }
    return ECOK;
}

enum ErrorCode viDClos(void) {
    uint16_t i = 0;  // OUTPUT_LOST_STEPS
    VidachaSolenoidUpperOpen();
    VidachaSolenoidLowerOpen();

    HAL_Delay(10);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);  // or
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);    // or
    for (; i < Sets.viDCloseMotorStp; i++) {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);  // or
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);  // or
        HAL_Delay(1);
    }
    VidachaSolenoidUpperClose();
    VidachaSolenoidLowerClose();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);  // or
    return ECOK;
}

// sbros zabitih izdelij iz okna vidachi
enum ErrorCode viDOpen(void) {
    uint16_t i = 0;  // OUTPUT_LOST_STEPS
    VidachaSolenoidUpperOpen();
    VidachaSolenoidLowerOpen();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);  // or
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);  // or
    for (; i < Sets.viDOpenMotorStp; i++) {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);  // or
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);  // or
        HAL_Delay(1);
    }
    VidachaSolenoidUpperClose();
    VidachaSolenoidLowerClose();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);  // or
    return ECOK;
}

enum ErrorCode viDClosNew(void) {
    uint16_t i = 0;  // OUTPUT_LOST_STEPS
    //	VidachaSolenoidUpperOpen();
    //			VidachaSolenoidLowerOpen();

    HAL_Delay(10);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);  // or
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);    // or
    for (; i < Sets.viDCloseMotorStp; i++) {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);  // or
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);  // or
        HAL_Delay(1);
    }
    // VidachaSolenoidUpperClose();
    //	VidachaSolenoidLowerClose();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);  // or
    return ECOK;
}

// sbros zabitih izdelij iz okna vidachi
enum ErrorCode viDOpenNew(void) {
    uint16_t i = 0;                                         // OUTPUT_LOST_STEPS
    // VidachaSolenoidUpperOpen();
    // VidachaSolenoidLowerOpen();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);  // or
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);  // or
    for (; i < Sets.viDOpenMotorStp; i++) {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);  // or
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);  // or
        HAL_Delay(1);
    }                                                     // VidachaSolenoidUpperClose();
    //	VidachaSolenoidLowerClose();
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);  // or
    return ECOK;
}
/*-----------------------------------------------------------    Mot Vidacha   End
 * -------------------------------------*/
