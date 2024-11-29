/**
 ******************************************************************************
 * File Name          : mot_x.c
 * Description        : This file provides X axis basic movements functions.
 ******************************************************************************
 */

#include <stdio.h>

#include "structs.h"
#include "services.h"

/*-----------------------------------------------------------    Mot X   Start  -------------------------------------*/

enum ErrorCode motXStepTo2(void) {
    //  move to steper X 2
    uint16_t delay_1 = 16, delay_2 = 784;
    set_x_dir(0); //left
    if (!if_x_left_stoper()) {
        move_x(delay_1, delay_2);
    }
    DWT_Delay_us(500);
    return ECOK;
};

enum ErrorCode motXStepTo1(void) {
    uint16_t delay_1 = 16, delay_2 = 784;
    set_x_dir(1); //right
    if (!if_x_right_stoper()) {
        move_x(delay_1, delay_2);
    }
    DWT_Delay_us(500);
    return ECOK;
};

enum ErrorCode motXStp(int32_t x) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 3600, delay_2 = 3600;

    printf("x - %ld\n", x);

    if (x > 0 && x < 5000) {
        set_x_dir(1); //right
        while (!if_x_right_stoper() && x > 0) {
            move_x(delay_1, delay_2);
            x--;
        }
    } else if (x <= 0 && x > -5000) {
        set_x_dir(0); //left
        while (!if_x_left_stoper() && x < 0) {
            move_x(delay_1, delay_2);
            x++;
        }
    } else
        return ECUnknownCommand;
    return ECOK;
}

enum ErrorCode motXSt2(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 160, delay_2 = 784;

    uint16_t ff = 0;
    if (!if_x_left_stoper()) {
        set_x_dir(0); //left
        while (ff < 10) {
            if (if_x_left_stoper() == 1)
                ff++;
            else
                ff = 0;
            move_x(delay_1, delay_2);
        }
    }
    return ECOK;
}

enum ErrorCode motXSt1(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 160, delay_2 = 784;

    uint16_t ff = 0;
    if (!if_x_right_stoper()) {
        set_x_dir(1); //right
        while (ff < 10) {
            if (if_x_right_stoper() == 1)
                ff++;
            else
                ff = 0;
            move_x(delay_1, delay_2);
        }
    }
    return ECOK;
}

enum ErrorCode staXCal(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 160, delay_2 = 784;

    uint16_t ff = 0;
    if (if_x_right_stoper()) {
        set_x_dir(0); //left
        for (int i = 0; i < 800; i++) {
            move_x(delay_1, delay_2);
        }
    }
    DWT_Delay_us(500);
    set_x_dir(1); //right
    while (ff < 10) {
        if (if_x_right_stoper() == 1)
            ff++;
        else
            ff = 0;
        move_x(delay_1, delay_2);
    }
    DWT_Delay_us(500);
    return ECOK;
}

/*-----------------------------------------------------------    Mot X   End  -------------------------------------*/

