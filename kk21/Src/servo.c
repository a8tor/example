/**
 ******************************************************************************
 * File Name          : servo.c
 * Description        : This file provides servo`s movements functions.
 ******************************************************************************
 */
#include "structs.h"

extern Settings Sets;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;
/*------------------------------------------   Servos   Start  -------------------------------------*/

// not use yet
enum ErrorCode karetkaSetAngle(uint16_t angle) {
    /*
    if (angle<KaretkaMin)
                    angle=KaretkaMin;
    else if (angle>KaretkaMax)
                    angle=KaretkaMax;
    //   Add position accept control
    //if (){
    */
    htim4.Instance->CCR1 = angle;
    HAL_Delay(3000);
    //}
    return ECOK;
};

// Throw product from the carriage onto the scales// sbros izdeliya iz karetki na vesi
enum ErrorCode karTurn(void) {
    uint16_t i = Sets.karetka_close_angle;  // KARETKA_CLOSE_ANGLE znacenie iz KaretkaMin
    if (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9)) {
        htim4.Instance->CCR1 = i;
        HAL_Delay(3000);
        if (Sets.karetka_close_angle < Sets.karetka_open_angle) {
            while (i < Sets.karetka_open_angle) {  // KARETKA_OPEN_ANGLE znacenie iz KaretkaMax
                htim4.Instance->CCR1 = i;
                HAL_Delay(50);
                i++;
            }
            HAL_Delay(500);
            while (i > Sets.karetka_close_angle) {  // KARETKA_CLOSE_ANGLE znacenie iz KaretkaMin
                htim4.Instance->CCR1 = i;
                HAL_Delay(50);
                i--;
            }
        } else if (Sets.karetka_close_angle > Sets.karetka_open_angle) {
            while (i > Sets.karetka_open_angle) {  // KARETKA_OPEN_ANGLE znacenie iz KaretkaMax
                htim4.Instance->CCR1 = i;
                HAL_Delay(50);
                i--;
            }
            HAL_Delay(500);
            while (i < Sets.karetka_close_angle) {  // KARETKA_CLOSE_ANGLE znacenie iz KaretkaMin
                htim4.Instance->CCR1 = i;
                HAL_Delay(50);
                i++;
            }
        }
    } else
        return ECWrongPositionCaretka;
    HAL_Delay(500);
    htim4.Instance->CCR1 = Sets.karetka_close_angle;
    HAL_Delay(800);
    htim4.Instance->CCR1 = 0;
    return ECOK;
}

// Sbros izdeliya s vesov v trap
// Stanina Control !!!!!
enum ErrorCode vUpTurn(void) {
    uint16_t i = Sets.vesi_close_angle;  // close   VESI_CLOSE_ANGLE   znachenie iz VesiUpMax
    if (Sets.vesi_close_angle > Sets.vesi_open_angle) {
        htim4.Instance->CCR2 = i;
        HAL_Delay(1000);
        while (i > Sets.vesi_open_angle) {  // slow up    VESI_OPEN_ANGLE   znachenie iz VesiUpMin
            htim4.Instance->CCR2 = i;
            HAL_Delay(50);
            i--;
        }
        HAL_Delay(1000);
        while (i < Sets.vesi_close_angle) {  // slow close   VESI_CLOSE_ANGLE   znachenie iz VesiUpMax
            htim4.Instance->CCR2 = i;
            HAL_Delay(50);
            i++;
        }
    } else if (Sets.vesi_close_angle < Sets.vesi_open_angle) {
        htim4.Instance->CCR2 = i;
        HAL_Delay(1000);
        while (i < Sets.vesi_open_angle) {  // slow up    VESI_OPEN_ANGLE   znachenie iz VesiUpMin
            htim4.Instance->CCR2 = i;
            HAL_Delay(50);
            i++;
        }
        HAL_Delay(1000);
        while (i > Sets.vesi_close_angle) {  // slow close   VESI_CLOSE_ANGLE   znachenie iz VesiUpMax
            htim4.Instance->CCR2 = i;
            HAL_Delay(50);
            i--;
        }
    }
    htim4.Instance->CCR2 = Sets.vesi_close_angle;
    HAL_Delay(500);
    htim4.Instance->CCR2 = 0;
    return ECOK;
}

