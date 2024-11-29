/**
 ******************************************************************************
 * File Name          : sensors.c
 * Description        : This file provides sensors processing functions.
 ******************************************************************************
 */
#include "FreeRTOS.h"
#include "semphr.h"
#include "structs.h"

extern Settings Sets;
extern State States;
extern xSemaphoreHandle xMutex;

/*-----------------------------------------------------------    Datchiki   Start
 * -------------------------------------*/

enum ErrorCode datUrWa(void) { return ECOK; }

enum ErrorCode turnOnn(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_Delay(50);
    return ECOK;
}

enum ErrorCode turnOff(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(50);
    return ECOK;
}

enum ErrorCode alrmSta(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

    // States.DatchikUdara=1;
    return ECOK;
}

enum ErrorCode alrmSto(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    // States.DatchikUdara=0;
    return ECOK;
}

// Stop ShockAlarm and reset ShokState
enum ErrorCode datUdar(void) {
    // while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11) ){}
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DoorLock = 1;
    States.DatchikUdara = 0;
    States.DoorAlarm = 0;

    xSemaphoreGive(xMutex);
    alrmSto();

    return ECOK;
}

// doorAlarm   1-door open? 0 - door close
enum ErrorCode dorLClo(void) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DoorLock = 1;
    xSemaphoreGive(xMutex);
    return ECOK;
}

// open zamok dveri
enum ErrorCode dorLOpe(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DoorLock = 0;

    xSemaphoreGive(xMutex);
    HAL_Delay(1000);  // DOOR_LOCK_DELAY 9000
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
    // if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)==1 && States.DoorLock==0)
    // HAL_Delay(3000);
    return ECOK;
}

enum ErrorCode resetStateFlags(void) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DoorLock = 1;
    States.DatchikUdara = 0;
    States.DoorAlarm = 0;
    xSemaphoreGive(xMutex);

    return ECOK;
}

/*-----------------------------------------------------------    Datchiki   End  -------------------------------------*/
