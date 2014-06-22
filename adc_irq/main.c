#include "regs.h"
void __attribute__((interrupt("IRQ")))adc_isr(void)
{
	uart_printf("%x\r",ADCDAT0&0xfff);
	ADCCLRINT=0;
	VIC0ADDRESS=0;
	VIC1ADDRESS=0;
}
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
        
	vic_request(63,adc_isr);//adc的中断号 63 S6410 410页	
	ADCCON = (1<<16)|(1<<14)|(65<<6);
	ADCTSC = 0x58;
	ADCDLY = 0xffff;
	while(1){
		ADCCON|=1;
		delay(10);
	}
}