enum ErrorCode vodTurn(void) { return ECOK; }

// otkrit' dveri trapa
enum ErrorCode vodOpen(void) {
    htim4.Instance->CCR3 = Sets.trap_open_angle;  // TRAP_OPEN_ANGLE     znachenie iz VodaOpen
    HAL_Delay(2000);
    htim4.Instance->CCR3 = 0;
    return ECOK;
}

//// zakrit' dveri trapa
enum ErrorCode vodClos(void) {
    htim4.Instance->CCR3 = Sets.trap_close_angle;  // TRAP_CLOSE_ANGLE     znachenie iz VodaClos
    HAL_Delay(2000);
    htim4.Instance->CCR3 = 0;
    return ECOK;
}

// not use ?
enum ErrorCode mokTurn(void) { /*
  if (Sets.mokAngl<40)
          while(Sets.mokAngl<42){//slow close
                          htim4.Instance->CCR4=Sets.mokAngl;
                    HAL_Delay(50);
                          Sets.mokAngl++;
                  } HAL_Delay(500);
  */
    return ECOK;
}

// kryk otpuska lodki
enum ErrorCode mokFree(void) {
    if (Sets.mokAngl < Sets.kryk_free_angle) {
        while (Sets.mokAngl < Sets.kryk_free_angle) {  // slow free   KRYK_FREE_ANGLE 100
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl++;
        }
        HAL_Delay(500);
    } else if (Sets.mokAngl > Sets.kryk_free_angle) {
        while (Sets.mokAngl > Sets.kryk_free_angle) {  // slow free   KRYK_FREE_ANGLE 100
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl--;
        }
        HAL_Delay(500);
    }

    htim4.Instance->CCR4 = 0;
    return ECOK;
}

// kryk zahvata lodki
enum ErrorCode mokClos(void) {
    if (Sets.mokAngl > Sets.kryk_close_angle) {
        while (Sets.mokAngl > Sets.kryk_close_angle) {  // slow close KRYK_CLOSE_ANGLE 25
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl--;
        }
        HAL_Delay(500);
    } else if (Sets.mokAngl < Sets.kryk_close_angle) {
        while (Sets.mokAngl < Sets.kryk_close_angle) {  // slow close KRYK_CLOSE_ANGLE 25
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl++;
        }
        HAL_Delay(500);
    }

    htim4.Instance->CCR1 = 0;
    return ECOK;
}

// kryk zahvata lodki  //not use
enum ErrorCode mokOslb(void) {
    if (Sets.mokAngl < 50)
        while (Sets.mokAngl < 53) {  // slow close
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl++;
        }
    HAL_Delay(500);
    return ECOK;
}

enum ErrorCode mokSetA(void) { /*
  if (x>24 && x<=68){
                  while(mokAngl>x ){//slow close
                          htim4.Instance->CCR3=mokAngl;
                    HAL_Delay(50);
                          mokAngl--;
                  } HAL_Delay(500);

          }*/
    return ECOK;
}

enum ErrorCode priTest(void) { return ECOK; }

enum ErrorCode priSolO(void) { return ECOK; }

enum ErrorCode priSolC(void) { return ECOK; }

enum ErrorCode katerShake(void) {
    if (Sets.kryk_free_angle > Sets.kryk_close_angle) {
        Sets.mokAngl = Sets.kryk_free_angle;
        while (Sets.mokAngl > Sets.kryk_close_angle) {  // slow close
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl--;
        }
        for (uint8_t ii = 0; ii < Sets.vesi_shake; ii++) {
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl += 6;
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl -= 6;
        }

        HAL_Delay(2000);
    } else if (Sets.kryk_free_angle < Sets.kryk_close_angle) {
        Sets.mokAngl = Sets.kryk_free_angle;
        while (Sets.mokAngl < Sets.kryk_close_angle) {  // slow close
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl++;
        }
        for (uint8_t ii = 0; ii < Sets.vesi_shake; ii++) {
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl -= 6;
            htim4.Instance->CCR4 = Sets.mokAngl;
            HAL_Delay(50);
            Sets.mokAngl += 6;
        }

        HAL_Delay(2000);
    }

