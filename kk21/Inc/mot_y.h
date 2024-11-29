#ifndef _MOT_Y_H
#define _MOT_Y_H

#include "stdint.h"

/*----------------------------------------------   Mot Y   Start  -------------------------------------*/

enum ErrorCode motYStepTo2(void);

enum ErrorCode motYStepTo1(void);

enum ErrorCode motYStp(int32_t x);

enum ErrorCode motYSt2(void);

enum ErrorCode motYSt1(void);

enum ErrorCode staYCal(void);

enum ErrorCode motYFastSpeedFrom2To1(void);

/*-----------------------------------------------------------    Mot Y   End  -------------------------------------*/
#endif  //_MOT_Y_H
