#include "regs.h"
void led_init(void)
{//GPM2
	GPMCON &= ~0xffff;
	GPMCON |= 0x1111;
	 
	GPMDAT |= 0xf;
}
void led_on(int no)
{
	GPMDAT &= ~(1 << no);
}
void led_off(int no)
{
	GPMDAT |= (1 << no);
}

