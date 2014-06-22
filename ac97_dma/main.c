#include "regs.h"
int main()
{
	uart_init();
	uart_printf("This is main\n");
	//1s采集44100 16位(看音频文件,一般是16位,高清有32位,我们只支持16位) 2声道 1位8字节
	ac97_init();
	wm9714_init();
	nand_read(0x50000000,0x40000,44100*16*2/8*(60*3+47));
	play_sound(0x50000000,44100*4*(60*3+47));
	while(1);
}
