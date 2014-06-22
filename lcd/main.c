#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\n");
	lcd_init();

	//nand_read(0x50000000,0x40000,0x100000);
	
	int x,y;
	for(y=100;y<200;y++){
		for(x=200;x<300;x++){
			draw_rgb565(x,y,0x3f<<5);//565 绿色 为111111
		}
	}
	while(1);
	
}
