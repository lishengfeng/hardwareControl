#include "regs.h"
void arm_boot(void)
{
	clock_init();
	ddr_init();
	nand_init();
	//读 1M
	nand_read(0x55000000,0,0x100000);
}
