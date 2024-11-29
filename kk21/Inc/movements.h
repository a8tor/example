#ifndef _MOVEMENTS_H
#define _MOVEMENTS_H

/*--------------------------------------------------Movements-----------------------------------------------*/
// lights on
enum ErrorCode ledsOn(void);

// lights off
enum ErrorCode ledsOff(void);

enum ErrorCode fVeToSp(void);

// karetka co spektra na vesi
enum ErrorCode fSpToVe(void);

enum ErrorCode fSpToPr(void);

// karetka edet ot priemki na spektr
enum ErrorCode tStFind(void);
/*--------------------------------------------------END Movements-------------------------------------------------*/

#endif  //_MOVEMENTS_H
