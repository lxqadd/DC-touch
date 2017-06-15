#ifndef __TOUCHSCREEN_H
#define __TOUCHSCREEN_H
#include "sys.h"
void usart2_rev(unsigned char *str, unsigned short len);

typedef struct 
{
	u8 year;
	u8 moon;
	u8 day;
	u8 week;
	u8 hour;
	u8 min;			
	u8 sec;			
}Time;

#endif
