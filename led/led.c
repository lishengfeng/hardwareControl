#include "regs.h"

void led_init(void)
{//GPM2
	GPMCON &= ~(0xf << 8);//清空
	GPMCON |= (1<<8); //赋值
	GPMDAT |= (1<<2);
}
void led_on(void)
{
	GPMDAT &=~(1<<2); //对应了六个口，第二个口,即是GPM2设置为低电位
}

void led_off(void)
{
	GPMDAT |=(1<<2); 
}
