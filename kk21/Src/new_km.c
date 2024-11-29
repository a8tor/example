/**
 ******************************************************************************
 * File Name          : new_km.c
 * Description        : This file provides king movements functions.
 ******************************************************************************
 */
#include "structs.h"
#include "services.h"

extern Settings Sets;


/*-------------------------------------- NEW KM  ---------------------------------------------    */

enum ErrorCode kingCalibrateToLeft(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;
//    if (!if_water_down_stoper_Db()) return ECWaterStoperFault;

    uint16_t delay_1 = Sets.hand_first_delay_preset + 500, delay_2 = Sets.hand_second_delay_preset + 500;
    uint32_t steps = 0;
    uint32_t counts = 0;

    if (!if_king_left_stoper_Db()) {
        set_king_dir(0);
        while (steps <= Sets.hand_max_steps_to_stop) {
            move_king(delay_1, delay_2);
            counts++;
            if (if_king_left_stoper()) {
                steps++;
            }
            if (counts > Sets.hand_rotate_timeout) {
                return ECHandRotateTimeout;
            }
        }
        if (if_king_right_stoper_Db()) {
            return ECHandAlarmStoperRight;
        }
    }
    return ECOK;
}


enum ErrorCode kingFromSideToSide(uint8_t dir) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    if (!if_water_down_stoper_Db()) return ECWaterStoperFault;

    uint16_t stop_1;
    uint16_t stop_2;
    if (dir == 0) {
        stop_1 = GPIO_PIN_1;
        stop_2 = GPIO_PIN_7;
    } else {
        stop_2 = GPIO_PIN_1;
        stop_1 = GPIO_PIN_7;
    }
    uint16_t delay_1 = Sets.hand_first_delay_preset, delay_2 = Sets.hand_second_delay_preset;
    uint32_t counts = 0;
    uint32_t steps = 0;
    uint8_t back_steps_number = 200;

    if (HAL_GPIO_ReadPinDebounced(GPIOE, stop_1)) {  // if already on stopper - recalibrate
        set_king_dir(!dir);
        while (counts < back_steps_number) {
            counts++;
            move_king(delay_1 + 500, delay_2 + 500);
        }
        counts = 0;
        set_king_dir(dir);
        HAL_Delay(500);
        if (HAL_GPIO_ReadPinDebounced(GPIOE, stop_1)) return dir ? ECHandAlarmStoperRight : ECHandAlarmStoperLeft;
        while (steps <= Sets.hand_max_steps_to_stop) {
            move_king(delay_1 + 500, delay_2 + 500);
            counts++;
            if (HAL_GPIO_ReadPin(GPIOE, stop_1)) {
                steps++;
            }
            if (counts > back_steps_number + 100) return ECHandRotateTimeout;
        }
        if (counts < back_steps_number - 100) {
            return dir ? ECHandAlarmStoperRight : ECHandAlarmStoperLeft;
        }
    } else if (HAL_GPIO_ReadPinDebounced(GPIOE, stop_2)) {
        set_king_dir(dir);
        while (steps <= Sets.hand_max_steps_to_stop) {
            if (counts < 500  && delay_1 > 300) {
                delay_1 -= 2;
                delay_2 -= 2;
            } else if (counts > 1800 && delay_1 < 2000) {
                delay_1 += 4;
                delay_2 += 4;
            }
            move_king(delay_1, delay_2);
            counts++;
            if (HAL_GPIO_ReadPin(GPIOE, stop_1)) {
                steps++;
            }
            if (counts > Sets.hand_rotate_timeout) {
                return ECHandRotateTimeout;
            }
        }
        if (counts < Sets.hand_rotate_timeout - 100) {
            return dir ? ECHandAlarmStoperRight : ECHandAlarmStoperLeft;
        }
        if (HAL_GPIO_ReadPinDebounced(GPIOE, stop_2)) {
            return dir ? ECHandAlarmStoperLeft : ECHandAlarmStoperRight;
        }
    } else {
        return ECHandAlarmNotInStopper;
    }
    return ECOK;
}


enum ErrorCode kingFromLeftToPos(uint32_t steps) {
    enum ErrorCode err = check_stops();
    if (err) return err;
    if (!if_water_down_stoper_Db()) return ECWaterStoperFault;

    uint16_t delay_1 = Sets.hand_first_delay_preset + 500, delay_2 = Sets.hand_second_delay_preset + 500;
    uint32_t counts = 0;

