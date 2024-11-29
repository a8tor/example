/**
 ******************************************************************************
 * File Name          : mot_z.c
 * Description        : This file provides Z axis(water container) movements functions.
 ******************************************************************************
 */
#include "structs.h"
#include "services.h"

extern Settings Sets;

/*--------------------------------------    Mot Z   Start  -------------------------------------*/

enum ErrorCode staZCal(void) {

    enum ErrorCode err = check_stops();
    if (err) return err;

    if (!if_king_left_stoper_Db() && !if_king_right_stoper_Db()) return ECHandAlarmNotInStopper;

    uint16_t delay_1 = 160, delay_2 = 784;

    if (if_water_down_stoper_Db()) {
        set_water_dir(0);  //up
        for (int i = 0; i < 1600; i++) {
            move_water(delay_1, delay_2);
        }
        DWT_Delay_us(500);
        if (if_water_down_stoper_Db()) return ECWaterStoperDownFault;
    }
    set_water_dir(1);  //down
    uint16_t sts = 0;
    uint16_t steps = 0;
    while (sts < 15) {
        if (if_water_down_stoper() || (steps > 200 && if_water_up_stoper()))
            sts += 1;
        else
            sts = 0;
        move_water(delay_1, delay_2);
        steps++;
        if (steps >= Sets.mot_z_after_slow_steps + Sets.mot_z_before_slow_steps) {
            return ECWaterTimeout;
        }
    }
    DWT_Delay_us(500);
    return ECOK;
}

enum ErrorCode staZTDown(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    if (!if_king_left_stoper_Db() && !if_king_right_stoper_Db()) return ECHandAlarmNotInStopper;

    uint16_t delay_1 = 160, delay_2 = 784;

    if (!if_water_up_stoper_Db()) return ECWaterNotInStoper;

    set_water_dir(1);  //down
    uint16_t sts = 0;
    uint16_t steps = 0;
    while (sts < 15) {
        if (if_water_down_stoper() || (steps > 200 && if_water_up_stoper()))
            sts += 1;
        else
            sts = 0;

        move_water(delay_1, delay_2);
        steps++;
        if (steps >= Sets.mot_z_after_slow_steps + Sets.mot_z_before_slow_steps) {
            return ECWaterTimeout;
        }
        if (sts > 14 && steps < Sets.mot_z_after_slow_steps + Sets.mot_z_before_slow_steps - 200) {
            return ECWaterStoperDownFault;
        }

    }
    if (if_water_up_stoper_Db()) return ECWaterStoperUpFault;
    DWT_Delay_us(500);
    return ECOK;
}

enum ErrorCode staZTUp(void) {
    enum ErrorCode err = check_stops();
    if (err) return err;

    uint16_t delay_1 = 16, delay_2 = 784;
    uint16_t sts = 0;

    if (!if_king_left_stoper_Db() && !if_king_right_stoper_Db()) return ECHandAlarmNotInStopper;

    if (if_water_down_stoper_Db()) {
        set_water_dir(0);  //up
        for (uint16_t i = 0; i < Sets.mot_z_before_slow_steps; i++) {
            if (if_water_up_stoper() || (if_water_down_stoper() && i > 200))
                sts++;
            else
                sts = 0;
            if (sts > 15) return ECWaterStoperUpFault;
            move_water(delay_1, delay_2);
        }
        if (if_water_down_stoper_Db()) return ECWaterStoperDownFault;

        uint16_t steps = 0;
        delay_1 = 2000;
        delay_2 = 3000;

        while (sts < 15) {
            if (if_water_up_stoper() || (if_water_down_stoper()))
                sts++;
            else
                sts = 0;
            move_water(delay_1, delay_2);
            steps++;
            if (steps > Sets.mot_z_after_slow_steps) return ECWaterTimeout;

            if (sts > 14 && steps < Sets.mot_z_after_slow_steps - 200) {
                return ECWaterStoperUpFault;
            }
        }
    } else
        return ECWaterNotInStoper;
    return ECOK;
}

enum ErrorCode staZUpStp(void) {
    uint16_t delay_1 = 16, delay_2 = 784;

    if (!if_king_left_stoper_Db() && !if_king_right_stoper_Db()) return ECHandAlarmNotInStopper;

    if (!if_water_up_stoper_Db()) {
        set_water_dir(0);  //up
        for (int i = 0; i < 50; i++) {
            move_water(delay_1, delay_2);
        }
    }
    return ECOK;
}

enum ErrorCode staZDownStp(void) {
    uint16_t delay_1 = 16, delay_2 = 784;

    if (!if_king_left_stoper_Db() && !if_king_right_stoper_Db()) return ECHandAlarmNotInStopper;

    if (!if_water_down_stoper_Db()) {
        set_water_dir(1);  //down
        for (int i = 0; i < 50; i++) {
            move_water(delay_1, delay_2);
        }
    }
    return ECOK;
}
/*-----------------------------------------------------------    Mot Z   End  -------------------------------------*/
