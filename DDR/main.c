#include "regs.h"
void str_cpy(char *to,char* from)
{
	while(*to++ = *from++);
}
int main()
{
	clock_init();
	uart_init();
	ddr_init();
	char *str = "hello ddr...";
	str_cpy((void *)0x52000000,str);
	uart_puts((void *)0x52000000);
	while(1);
	
}
