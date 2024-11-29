#ifndef _MOT_X_H
#define _MOT_X_H

#include "stdint.h"

/*-----------------------------------------------------------    Mot X   Start  -------------------------------------*/

enum ErrorCode motXStepTo2(void);

enum ErrorCode motXStepTo1(void);

enum ErrorCode motXStp(int32_t x);

enum ErrorCode motXSt2(void);

enum ErrorCode motXSt1(void);

enum ErrorCode staXCal(void);

/*-----------------------------------------------------------    Mot X   End  -------------------------------------*/

#endif  //_MOT_X_H
