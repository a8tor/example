#ifndef _SERVO_H
#define _SERVO_H

#include "stdint.h"

/*-----------------------------------------------------------    Servos   Start  -------------------------------------*/

// not use yet
enum ErrorCode karetkaSetAngle(uint16_t angle);

// sbros izdeliya iz karetki na vesi
enum ErrorCode karTurn(void);

// Sbros izdeliya s vesov v trap
// Stanina Control !!!!!
enum ErrorCode vUpTurn(void);

enum ErrorCode vodTurn(void);

// otkrit' dveri trapa
enum ErrorCode vodOpen(void);

//// zakrit' dveri trapa
enum ErrorCode vodClos(void);

// not use ?
enum ErrorCode mokTurn(void);

// kryk otpuska lodki
enum ErrorCode mokFree(void);

// kryk zahvata lodki
enum ErrorCode mokClos(void);

// kryk zahvata lodki    not use
enum ErrorCode mokOslb(void);

enum ErrorCode mokSetA(void);

enum ErrorCode priTest(void);

enum ErrorCode priSolO(void);

enum ErrorCode priSolC(void);

enum ErrorCode katerShake(void);

// otkrit' okno priemku
enum ErrorCode priOpen(void);

// with corrupt control
enum ErrorCode priClosNew(void);

// zakrit' okno priemku
enum ErrorCode priClos(void);
/*----------------------------------------    Servos   End  -------------------------------------*/

#endif  //_SERVO_H
