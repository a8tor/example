#ifndef _STRUCTS_H
#define _STRUCTS_H

#include "main.h"

enum ErrorCode {
    ECOK,  //0
    ECUnknownCommand,  //1
    ECInvalidArg,  //2
    ECMotOn,  //3
    ECMotOff,  //4
    ECNoWaterSensor,  //5
    ECViBCloseFault,  //6
    ECMotYFault,  //7
    ECTimeout,  //8
    ECWrongPositionCaretka,  //9
    ECKingFault,  //10
    ECWaterKrykFault,  //11
    ECWaterTimeout,  //12
    ECWaterStoperUpFault,  //13
    ECWaterStoperDownFault,  //14
    ECWaterStoperFault,  //15
    ECWaterNotInStoper,  //16
    ECPriemkaFail,  //17
    ECRevNoTube,  //18
    ECHandRotateTimeout,  //19
    ECHandAlarmStoperLeft,  //20
    ECHandAlarmStoperRight,  //21
    ECHandAlarmNotInStopper,  //22
    ECHandAlarmStoper,  //23
    ECxStoperFault,  //24
    ECxStoperLeftFault,  //25
    ECxStoperRightFault,  //26
    ECyStoperFault,  //27
    ECyStoperLeftFault,  //28
    ECyStoperRightFault,  //29
};

#pragma pack(1)
typedef struct {
    uint8_t type;  // 0 = status (from stm only); 1 = request/ack; 2 = command result;
    uint8_t id;    // request/command id
    int32_t arg1;  // arg 1
    int32_t arg2;  // arg 2
} Message;

#pragma pack(1)

enum Command {
    ResetOn,
    FullCal,

    MotXSt2,
    MotXSt1,
    StaXCal,
    MotXStp,

    MotYSt2,
    MotYSt1,
    StaYCal,
    MotYStp,

    TStFind,
    FSpToVe,
    FVeToSp,
    FSpToPr,

    StaZCal, //callibrate water to down
    StaZTDown, //move water from up to down
    StaZTUp,  //move water from down to up

    KarTurn,
    VUpTurn,  // //danger stanina x not control yet.Stanina Control !!!!!
    VodTurn,  // empty
    VodOpen,
    VodClos,
    MokTurn,
    MokFree,
    MokClos,
    MokOslb,
    MokSetA,
    PriTest,

    DatUrWa,
    PomUSta,
    PomUSto,
    PomDSta,
    PomDSto,

    ViBOpen,
    ViBClos,
    ViDOpen,
    ViDClos,
    ViDOpenNew,
    ViDClosNew,

    AlrmSta,
    AlrmSto,
    DorLOpe,
    DorLClo,

    DatUdar,

    PriOpen,
    PriClos,
    PriClosNew,
    TurnOnn,
    TurnOff,

    MotXStepTo2,
    MotXStepTo1,
    StaZUpStp,
    StaZDownStp,
    KaretkaSetAngle,  // very danger, later make safely

    // new
    ResetStateFlags,
    LedsOn,
    LedsOff,
    KaterShake,
    ReadSettings,
    WriteSettings,
    Unknown,

    DropPawn, //drop and shake pawn
    PawnCal, //callibrate pawn

    RevolvCalibration,
    RevolvZOpen,
    RevolvZClose,
    RevolvZStp,
    RevolvCheckCartridge,

    KingLRst,  // from left to right stoper
    KingRLst,  // from right to left stoper
    KingLD,    // from left stoper to dispenser
    KingDL,    // from dispenser to left stoper
    KingLW,    // from left stoper to water
    KingWL,    // from water to left stoper
    KingDR,    // from dispenser to right stoper
    KingWR,    // from water to right stoper
    KingCal,   // calibration to leaft stoper without error handlers
};

typedef struct {
    // botState
    _Bool DoorOpened;
    _Bool DoorAlarm;
    _Bool DatchikUdara;
    _Bool DoorLock;
    float DatchikTemperaturi;
    float DatchikZadimleniya;

    float DatchikNaklonaX;
    float DatchikNaklonaY;
    float DatchikNaklonaZ;
    float DatchikGPRSX;
    float DatchikGPRSY;
    float DatchikGPRSZ;
} State;

enum ErrorCode viBClos(void);

#pragma pack(1)
typedef struct {
    uint32_t mokAngl;
    uint32_t y_find_spd;
    uint32_t motYMaxSpeed;
    uint32_t motYFromSpToVe;
    uint32_t motXToVe;
    uint32_t motXminDelay;
    uint32_t motXmaxDelay;
    uint32_t timeToFlushWater;
    uint32_t timeToPompUpWater;
    uint32_t viDOpenMotorStp;
    uint32_t viDCloseMotorStp;
    uint32_t viBOpenMotorStp;
    uint32_t viBClosMotorStp;
    uint32_t input_window_open_angle;
    uint32_t input_window_corrupt_angle;
    uint32_t input_window_close_angle;
    uint32_t kryk_close_angle;
    uint32_t kryk_free_angle;
    uint32_t trap_close_angle;
    uint32_t trap_open_angle;
    uint32_t vesi_close_angle;
    uint32_t vesi_open_angle;
    uint32_t karetka_close_angle;
    uint32_t karetka_open_angle;

    uint32_t mot_z_before_slow_steps; //number of steps needed to move water before slowdown
    uint32_t mot_z_after_slow_steps; //number of steps needed to move water after slowdown

    uint32_t mot_y_to_center_spectr_steps;
    uint32_t mot_x_to_center_spectr_steps;
    uint32_t mot_y_from_priemka_to_spectr_max_steps;
    uint32_t mot_y_from_priemka_to_spectr_start_slow_steps;
    uint32_t mot_y_from_priemka_to_spectr_stop_fast_steps;
    uint32_t vesi_shake;

    uint32_t sbros_shake_times;
    uint32_t sbros_shake_angle;
    uint32_t sbros_shake_small_angle;
    uint32_t sbros_min_spd;
    uint32_t sbros_max_spd;
    uint32_t sbros_timeout_calibration_stp;
    uint32_t sbros_steps_to_stop_calibration;

    uint32_t rev_max_stp_calibration;
    uint32_t hand_max_steps_to_stop; //number of steps after stopper
    uint32_t hand_rotate_timeout; //max steps for side to side movement
    uint32_t hand_left_to_disp_steps;      // number of steps needed to move hand from left to dispencer
    uint32_t hand_left_to_water_steps;     // number of steps needed to move hand from left to water
    uint32_t hand_disp_to_right_steps;   // number of steps needed to move hand from dispencer to right
    uint32_t hand_water_to_right_steps;  // number of steps needed to move hand from water to right
    uint32_t hand_first_delay_preset;  // hand movement firts delay in ns
    uint32_t hand_second_delay_preset;  // hand movement second delay in ns
} Settings;

#pragma pack(1)

#pragma pack(1)
typedef struct {
    Message mess;
    Settings set;
} ReadSet;
#pragma pack(1)

#endif /* _STRUCTS_H */
