#include "regs.h"
int abc = 111;
int main()
{
	clock_init();
	uart_init();

	key_init();

	while(1);
	
}
