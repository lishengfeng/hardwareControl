#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
	
	ADCCON = (1<<16)|(1<<14)|(65<<6);
	ADCTSC = 0x58;
	ADCDLY = 0xffff;

	while(1){
		ADCCON|=1;
		while(!(ADCCON&(1<<15)));
		uart_printf("%x\r",ADCDAT0&0xfff);
	}
	
}
