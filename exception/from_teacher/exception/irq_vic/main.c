#include "regs.h"
void __attribute__((interrupt("IRQ")))soft_isr(void)
{
	uart_printf("soft int\n");
	VIC0SOFTINTCLEAR = (1 << 26);
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
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
