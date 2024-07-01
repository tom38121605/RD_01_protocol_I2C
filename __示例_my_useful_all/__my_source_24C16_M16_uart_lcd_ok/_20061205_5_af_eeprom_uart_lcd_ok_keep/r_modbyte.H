#include <iom16v.h>
#include <macros.h>

#define	SETBIT(x,y) (x|=(1<<y))      //set bit y in byte x
#define	CLRBIT(x,y) (x&=(~(1<<y)))   //clear bit y in byte x
#define	CHKBIT(x,y) (x&(1<<y))       //check bit y in byte x