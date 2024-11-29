/**
 ******************************************************************************
 * File Name          : mot_y.c
 * Description        : This file provides Y axis basic movements functions.
 ******************************************************************************
 */

#include <stdio.h>
#include "structs.h"
#include "services.h"


extern Settings Sets;

/*-----------------------------------------------------------    Mot Y   Start  -------------------------------------*/

enum ErrorCode motYStepTo2(void) {
    uint16_t delay_1 = 16, delay_2 = 784;
    //  move to steper Y 2
    set_y_dir(0);
    if (!if_y_down_stoper()) {
        move_y(delay_1, delay_2);
    } else
        return ECUnknownCommand;
    DWT_Delay_us(100);
    return ECOK;
};

enum ErrorCode motYStepTo1(void) {
    uint16_t delay_1 = 16, delay_2 = 784;
    //  move to steper Y 1
    set_y_dir(1);
    if (!if_y_up_stoper()) {
        move_y(delay_1, delay_2);
    } else
        return ECUnknownCommand;
    DWT_Delay_us(100);
    return ECOK;
};

enum ErrorCode motYStp(int32_t x) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    printf("y -%ld\n", x);
    if (x > 0 && x < 5000) {
        set_y_dir(0);
        while (x > 0) {
            move_y(Sets.y_find_spd, Sets.y_find_spd);
            x--;
        }
    } else if (x <= 0 && x > -5000) {
        set_y_dir(1);
        while (x < 0) {
            move_y(Sets.y_find_spd, Sets.y_find_spd);
            x++;
        }
    } else
        return ECUnknownCommand;
    return ECOK;
}

enum ErrorCode motYSt2(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 16, delay_2 = 784;
    if (!if_y_down_stoper_Db()) {
        set_y_dir(0);
        uint16_t ff = 0;
        while (ff < 10) {
            if (if_y_down_stoper())
                ff++;
            else
                ff = 0;
            move_y(delay_1, delay_2);
        }
    }
    return ECOK;
}

enum ErrorCode motYSt1(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 16, delay_2 = 784;
    if (!if_y_up_stoper_Db()) {
        set_y_dir(1);
        uint16_t ff = 0;
        while (ff < 10) {
            if (if_y_up_stoper())
                ff++;
            else
                ff = 0;
            move_y(delay_1, delay_2);
        }
    }
    return ECOK;
}

enum ErrorCode staYCal(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t ff = 0;
    uint32_t co = 0;
    uint16_t delay_1 = 500, delay_2 = 500;
    if (if_y_down_stoper_Db()) {
        set_y_dir(1);
        for (int i = 0; i < 800; i++) {
            move_y(delay_1, delay_2);
        }
    }
    DWT_Delay_us(500);
    set_y_dir(0);

    while (ff < 10) {
        if (if_y_down_stoper())
            ff++;
        else
            ff = 0;
        move_y(delay_1, delay_2);
        co++;
        if (co > Sets.mot_y_from_priemka_to_spectr_max_steps) return ECTimeout;
    }
    DWT_Delay_us(500);
    return ECOK;
}

enum ErrorCode motYFastSpeedFrom2To1(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint32_t co = 0;
    uint16_t spdY = 500;
    if (if_y_up_stoper_Db()) {
        set_y_dir(0);
        while (!if_y_up_stoper() && co < 15600) {
            move_y(spdY, spdY);
            if (spdY <= 1000 && spdY > 120 && co % 50 == 0 && co < 8500) spdY -= 2;
            if (co > 13500 && spdY < 1000 && co % 25 == 0) spdY += 4;
            co++;
        }
    }
    return ECOK;
}

/*-----------------------------------------------------------    Mot Y   End  -------------------------------------*/
