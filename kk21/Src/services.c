/**
******************************************************************************
* File Name          : services.c
* Description        : This file provides service functions.
******************************************************************************
*/

#include "structs.h"

extern Settings Sets;


/*------------------------------------- Services ---------------------------------------------*/


enum ErrorCode resetSTM(void) {
    HAL_NVIC_SystemReset();
    return ECOK;
}

void move_king(uint32_t delay_1, uint32_t delay_2) {
    DWT_Delay_us(delay_1);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_SET);
    DWT_Delay_us(delay_2);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_RESET);
}

void move_water(uint32_t delay_1, uint32_t delay_2) {
    DWT_Delay_us(delay_1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    DWT_Delay_us(delay_2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
}

void move_pawn(uint32_t delay_1, uint32_t delay_2) {
    DWT_Delay_us(delay_1);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
    DWT_Delay_us(delay_2);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
}

void move_x(uint32_t delay_1, uint32_t delay_2) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    DWT_Delay_us(delay_1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    DWT_Delay_us(delay_2);
}

void move_y(uint32_t delay_1, uint32_t delay_2) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
    DWT_Delay_us(delay_1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
    DWT_Delay_us(delay_2);
}

void set_king_dir(_Bool dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET);  // left
    } else {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);  // right
    }
}

void set_water_dir(_Bool dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  // up
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  // down
    }
}

void set_pawn_dir(_Bool dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);  // CCW
    } else {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);  // CW
    }
}

void set_x_dir(_Bool dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET); //left 2 st
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); //right 1 st
    }
}

void set_y_dir(_Bool dir) {
    if (dir == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); //down 2 st
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); //up 1 st
    }
}

GPIO_PinState HAL_GPIO_ReadPinDebounced(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_PinState pin_state = GPIO_PIN_RESET;
    uint8_t count = 0;

    // Debounce settings
    uint16_t debounce_time = 10;  // in milliseconds
    uint16_t debounce_count = 3;  // number of consecutive reads required to confirm state

    do {
        pin_state = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
        count++;
        HAL_Delay(debounce_time);
    } while (count < debounce_count && pin_state != HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));

    return pin_state;
}

GPIO_PinState if_king_left_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
}

GPIO_PinState if_king_right_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
}

GPIO_PinState if_water_up_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);
}

GPIO_PinState if_water_down_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
}

GPIO_PinState if_king_left_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOE, GPIO_PIN_1);
}

GPIO_PinState if_king_right_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOE, GPIO_PIN_7);
}

GPIO_PinState if_water_up_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOD, GPIO_PIN_7);
}

GPIO_PinState if_water_down_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOD, GPIO_PIN_8);
}

GPIO_PinState if_pawn_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
}

GPIO_PinState if_pawn_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOE, GPIO_PIN_5);
}

GPIO_PinState if_x_left_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
}

GPIO_PinState  if_x_left_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOA, GPIO_PIN_6);
}

GPIO_PinState if_x_right_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
}

GPIO_PinState if_x_right_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOB, GPIO_PIN_5);
}

GPIO_PinState if_y_up_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
}

GPIO_PinState if_y_up_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOB, GPIO_PIN_15);
}

GPIO_PinState if_y_down_stoper(void) {
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
}

GPIO_PinState if_y_down_stoper_Db(void) {
    return HAL_GPIO_ReadPinDebounced(GPIOE, GPIO_PIN_9);
}

enum ErrorCode check_stops(void) {
    if (if_x_right_stoper_Db() && if_x_left_stoper_Db()) return ECxStoperFault;

    if (if_y_up_stoper_Db() && if_y_down_stoper_Db()) return ECyStoperFault;

    if (if_water_down_stoper_Db() && if_water_up_stoper_Db()) return ECWaterStoperFault;

    if (if_king_left_stoper_Db() && if_king_right_stoper_Db()) {
        return ECHandAlarmStoper;
    }

    return ECOK;
}


