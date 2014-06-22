#include "regs.h"

#define NAND_ENABLE	NFCONT &= ~(1 << 1)
#define NAND_DISABLE NFCONT |= (1 << 1)
#define NAND_BUSY	while(!(NFSTAT & 1))

void nand_init(void)
{
	GPOCON &= ~0x3;
	GPOCON |= 2;
	GPPCON &= ~(0x3ff << 6);
	GPPCON |= (0x2aa << 6);

	NFCONF = (1 << 12)|(2 << 8)|(0 << 4)|(1 << 2);
	NFCONT = 7;

	NAND_ENABLE;
	NFCMMD = 0xff;
	NAND_BUSY;
	NAND_DISABLE;
}
typedef enum{
	Nand_RW,
	Nand_Erase,
}Nand_Ops;
void nand_send_address(unsigned long nand,Nand_Ops ops)
{
	unsigned long col,row;
	col = nand & 0x7ff;
	row = (nand >> 11);
	switch(ops){
		case Nand_RW:
			NFADDR = col & 0xff;
			NFADDR = (col >> 8) & 0xff;
		case Nand_Erase:
			NFADDR = row & 0xff;
			NFADDR = (row >> 8) & 0xff;
			NFADDR = (row >> 16) & 0xff;
		break;
	}
}
void nand_erase(unsigned long nand,unsigned long size)
{
	unsigned long addr;
	NAND_ENABLE;
	for(addr = nand;addr < nand + size;addr += 64 * 2048){
		NFCMMD = 0x60;
		nand_send_address(addr,Nand_Erase);
		NFCMMD = 0xd0;
		NAND_BUSY;
	}
	NAND_DISABLE;
}
void nand_write(unsigned long ram,unsigned long nand,unsigned long size)
{
	unsigned long addr;
	int i;
	NAND_ENABLE;
	for(addr = nand;addr < nand + size; addr += 2048){
		NFCMMD = 0x80;
		nand_send_address(addr,Nand_RW);
		for(i = 0;i < 2048;i += 4,ram += 4){
			NFDATA = *(unsigned long*)ram;
		}
		NFCMMD = 0x10;
		NAND_BUSY;
	}
	NAND_DISABLE;
}
void nand_read(unsigned long ram,unsigned long nand,unsigned long size)
{
	unsigned long addr;
	int i;
	NAND_ENABLE;
	for(addr = nand;addr < nand + size;addr += 2048){
		NFCMMD = 0x00;
		nand_send_address(addr,Nand_RW);
		NFCMMD = 0x30;
		NAND_BUSY;
		for(i = 0;i < 2048;i += 4,ram += 4){
			*(unsigned long*)ram = NFDATA;
//			ram += 4;
		}
	}
	NAND_DISABLE;
}
void nand_read_id(void)
{
	NAND_ENABLE;
	volatile char *id = (void *)&NFDATA;
	NFCMMD = 0x90;
	NFADDR = 0x00;
	int i;
	for(i = 0;i < 5;i++){
		uart_printf("%x ",*id);
	}
	NAND_DISABLE;
}