    return ECOK;
}

// otkrit' okno priemku
enum ErrorCode priOpen(void) {
    htim3.Instance->CCR4 = 0;

    HAL_Delay(50);
    uint16_t i = Sets.input_window_close_angle;  // INPUT_WINDOW_CLOSE_ANGLE  96

    if (Sets.input_window_close_angle > Sets.input_window_open_angle) {
        for (; i > Sets.input_window_open_angle; i--) {  // INPUT_WINDOW_OPEN_ANGLE  40

            htim3.Instance->CCR4 = i;
            HAL_Delay(50);
        }
    } else if (Sets.input_window_close_angle < Sets.input_window_open_angle) {
        for (; i < Sets.input_window_open_angle; i++) {  // INPUT_WINDOW_OPEN_ANGLE  40

            htim3.Instance->CCR4 = i;
            HAL_Delay(50);
        }
    }

    htim3.Instance->CCR4 = 0;
    return ECOK;
}

// with corrupt control
enum ErrorCode priClosNew(void) {
    htim3.Instance->CCR4 = 0;

    uint16_t i = Sets.input_window_open_angle;  // INPUT_WINDOW_OPEN_ANGLE  40
    htim3.Instance->CCR4 = i;
    HAL_Delay(100);
    if (Sets.input_window_close_angle > Sets.input_window_open_angle) {
        HAL_Delay(100);
        for (; i < Sets.input_window_close_angle; i++) {  // INPUT_WINDOW_CLOSE_ANGLE  96

            htim3.Instance->CCR4 = i;
            HAL_Delay(100);
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1 && i < Sets.input_window_corrupt_angle &&
                i > (Sets.input_window_open_angle + 10)) {
                for (; i > Sets.input_window_open_angle; i--) {
                    htim3.Instance->CCR4 = i;
                    HAL_Delay(100);
                }
                htim3.Instance->CCR4 = 0;
                return ECPriemkaFail;
            }
        }
    } else if (Sets.input_window_close_angle < Sets.input_window_open_angle) {
        for (; i > Sets.input_window_close_angle; i--) {  // INPUT_WINDOW_CLOSE_ANGLE  96

            htim3.Instance->CCR4 = i;
            HAL_Delay(100);
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1 && i > Sets.input_window_corrupt_angle &&
                i < (Sets.input_window_open_angle - 10)) {
                for (; i < Sets.input_window_open_angle; i++) {
                    htim3.Instance->CCR4 = i;
                    HAL_Delay(100);
                }
                htim3.Instance->CCR4 = 0;
                return ECPriemkaFail;
            }
        }
    }
    HAL_Delay(100);
    htim3.Instance->CCR4 = Sets.input_window_close_angle;
    HAL_Delay(500);
    htim3.Instance->CCR4 = 0;
    return ECOK;
}

// zakrit' okno priemku
enum ErrorCode priClos(void) {
    htim3.Instance->CCR4 = 0;

    uint16_t i = Sets.input_window_open_angle;  // INPUT_WINDOW_OPEN_ANGLE  40
    htim3.Instance->CCR4 = i;
    HAL_Delay(100);
    if (Sets.input_window_close_angle > Sets.input_window_open_angle) {
        HAL_Delay(100);
        for (; i < Sets.input_window_close_angle; i++) {  // INPUT_WINDOW_CLOSE_ANGLE  96

            htim3.Instance->CCR4 = i;
            HAL_Delay(50);
        }
    } else if (Sets.input_window_close_angle < Sets.input_window_open_angle) {
        for (; i > Sets.input_window_close_angle; i--) {  // INPUT_WINDOW_CLOSE_ANGLE  96

            htim3.Instance->CCR4 = i;
            HAL_Delay(50);
        }
    }
    HAL_Delay(100);
    htim3.Instance->CCR4 = Sets.input_window_close_angle;
    HAL_Delay(500);
    htim3.Instance->CCR4 = 0;
    return ECOK;
}
/*-----------------------------------------------------------    Servos   End  -------------------------------------*/
