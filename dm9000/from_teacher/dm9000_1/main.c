#include "regs.h"
int main()
{
	uart_init();
	
	uart_printf("main\n");
	dm9000_init();
	while(1);
}




