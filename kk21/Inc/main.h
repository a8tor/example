/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>

#include "dwt_stm32_delay.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_TIM3_Init(void);

static void MX_TIM4_Init(void);

static void MX_ADC2_Init(void);

static void MX_ADC3_Init(void);

static void MX_I2C1_Init(void);

static void MX_ADC1_Init(void);

void StartDefaultTask(void const *argument);

void StartNetTask(void const *argument);

void StartStateTask(void const *argument);

void StartSendTask(void const *argument);

void StartShockTask(void const *argument);

void StartDoorAlarm(void const *argument);

GPIO_PinState HAL_GPIO_ReadPinDebounced(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KMCaret_ES_Pin GPIO_PIN_6
#define KMCaret_ES_GPIO_Port GPIOE
#define PriemkaADC_Potenciometr_Pin GPIO_PIN_3
#define PriemkaADC_Potenciometr_GPIO_Port GPIOF
#define NOT_USE_Pin GPIO_PIN_4
#define NOT_USE_GPIO_Port GPIOF
#define NOT_USEF5_Pin GPIO_PIN_5
#define NOT_USEF5_GPIO_Port GPIOF
#define Datchik_WaterLevel111_Pin GPIO_PIN_6
#define Datchik_WaterLevel111_GPIO_Port GPIOF
#define Datchik_WaterLevel1_Pin GPIO_PIN_7
#define Datchik_WaterLevel1_GPIO_Port GPIOF
#define NOT_USEC0_Pin GPIO_PIN_0
#define NOT_USEC0_GPIO_Port GPIOC
#define NOT_USEC2_Pin GPIO_PIN_2
#define NOT_USEC2_GPIO_Port GPIOC
#define NOT_USEC3_Pin GPIO_PIN_3
#define NOT_USEC3_GPIO_Port GPIOC
#define NOT_USEA3_Pin GPIO_PIN_3
#define NOT_USEA3_GPIO_Port GPIOA
#define DatchikZadblmleniya_Pin GPIO_PIN_5
#define DatchikZadblmleniya_GPIO_Port GPIOA
#define EndStopX2_Pin GPIO_PIN_6
#define EndStopX2_GPIO_Port GPIOA
#define PriemkaTimer_Pin GPIO_PIN_1
#define PriemkaTimer_GPIO_Port GPIOB
#define Gerkon_Pin GPIO_PIN_2
#define Gerkon_GPIO_Port GPIOB
#define LEDS_LIGHT_Pin GPIO_PIN_12
#define LEDS_LIGHT_GPIO_Port GPIOF
#define motKing2Stp_Pin GPIO_PIN_13
#define motKing2Stp_GPIO_Port GPIOF
#define motKing2Dir_Pin GPIO_PIN_14
#define motKing2Dir_GPIO_Port GPIOF
#define motKing3Stp_Pin GPIO_PIN_15
#define motKing3Stp_GPIO_Port GPIOF
#define motKing3Dir_Pin GPIO_PIN_0
#define motKing3Dir_GPIO_Port GPIOG
#define KM_ES5_Pin GPIO_PIN_7
#define KM_ES5_GPIO_Port GPIOE
#define NOT_USEE8_Pin GPIO_PIN_8
#define NOT_USEE8_GPIO_Port GPIOE
#define EndStopY2_Pin GPIO_PIN_9
#define EndStopY2_GPIO_Port GPIOE
#define PompaUp_Pin GPIO_PIN_10
#define PompaUp_GPIO_Port GPIOE
#define BotOutPutMotorStp1_Pin GPIO_PIN_11
#define BotOutPutMotorStp1_GPIO_Port GPIOE
#define BotOutPutMotorStp2_Pin GPIO_PIN_12
#define BotOutPutMotorStp2_GPIO_Port GPIOE
#define BotOutPutMotorStp3_Pin GPIO_PIN_13
#define BotOutPutMotorStp3_GPIO_Port GPIOE
#define BotOutPutMotorStp4_Pin GPIO_PIN_14
#define BotOutPutMotorStp4_GPIO_Port GPIOE
#define EndStopBotOutPut_Pin GPIO_PIN_15
#define EndStopBotOutPut_GPIO_Port GPIOE
#define VidachaStp_Pin GPIO_PIN_10
#define VidachaStp_GPIO_Port GPIOB
#define VidachaDir_Pin GPIO_PIN_12
#define VidachaDir_GPIO_Port GPIOB
#define EndStopY1_Pin GPIO_PIN_15
#define EndStopY1_GPIO_Port GPIOB
#define EndStopZ1_Pin GPIO_PIN_8
#define EndStopZ1_GPIO_Port GPIOD
#define PompaDown_Pin GPIO_PIN_10
#define PompaDown_GPIO_Port GPIOD
#define DatchikiUdara_Pin GPIO_PIN_11
#define DatchikiUdara_GPIO_Port GPIOD
#define Servo_karetka_SysPos_Pin GPIO_PIN_12
#define Servo_karetka_SysPos_GPIO_Port GPIOD
#define ServoDryDrop_Pin GPIO_PIN_13
#define ServoDryDrop_GPIO_Port GPIOD
#define Servo_Ramp_drop_Pin GPIO_PIN_14
#define Servo_Ramp_drop_GPIO_Port GPIOD
#define Servo_Water_Drop_Pin GPIO_PIN_15
#define Servo_Water_Drop_GPIO_Port GPIOD
#define motKing1Dir_Pin GPIO_PIN_2
#define motKing1Dir_GPIO_Port GPIOG
#define motKing1Stp_Pin GPIO_PIN_3
#define motKing1Stp_GPIO_Port GPIOG
#define motKingYDir_Pin GPIO_PIN_4
#define motKingYDir_GPIO_Port GPIOG
#define motKingYStp_Pin GPIO_PIN_5
#define motKingYStp_GPIO_Port GPIOG
#define motKing4Dir_Pin GPIO_PIN_6
#define motKing4Dir_GPIO_Port GPIOG
#define motKing4Stp_Pin GPIO_PIN_7
#define motKing4Stp_GPIO_Port GPIOG
#define PriemkaSolenoid_Pin GPIO_PIN_8
#define PriemkaSolenoid_GPIO_Port GPIOG
#define DatchikPiliDigitLed_Pin GPIO_PIN_6
#define DatchikPiliDigitLed_GPIO_Port GPIOC
#define motZDir_Pin GPIO_PIN_7
#define motZDir_GPIO_Port GPIOC
#define motXDir_Pin GPIO_PIN_8
#define motXDir_GPIO_Port GPIOC
#define ScaleOnOff_Pin GPIO_PIN_9
#define ScaleOnOff_GPIO_Port GPIOC
#define NOT_USEA8_Pin GPIO_PIN_8
#define NOT_USEA8_GPIO_Port GPIOA
#define motZStp_Pin GPIO_PIN_9
#define motZStp_GPIO_Port GPIOA
#define DoorLock_Pin GPIO_PIN_10
#define DoorLock_GPIO_Port GPIOA
#define VidachaSolenoidLower1_Pin GPIO_PIN_11
#define VidachaSolenoidLower1_GPIO_Port GPIOA
#define VidachaSolenoidUpper_Pin GPIO_PIN_12
#define VidachaSolenoidUpper_GPIO_Port GPIOA
#define motYDir_Pin GPIO_PIN_10
#define motYDir_GPIO_Port GPIOC
#define motYStp_Pin GPIO_PIN_11
#define motYStp_GPIO_Port GPIOC
#define KukaControlPin_Pin GPIO_PIN_1
#define KukaControlPin_GPIO_Port GPIOD
#define NOT_USED3_Pin GPIO_PIN_3
#define NOT_USED3_GPIO_Port GPIOD
#define NOT_USED4_Pin GPIO_PIN_4
#define NOT_USED4_GPIO_Port GPIOD
#define motorsControlPin_Pin GPIO_PIN_5
#define motorsControlPin_GPIO_Port GPIOD
#define EndStopZ2_Pin GPIO_PIN_7
#define EndStopZ2_GPIO_Port GPIOD
#define Alarma_Pin GPIO_PIN_4
#define Alarma_GPIO_Port GPIOB
#define EndStopX1_Pin GPIO_PIN_5
#define EndStopX1_GPIO_Port GPIOB
#define motXStp_Pin GPIO_PIN_8
#define motXStp_GPIO_Port GPIOB
#define Datchik_WaterLevel2_Pin GPIO_PIN_9
#define Datchik_WaterLevel2_GPIO_Port GPIOB
#define DoorIn_Pin GPIO_PIN_1
#define DoorIn_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
