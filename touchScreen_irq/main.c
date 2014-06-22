#include "regs.h"
void __attribute__((interrupt("IRQ")))pen_isr(void)
{
	if(ADCUPDN&1){ //DOWN
		ADCUPDN&=~1;
		uart_printf("down\n");
		ADCTSC=0x1d3; //按下后检测抬起
	}
	if(ADCUPDN&(1<<1)){ //UP
		ADCUPDN&=~(1<<1);
		uart_printf("up\n");
		ADCTSC=0xd3;//抬起后检测按下
	}

	ADCCLRINTPNDNUP = 0;//清除寄存器
	VIC1ADDRESS = 0;
	VIC0ADDRESS = 0;
}
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
	
	ADCCON = (1<<16)|(1<<14)|(65<<6);
	ADCDLY = 0xffff;

	ADCTSC = 0xd3;

	vic_request(62,pen_isr);//62是INT_PNDNUP中断号
	while(1);
}
