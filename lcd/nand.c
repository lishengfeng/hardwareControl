#include "regs.h"

#define NAND_ENABLE NFCONT &=~(1<<1)
#define NAND_DISABLE NFCONT|=(1<<1)
#define NAND_BUSY while(!(NFSTAT&1))

void nand_init(void)
{
	GPOCON &=~0x3;
	GPOCON |= 2;
	GPPCON &=~(0x3ff<<6);
	GPPCON |=(0x2aa <<6);

	NFCONF = (1<<12)|(1<<8)|(0<<4)|(1<<2);
	NFCONT = 7; //芯片用时才变成低电位,不然费电
	
	NAND_ENABLE;
	NFCMMD=0xff; //0C.pdf 36页 //复位芯片
	NAND_BUSY;//36页最后一句它说会有一段时间busy，所以得等待他busy恢复
	NAND_DISABLE;
	 
}
typedef enum{
	Nand_RW,
	Nand_Erase,
}Nand_Ops;
void nand_send_address(unsigned long nand,Nand_Ops ops)
{
	unsigned long col,row; //行和列地址
	col = nand&0x7ff; //低11位
	row = (nand>>11);
	//看时序图
	switch(ops){
		case Nand_RW:
			NFADDR = col& 0xff;
			NFADDR = (col>>8)&0xff;
		case Nand_Erase:
			NFADDR = row &0xff;
			NFADDR = (row>>8)&0xff;
			NFADDR = (row>>16)&0xff;
		break;
	}
}

void nand_erase(unsigned long nand,unsigned long size)
{
	//0c.pdf -> 28页
	//将size 拆分成多个块来擦除
	unsigned long addr;
	NAND_ENABLE;
	//64页*2K 一个块
	for(addr = nand;addr<nand+size;addr+=64*2048){
		NFCMMD = 0x60;//看28页时序图
		nand_send_address(addr,Nand_Erase);
		NFCMMD = 0xd0;
		NAND_BUSY;
	}
	NAND_DISABLE;
}

void nand_write(unsigned long ram,unsigned long nand,unsigned long size)
{
        //0c.pdf -> 24页
        unsigned long addr;
        int i;
        NAND_ENABLE;
        //2048 2k
        for(addr = nand;addr<nand+size;addr+=2048){
                NFCMMD = 0x80;
                nand_send_address(addr,Nand_RW);
		//准备数据
                //S3C6410 c语言long是32位4字节,如果是char 则i++,ram++
                //一次读4字节
                for(i=0;i<2048;i+=4,ram+=4){
                        NFDATA = *(unsigned long*)ram;
                }
		NFCMMD = 0x10;		
                NAND_BUSY;
        }
        NAND_DISABLE;

}

void nand_read(unsigned long ram,unsigned long nand, unsigned long size)
{	
        //0c.pdf -> 21页
        unsigned long addr;
        int i;
        NAND_ENABLE;
        //2048 2k
        for(addr = nand;addr<nand+size;addr+=2048){
                NFCMMD = 0x00;
                nand_send_address(addr,Nand_RW);
                NFCMMD = 0x30;
                NAND_BUSY;
                //S3C6410 c语言long是32位4字节,如果是char 则i++,ram++
                //一次读4字节
                for(i=0;i<2048;i+=4,ram+=4){
                        *(unsigned long*)ram = NFDATA;
                        //ram+=4;
                }
        }
        NAND_DISABLE;
}

void nand_read_id()
{
	//用char就是八字节的读，用long就是32字节读了，这里必须用char读
	volatile char *id = (void *)&NFDATA;
	int i,j;
	NAND_ENABLE;
	NFCMMD = 0x90;
	NFADDR = 0x00;
	uart_printf("below is the nand_id\n");
	for(i=0;i<5;i++){
		uart_printf("%x ",*id);		
	}
	NAND_DISABLE;
}
