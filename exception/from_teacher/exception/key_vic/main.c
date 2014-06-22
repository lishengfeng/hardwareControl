#include "regs.h"
int main()
{
	clock_init();
	uart_init();

	key_init();

	while(1);
	
}
