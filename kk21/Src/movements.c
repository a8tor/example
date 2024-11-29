/**
 ******************************************************************************
 * File Name          : movements.c
 * Description        : This file provides modular carriage movement functions.
 ******************************************************************************
 */

#include "mot_x.h"
#include "mot_y.h"
#include "structs.h"
#include "services.h"

extern Settings Sets;

/*--------------------------------------------------Movements---------------------------------------------*/
// lights on
enum ErrorCode ledsOn(void) {
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET);
    return ECOK;
}

// lights off
enum ErrorCode ledsOff(void) {
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
    return ECOK;
}

enum ErrorCode fVeToSp(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;
    // X to vesi
    motXSt1();
    HAL_Delay(100);
    // Y to vesi
    uint32_t co = 0, ff = 0;
    uint16_t spdY = 700;

    set_y_dir(1);
    while (ff < 10) {
        if (if_y_up_stoper())
            ff++;
        else
            ff = 0;
        move_y(20, spdY);

        if (spdY <= 1000 && spdY > 200 && co > 2500 && co % 50 == 0 && co < 8000) spdY -= 4;

        if (co > Sets.motYFromSpToVe - 3000 && spdY < 1000 && co % 25 == 0) spdY += 4;  // was 10500
        co++;

        if (co == Sets.motYFromSpToVe + 100 /*motYFromVeToSp*/) return ECTimeout;
    }

    HAL_Delay(600);

    for (int i = 0; i < Sets.mot_y_to_center_spectr_steps; i++) {  // MOT_Y_TO_CENTER_SPECTR_STEPS  1100
        motYStepTo2();
    }
    // was 3450
    for (int i = 0; i < Sets.mot_x_to_center_spectr_steps; i++) {  // MOT_X_TO_CENTER_SPECTR_STEPS  2200
        motXStepTo2();
    }
    HAL_Delay(300);
    return ECOK;
}

// karetka co spektra na vesi
enum ErrorCode fSpToVe(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;
    // X to vesi
    motXSt1();
    // Y to UP

    if (if_y_up_stoper_Db()) {
        set_y_dir(0);
        for (uint16_t ggg = 0; ggg < 1500; ggg++) {
            move_y(200, 800);
        }
    }
    motYSt1();
    HAL_Delay(500);
    // Y to vesi
    uint32_t co = 0, ff = 0;
    uint16_t spdY = 700;  // MOT_Y_STOP_FLOW_DELAY 500   was500
    set_y_dir(0);
    while (ff < 10 && co < Sets.motYFromSpToVe /*12700*/) {  // MOT_Y_FROM_SPECTR_TO_VESI_STOP_FAST_STEPS 12700
        if (if_y_down_stoper())
            ff++;
        else
            ff = 0;
        move_y(20, spdY);
        if (spdY <= 1000 && spdY > 300 && co > 2500 && co % 50 == 0 && co < 8000) spdY -= 4;  //
        if (co > Sets.motYFromSpToVe - 3000 && spdY < 1000 && co % 25 == 0) spdY += 4;
        co++;
    }
    if (ff == 10) return ECMotYFault;
    HAL_Delay(100);
    if (if_x_right_stoper_Db()) {
        set_x_dir(0);
        for (int i = 0; i < Sets.motXToVe; i++) {
            move_x(500, 500);
        }
    }

    return ECOK;
}

enum ErrorCode fSpToPr(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;
    // X to vesi
    motXSt1();
    // Y to UP
    motYSt1();
    HAL_Delay(1000);
    // Y to vesi
    uint32_t co = 0, ff = 0;
    uint16_t spdY = 700;  // MOT_Y_STOP_FLOW_DELAY 500
    set_y_dir(0);
    while (ff < 10) {
        if (if_y_down_stoper())
            ff++;
        else
            ff = 0;
        move_y(20, spdY);

        if (spdY <= 1000 && spdY > 200 && co > 2500 && co % 40 == 0 &&
            co < Sets.mot_y_from_priemka_to_spectr_stop_fast_steps)
            spdY -= 4;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_STOP_FAST_STEPS 10500

        if (co > Sets.mot_y_from_priemka_to_spectr_start_slow_steps && spdY < 1000 && co % 25 == 0)
            spdY +=
                    6;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_START_SLOW_STEPS 20000   ona = MOT_Y_FROM_PRIEMKA_TO_SPECTR_MAX_STEPS-3000
        co++;
        if (co == Sets.mot_y_from_priemka_to_spectr_max_steps)
            return ECTimeout;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_MAX_STEPS 23500
    }

    return ECOK;
}

// karetka edet ot priemki na spektr
enum ErrorCode tStFind(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;
    motXSt1();
    motYSt2();
    DWT_Delay_us(500);
    uint32_t co = 0, ff = 0;
    uint16_t spdY = 700;  // MOT_Y_STOP_FLOW_DELAY 500
    if (if_x_right_stoper_Db() && if_y_down_stoper_Db()) {
        set_y_dir(1);
        while (ff < 10) {
            if (if_y_up_stoper())
                ff++;
            else
                ff = 0;
            move_y(20, spdY);

            if (spdY <= 1000 && spdY > 200 && co > 2500 && co % 50 == 0 &&
                co < Sets.mot_y_from_priemka_to_spectr_stop_fast_steps)
                spdY -=
                        4;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_STOP_FAST_STEPS 10500 (MOT_Y_FROM_PRIEMKA_TO_SPECTR_START_SLOW_STEPS/2)

            if (co > Sets.mot_y_from_priemka_to_spectr_start_slow_steps && spdY < 1000 && co % 25 == 0)
                spdY += 6;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_START_SLOW_STEPS 20500 (MOT_Y_FROM_PRIEMKA_TO_SPECTR_MAX_STEPS-3000)

            if (co == Sets.mot_y_from_priemka_to_spectr_max_steps)
                return ECTimeout;  // MOT_Y_FROM_PRIEMKA_TO_SPECTR_MAX_STEPS 23500
            co++;
        }
        // go to center spektr
        HAL_Delay(300);
        for (int i = 0; i < Sets.mot_y_to_center_spectr_steps; i++) {  // MOT_Y_TO_CENTER_SPECTR_STEPS  1100
            motYStepTo2();
        }
        // was 3450
        for (int i = 0; i < Sets.mot_x_to_center_spectr_steps; i++) {  // MOT_X_TO_CENTER_SPECTR_STEPS  2200
            motXStepTo2();
        }
        HAL_Delay(300);
    }

    // add mutex
    return ECOK;
}
/*--------------------------------------------------END
 * Movements--------------------------------------------------------------*/
