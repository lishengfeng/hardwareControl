#include "regs.h"

#define START_ADC ADCCON|=1
#define AUTO_PST ADCTSC=(1<<2)
#define WAIT_UP ADCTSC=(0x1d3)
#define WAIT_DOWN ADCTSC=(0xd3)

#define WDT_ON WTCON|=(1<<5)
#define WDT_OFF WTCON&=~(1<<5)


void __attribute__((interrupt("IRQ")))pen_isr(void)
{
        if(ADCUPDN&1){ //DOWN
                ADCUPDN&=~1;
                uart_printf("down\n");
                WDT_ON; 
        }
        if(ADCUPDN&(1<<1)){ //UP
                ADCUPDN&=~(1<<1);
                uart_printf("up\n");
        	WAIT_DOWN;
	        WDT_OFF;
        }

        ADCCLRINTPNDNUP = 0;
        VIC1ADDRESS = 0;
        VIC0ADDRESS = 0;
}

void __attribute__((interrupt("IRQ")))adc_isr(void)
{
	uart_printf("x=%x y=%x\n",ADCDAT0 &0xfff,ADCDAT1&0xfff);
	WAIT_UP;
	ADCCLRINT = 0;
	VIC0ADDRESS=0;
	VIC1ADDRESS=0;
}

void __attribute__((interrupt("IRQ")))wdt_isr(void)
{
	AUTO_PST;
	START_ADC;
	
	WTCLRINT = 0;
	VIC0ADDRESS=0;
	VIC1ADDRESS=0;
}
void wdt_init(void)
{
	WTCON = (0xff << 8)|(3 << 3)|(1 << 2);
	WTCNT = 201;
	WTDAT = 201;
	vic_request(26,wdt_isr);
	//WTCON |= (1 << 5);
}
void ts_init(void){
        ADCCON = (1<<16)|(1<<14)|(65<<6);
        ADCDLY = 0xffff;

        ADCTSC = 0xd3;
        wdt_init();
        vic_request(62,pen_isr);//62是INT_PNDNUP中断号
	vic_request(63,adc_isr);
}