    if (if_king_left_stoper_Db()) {
        set_king_dir(1);  // right
        while (counts < steps) {
            counts++;
            if (steps > 300) {
                if (counts < steps / 3 && delay_1 > 300) {
                    delay_1 -= 3;
                    delay_2 -= 3;
                } else if (counts > steps - (steps / 3) && delay_1 < 2000) {
                    delay_1 += 4;
                    delay_2 += 4;
                }
            }
            move_king(delay_1, delay_2);
        }
        if (if_king_left_stoper_Db()) return ECHandAlarmStoperLeft;
    } else {
        return ECHandAlarmNotInStopper;
    }

    if (if_king_right_stoper()) {
        return ECHandAlarmStoperRight;
    }
    return ECOK;
}


enum ErrorCode kingFromPosToStop(uint32_t timeout, uint8_t dir) {

    enum ErrorCode err = check_stops();
    if (err) return err;

    if (!if_water_down_stoper_Db()) return ECWaterStoperFault;

    if (if_king_left_stoper_Db()) {
        return ECHandAlarmStoperLeft;
    }
    if (if_king_right_stoper_Db()) {
        return ECHandAlarmStoperRight;
    }

    uint16_t stop;
    if (dir == 0) {
        stop = GPIO_PIN_1;
    } else {
        stop = GPIO_PIN_7;
    }
    uint32_t delay_1 = Sets.hand_first_delay_preset + 500, delay_2 = Sets.hand_second_delay_preset + 500;
    uint32_t counts = 0;
    uint32_t steps = 0;

    set_king_dir(dir);

    while (steps <= Sets.hand_max_steps_to_stop) {
        if (timeout > 300) {
            if (counts < timeout / 3 && delay_1 > 300) {
                delay_1 -= 3;
                delay_2 -= 3;
            } else if (counts > timeout - (timeout / 3) && delay_1 < 2000) {
                delay_1 += 4;
                delay_2 += 4;
            }
        }
        move_king(delay_1, delay_2);
        counts++;
        if (HAL_GPIO_ReadPin(GPIOE, stop)) {
            steps++;
        }
        if (counts > timeout + 100) return ECHandRotateTimeout;
    }
    if (counts < timeout - 100) {
        return ECHandAlarmStoperLeft;
    }
    return ECOK;
}


enum ErrorCode PawnCalibrationCCW(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 250, delay_2 = 500;

    uint8_t stops = 0;
    int allstp = 0;
    if (if_pawn_stoper_Db()) {
        set_pawn_dir(1); //CW
        for (int stp = 0; stp < 300; stp++) {
            move_pawn(delay_1, delay_2);
        }
        DWT_Delay_us(500);
    }
    if (!if_pawn_stoper_Db()) {
        set_pawn_dir(0); //CCW
        while (stops <= Sets.sbros_steps_to_stop_calibration) {
            move_pawn(delay_1, delay_2);
            if (if_pawn_stoper())
                stops++;
            else
                stops = 0;
            if (allstp++ > Sets.sbros_shake_angle + 100) return ECTimeout;
        }
    }

    return ECOK;
}

enum ErrorCode DropPawnFunc(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;

    if (!(if_king_left_stoper_Db() || if_king_right_stoper_Db())) {
        return ECHandAlarmStoper;
    }

    uint16_t stp = 0;
    uint16_t delay_1 = 200, delay_2 = 400;

    set_pawn_dir(1); //CW
    for (; stp < Sets.sbros_shake_angle; stp++) {
        move_pawn(delay_1, delay_2);
    }
    HAL_Delay(200);
    for (int i = 0; i < Sets.sbros_shake_times; i++) {
        set_pawn_dir(0); //CCW
        for (stp = 0; stp < Sets.sbros_shake_small_angle; stp++) {
            move_pawn(Sets.sbros_min_spd, Sets.sbros_max_spd);
        }
        HAL_Delay(10);
        set_pawn_dir(1); //CW
        for (stp = 0; stp < Sets.sbros_shake_small_angle; stp++) {
            move_pawn(Sets.sbros_min_spd, Sets.sbros_max_spd);
        }
        HAL_Delay(10);
    }
    HAL_Delay(100);
    PawnCalibrationCCW(); /*------------------- NAHUY POTOM UBRAT !!!!!!!!!*/

    return ECOK;
}

/*---------------------------------------------------- END NEW KM -------------------------------------    */
