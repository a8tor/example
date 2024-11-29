#ifndef _SENSORS_H
#define _SENSORS_H

/*-----------------------------------------  Datchiki   Start-------------------------------------*/

enum ErrorCode datUrWa(void);

enum ErrorCode turnOnn(void);

enum ErrorCode turnOff(void);

enum ErrorCode alrmSta(void);

enum ErrorCode alrmSto(void);

// Stop ShockAlarm and reset ShokState
enum ErrorCode datUdar(void);

// doorAlarm   1-door open? 0 - door close
enum ErrorCode dorLClo(void);

// open zamok dveri
enum ErrorCode dorLOpe(void);

enum ErrorCode resetStateFlags(void);

/*--------------------------------------------  Datchiki   End  -------------------------------------*/
#endif  //_SENSORS_H
