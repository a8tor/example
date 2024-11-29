/**
 ******************************************************************************
 * File Name          : mpu.c
 * Description        : This file provides initialization code for mpu6050.
 ******************************************************************************
 */
#include "mpu.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "structs.h"

extern Settings Sets;
extern State States;
extern I2C_HandleTypeDef hi2c1;
extern xSemaphoreHandle xMutex;

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;
int16_t Temp_RAW = 0;

float Ax, Ay, Az, Gx, Gy, Gz, Temp;

/*---------------------------------------------------------------Gyroscope-------------------------------------------*/

void MPU6050_Init(void) {
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, 1000);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
        printf("\n-Start MPU6050_Init -\n");

    } else
        printf("\n-False MPU6050_Init - %d\n", check);
}

void MPU6050_Read_Accel(void) {
    uint8_t Rec_Data[6];
    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

    Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DatchikNaklonaX = Accel_X_RAW / 16384.0;
    States.DatchikNaklonaY = Accel_Y_RAW / 16384.0;
    States.DatchikNaklonaZ = Accel_Z_RAW / 16384.0;
    xSemaphoreGive(xMutex);
}

void MPU6050_Read_Gyro(void) {
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

    Gyro_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    Gyro_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DatchikGPRSX = Gyro_X_RAW / 131.0;
    States.DatchikGPRSY = Gyro_Y_RAW / 131.0;
    States.DatchikGPRSZ = Gyro_Z_RAW / 131.0;
    xSemaphoreGive(xMutex);
}

void MPU6050_Read_Temp(void) {
    uint8_t Rec_Data[2];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 2, 1000);

    Temp_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/
    xSemaphoreTake(xMutex, portMAX_DELAY);
    States.DatchikTemperaturi = Temp_RAW / 340 + 36.53;
    xSemaphoreGive(xMutex);
}
