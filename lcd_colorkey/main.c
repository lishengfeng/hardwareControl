#include "regs.h"
int main()
{
	int out;
	uart_init();
	uart_printf("This is main\n");
	key_init();
	lcd_init();

	nand_read(0x50000000,0x40000,480*272*4);
	
	int x,y;
	for(y=0;y<272;y++){
		for(x=0;x<480;x++){
			if(x<160){
				draw_rgb888(x,y,0xff0000);
			}else if(x>=160 &&x<320){
				draw_rgb888(x,y,0x00ff00);
			}else if(x>=320){
				draw_rgb888(x,y,0x0000ff);
			}
		}
	}
	while(1);
	
}
