#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "main.h"
#include "structs.h"

extern State States;
extern Settings Sets;
extern ReadSet outset;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

enum ErrorCode setDefaultSettings() {
    /*
     Sets.karetkaMin=40;// Min angle - close
     Sets.karetkaMax=90;// Max angle - open
     Sets.vesiUpMin=40;// Min angle //open vesi
     Sets.vesiUpMax=62;// Max angle //close vesi
     Sets.vodaClose=72;// Voda trap close
     Sets.vodaOpen=89;// Voda trap open */
    Sets.mokAngl = 25;  // kryk
    Sets.y_find_spd = 1600;
    Sets.motYMaxSpeed = 200;
    // Sets.motYFromPrToSp=40;//  move from PRIEMKA to SPECTROMETR
    Sets.motYFromSpToVe = 40;  //  move from SPECTROMETR to VESI
    // Sets.motYFromVeToSp=40;//  move from VESI to SPECTROMETR
    // Sets.motYFromSpToPr=40;//  move from SPECTROMETR to PRIEMKA
    // Sets.motYFromSpToPrDelay=23500;
    Sets.motXToVe = 40;  //  move to vesi

    // Sets.motXToCenterSP=2200;//  move to vesi
    // Sets.motYToCenterSP=1100;//  move to vesi

    Sets.motXminDelay = 16;
    Sets.motXmaxDelay = 784;

    Sets.timeToFlushWater = 2000 * 60;
    Sets.timeToPompUpWater = 7500;

    Sets.viDOpenMotorStp = 1600;
    Sets.viDCloseMotorStp = 1700;

    Sets.viBOpenMotorStp = 2200;
    Sets.viBClosMotorStp = Sets.viBOpenMotorStp + 300;

    Sets.input_window_open_angle = 105;
    Sets.input_window_close_angle = 45;
    Sets.input_window_corrupt_angle = 75;
    Sets.kryk_close_angle = 100;
    Sets.kryk_free_angle = 25;

    Sets.trap_close_angle = 73;
    Sets.trap_open_angle = 88;

    Sets.vesi_close_angle = 52;
    Sets.vesi_open_angle = 77;

    Sets.karetka_close_angle = 90;
    Sets.karetka_open_angle = 40;

    Sets.mot_z_before_slow_steps = 6000;
    Sets.mot_z_after_slow_steps = 3500;  // thats good steps



    //-------------------- moves for steps
    // spectr
    Sets.mot_y_to_center_spectr_steps = 1100;
    Sets.mot_x_to_center_spectr_steps = 2200;
    Sets.mot_y_from_priemka_to_spectr_max_steps = 23500;
    Sets.mot_y_from_priemka_to_spectr_start_slow_steps = Sets.mot_y_from_priemka_to_spectr_max_steps - 3000;
    Sets.mot_y_from_priemka_to_spectr_stop_fast_steps = 10500;

    Sets.vesi_shake = 30;
    /*
    htim3.Instance->CCR4=0;//close 50
                   //htim3.Instance->CCR4=96;// need 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                   htim4.Instance->CCR2=Sets.vesi_close_angle;//DryDrop close
       htim4.Instance->CCR4=Sets.kryk_free_angle; // kryk
                   htim4.Instance->CCR1=Sets.karetka_close_angle;//servo SysPos karetke zakrito
                   htim4.Instance->CCR3=Sets.vodaClose;//sbros v mokroe izmerenie
    */
    Sets.sbros_shake_times = 16;
    Sets.sbros_shake_angle = 1000;
    Sets.sbros_shake_small_angle = 160;
    Sets.sbros_min_spd = 75;
    Sets.sbros_max_spd = 300;
    Sets.sbros_timeout_calibration_stp = 0;
    Sets.sbros_steps_to_stop_calibration = 7;
    Sets.rev_max_stp_calibration = 7;

    Sets.hand_max_steps_to_stop = 7;
    Sets.hand_rotate_timeout = 5000;
    Sets.hand_left_to_disp_steps = 200;
    Sets.hand_left_to_water_steps = 1250;
    Sets.hand_disp_to_right_steps = 2000;
    Sets.hand_water_to_right_steps = 1000;

    Sets.hand_first_delay_preset = 1500;
    Sets.hand_second_delay_preset = 2000;
    return ECOK;
}

enum ErrorCode readSettings() {
    outset.set = Sets;
    outset.mess.arg2 = sizeof(Sets);
    // printf("sets %d\t mess %d\t out %d\n",sizeof(outset.set),sizeof(outset.mess),sizeof(outset));
    return ECOK;
}

enum ErrorCode writeSettings(Settings *gets) {
    /*	Sets.karetkaMin=gets->karetkaMin;// Min angle - close
            Sets.karetkaMax=gets->karetkaMax;// Max angle - open
            Sets.vesiUpMin=gets->vesiUpMin;// Min angle //open vesi
            Sets.vesiUpMax=gets->vesiUpMax;// Max angle //close vesi
            Sets.vodaClose=gets->vodaClose;// Voda trap close
            Sets.vodaOpen=gets->vodaOpen;// Voda trap open*/

