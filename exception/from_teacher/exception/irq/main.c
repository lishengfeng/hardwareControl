#include "regs.h"
void soft_isr(void)
{
	uart_printf("soft int\n");
	VIC0SOFTINTCLEAR = (1 << 26);
}//26
int main()
{
	clock_init();
	uart_init();
	vic_request(26,soft_isr);
	while(1){
		VIC0SOFTINT = (1 << 26);
		delay(100);
	}
}
