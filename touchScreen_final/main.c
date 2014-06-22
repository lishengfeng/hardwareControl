#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\r\n");
	
	ts_init();
	while(1);
}
