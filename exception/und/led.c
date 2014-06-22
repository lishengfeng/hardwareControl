#include "regs.h"

void led_init(void)
{//GPM2
	GPMCON &= ~(0xffff);//清空
	GPMCON |= (0x1111); //赋值
	GPMDAT |= (111111);
}
void led_on(int n)
{
	GPMDAT &=~(1<<n); //对应了六个口，第二个口,即是GPM2设置为低电位
}

void led_off(int n)
{
	GPMDAT |=(1<<n); 
}