    Sets.y_find_spd = gets->y_find_spd;
    Sets.motYMaxSpeed = gets->motYMaxSpeed;
    //	Sets.motYFromPrToSp=gets->motYFromPrToSp;//  move from PRIEMKA to SPECTROMETR
    Sets.motYFromSpToVe = gets->motYFromSpToVe;  //  move from SPECTROMETR to VESI
    //	Sets.motYFromVeToSp=gets->motYFromVeToSp;//  move from VESI to SPECTROMETR
    //	Sets.motYFromSpToPr=gets->motYFromSpToPr;//  move from SPECTROMETR to PRIEMKA
    //	Sets.motYFromSpToPrDelay=gets->motYFromSpToPrDelay;
    Sets.motXToVe = gets->motXToVe;  //  move to vesi

    // Sets.motXToCenterSP=gets->motXToCenterSP;//  move to vesi
    // Sets.motYToCenterSP=gets->motYToCenterSP;//  move to vesi

    Sets.motXminDelay = gets->motXminDelay;
    Sets.motXmaxDelay = gets->motXmaxDelay;

    Sets.timeToFlushWater = gets->timeToFlushWater;
    Sets.timeToPompUpWater = gets->timeToPompUpWater;

    Sets.viDOpenMotorStp = gets->viDOpenMotorStp;
    Sets.viDCloseMotorStp = gets->viDCloseMotorStp;

    Sets.viBOpenMotorStp = gets->viBOpenMotorStp;
    Sets.viBClosMotorStp = Sets.viBOpenMotorStp + gets->viBClosMotorStp;

    Sets.input_window_open_angle = gets->input_window_open_angle;
    Sets.input_window_close_angle = gets->input_window_close_angle;
    Sets.input_window_corrupt_angle = gets->input_window_corrupt_angle;

    Sets.kryk_close_angle = gets->kryk_close_angle;
    Sets.kryk_free_angle = gets->kryk_free_angle;

    Sets.trap_close_angle = gets->trap_close_angle;
    Sets.trap_open_angle = gets->trap_open_angle;

    Sets.vesi_close_angle = gets->vesi_close_angle;
    Sets.vesi_open_angle = gets->vesi_open_angle;

    Sets.karetka_close_angle = gets->karetka_close_angle;
    Sets.karetka_open_angle = gets->karetka_open_angle;

    Sets.mot_z_before_slow_steps = gets->mot_z_before_slow_steps;
    Sets.mot_z_after_slow_steps = gets->mot_z_after_slow_steps;  // thats good steps

    //-------------------- moves for steps
    // spectr
    Sets.mot_y_to_center_spectr_steps = gets->mot_y_to_center_spectr_steps;
    Sets.mot_x_to_center_spectr_steps = gets->mot_x_to_center_spectr_steps;
    Sets.mot_y_from_priemka_to_spectr_max_steps = gets->mot_y_from_priemka_to_spectr_max_steps;
    Sets.mot_y_from_priemka_to_spectr_start_slow_steps =
            gets->mot_y_from_priemka_to_spectr_start_slow_steps;  // Sets.mot_y_from_priemka_to_spectr_max_steps - 3000;
    Sets.mot_y_from_priemka_to_spectr_stop_fast_steps = gets->mot_y_from_priemka_to_spectr_stop_fast_steps;

    Sets.vesi_shake = gets->vesi_shake;
    Sets.mokAngl = gets->kryk_free_angle;  // kryk
    htim3.Instance->CCR4 = 0;              // close 50
    // htim3.Instance->CCR4=96;// need 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    htim4.Instance->CCR2 = Sets.vesi_close_angle;     // DryDrop close
    htim4.Instance->CCR4 = Sets.kryk_free_angle;      // kryk
    htim4.Instance->CCR1 = Sets.karetka_close_angle;  // servo SysPos karetke zakrito
    htim4.Instance->CCR3 = Sets.trap_close_angle;     // sbros v mokroe izmerenie

    Sets.sbros_shake_times = gets->sbros_shake_times;
    Sets.sbros_shake_angle = gets->sbros_shake_angle;
    Sets.sbros_shake_small_angle = gets->sbros_shake_small_angle;
    Sets.sbros_min_spd = gets->sbros_min_spd;
    Sets.sbros_max_spd = gets->sbros_max_spd;
    Sets.sbros_timeout_calibration_stp = gets->sbros_timeout_calibration_stp;
    Sets.sbros_steps_to_stop_calibration = gets->sbros_steps_to_stop_calibration;
    Sets.rev_max_stp_calibration = gets->rev_max_stp_calibration;
    Sets.hand_max_steps_to_stop = gets->hand_max_steps_to_stop;
    Sets.hand_rotate_timeout = gets->hand_rotate_timeout;

    Sets.hand_left_to_disp_steps = gets->hand_left_to_disp_steps;
    Sets.hand_left_to_water_steps = gets->hand_left_to_water_steps;
    Sets.hand_disp_to_right_steps = gets->hand_disp_to_right_steps;
    Sets.hand_water_to_right_steps = gets->hand_water_to_right_steps;
    Sets.hand_first_delay_preset = gets->hand_first_delay_preset;
    Sets.hand_second_delay_preset = gets->hand_second_delay_preset;

    return ECOK;
}

#endif /* _SETTINGS_H */
