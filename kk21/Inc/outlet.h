#ifndef _OUTLET_H
#define _OUTLET_H

/*-----------------------------------------------------------    Mot Vidacha   Start
 * -------------------------------------*/
enum ErrorCode VidachaSolenoidUpperOpen(void);

enum ErrorCode VidachaSolenoidLowerOpen(void);

enum ErrorCode VidachaSolenoidUpperClose(void);

enum ErrorCode VidachaSolenoidLowerClose(void);

// open output window esli stopik zajat
enum ErrorCode viBOpen(void);

// zakritb okno vidachi.  Idem do 2250, ecli za eti shagi ne doshli do stopika, znachi cho-to zajali i nado otkritsya
// chobi ne zajat' ruku klietnta
enum ErrorCode viBClos(void);

enum ErrorCode viDClos(void);

// sbros zabitih izdelij iz okna vidachi
enum ErrorCode viDOpen(void);

enum ErrorCode viDClosNew(void);

// sbros zabitih izdelij iz okna vidachi
enum ErrorCode viDOpenNew(void);
/*-----------------------------------------------------------    Mot Vidacha   End
 * -------------------------------------*/

#endif  //_OUTLET_H
