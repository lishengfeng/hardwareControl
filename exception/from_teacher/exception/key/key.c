#include "regs.h"
void key_isr(void)
{
	if(EINT0PEND & 1){
		uart_printf("EINT0\n");
		EINT0PEND = 1;
	}
	if(EINT0PEND & (1 << 1)){
		uart_printf("EINT1\n");
		EINT0PEND = (1 << 1);
	}
	if(EINT0PEND & (1 << 2)){
		uart_printf("EINT2\n");
		EINT0PEND = (1 << 2);
	}
	if(EINT0PEND & (1 << 3)){
		uart_printf("EINT3\n");
		EINT0PEND = (1 << 3);
	}
	if(EINT0PEND & (1 << 4)){
		uart_printf("EINT4\n");
		EINT0PEND = (1 << 4);
	}
	if(EINT0PEND & (1 << 5)){
		uart_printf("EINT5\n");
		EINT0PEND = (1 << 5);
	}
}
void key_init(void)
{
	GPNCON &= ~0xfff;
	GPNCON |= 0xaaa;
	EINT0CON0 &= ~0xfff;
	EINT0CON0 |= 0x222;
	EINT0MASK &= ~0x3f;
	vic_request(0,key_isr);
	vic_request(1,key_isr);
}	
