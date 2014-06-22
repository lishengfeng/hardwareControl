#include "regs.h"
int a  = 0;
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\n");
	__asm__ __volatile__(
		"mov %0,pc\n"
		:"=&r"(out)
	);
	uart_printf("pc %x\n",out);
	uart_printf("a %x\n",a);
	while(1);
	
}
