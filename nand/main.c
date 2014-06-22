#include "regs.h"
int main()
{
	clock_init();
	uart_init();
	nand_init();

	/*char *str = "Hello nand...";
	
	nand_erase(0x40000,0x100000);
	nand_write((unsigned long)str,0x40000,2048);
	//别读太前，是程序，也别读太后是栈 8k
	//找Disassembly of section .text: 表示代码段
	nand_read(0x1000,0x40000,2048);
	uart_puts((void*)0x1000);
	*/
	nand_read_id();
	while(1);
	
}
