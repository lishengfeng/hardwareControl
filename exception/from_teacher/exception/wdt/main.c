#include "regs.h"
int main()
{
	clock_init();
	uart_init();

	wdt_init();

	while(1);
}
