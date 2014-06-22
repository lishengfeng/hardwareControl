#include "regs.h"

void wdt_isr(void)
{
	uart_printf("Watch Dog.\n");
	WTCLRINT = 0;
}
void wdt_init(void)
{
	WTCON = (0xff << 8)|(3 << 3)|(1 << 2);
	WTCNT = 2014;
	WTDAT = 2014;
	vic_request(26,wdt_isr);
	WTCON |= (1 << 5);
}



