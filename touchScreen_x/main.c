#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
	
	ADCCON = (1<<16)|(1<<14)|(65<<6);
	ADCDLY = 0xffff;

	while(1){
		ADCTSC =1;//x,写在while目的是因为ADCTSC用完后会还原
		ADCCON|=1;
		while(!(ADCCON&(1<<15)));
		uart_printf("%x  ",ADCDAT0&0xfff);
		
		ADCTSC = 2;//y方向
		ADCCON|=1;
		while(!(ADCCON&(1<<15)));
		uart_printf("%x\n",ADCDAT1&0xfff);
		delay(10);
	}
	
}
