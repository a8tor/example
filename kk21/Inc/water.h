#ifndef _WATER_H
#define _WATER_H

/*-----------------------------------------------------------    Water   Start  -------------------------------------*/

// Stop pump water
enum ErrorCode pomUSto(void);

// Start pump water
enum ErrorCode pomUSta(void);

// stop to flush water
enum ErrorCode pomDSto(void);

// start to flush water
enum ErrorCode pomDSta(void);

/*-----------------------------------------------------------    Water   End  -------------------------------------*/

#endif  //_WATER_H
