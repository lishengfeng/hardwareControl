#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
	
	ADCCON = (1<<16)|(1<<14)|(65<<6);
	ADCDLY = 0xffff;

	while(1){
		ADCTSC =(1<<2);//自动计算x,y
		ADCCON|=1;
		while(!(ADCCON&(1<<15)));
		uart_printf("%x %x\n",ADCDAT0&0xfff,ADCDAT1&0xfff);
		delay(10);
	}
	
}
