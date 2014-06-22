#include "regs.h"
void iow(unsigned short index,unsigned char data)
{
	DM9000_INDEX = index;
	DM9000_DATA8 = data;
}
unsigned char ior(unsigned short index)
{
	DM9000_INDEX = index;
	return DM9000_DATA8;
}

void dm9000_send(unsigned long addr,int size)
{
	int i;
	irq_disable(1);//防止dm9000_isr影响索引值
	DM9000_INDEX = 0xf8;
	for(i=0;i<(size+1)/2;i++){//16bit,每次发2,所以除以2
		DM9000_DATA16 = ((short *)addr)[i];
	}
	iow(0xfd,(size>>8)&0xff);
	iow(0xfc,size&0xff);
	iow(0x02,1);
	irq_enable(1);
}

unsigned char Net_Rxbuf
void __attribute__((interrupt("IRQ")))dm9000_isr(void)
{
	unsigned char int_status,Rx_ready;
	unsigned short Rx_status,Rx_len;
	if(EINT0PEND &(1<<7)){
		int_status=ior(0xfe);
		if(int_status&1){//rx
			//APP 30页 DM9000 27页
			//01表示有效,status状态,
			Rx_ready=ior(0xf0);
			Rx_ready=ior(0xf0);//读两次确保正确
			if(Rx_ready==1){
				DM9000_INDEX=0xf2;
				Rx_status = DM9000_DATA16;
				Rx_len = DM9000_DATA16;
				for(i=0;i<(Rx_len+1)/2;i++){
					((unsigned short*)Net_Rxbuf)[i]=DM9000_DATA16;
				}
			///eth 14 ip 20 udp 8
			uart_puts(Net_Rxbuf+42);
			}
			iow(0xfe,1);
		}
		if(int_status&2){//tx
			
			if(ior(0x01)&(4|8)){
				uart_printf("dm9000 send complete\n");
			}

			iow(0xfe,2);
		}
		EINT0PEND = (1<<7);//write 1 clean
	}
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

void dm9000_init(void)
{
	SROM_BW |=(1<<4); //位宽
	GPNCON &=~(0x3<<14);
	GPNCON |=(2<<14);//引脚配置成isr
	EINT0CON0 &=~(7<<12);//外部中断7 6410 361页
	EINT0CON0 |=(1<<12);
	EINT0MASK &=~(1<<7);
	vic_request(1,dm9000_isr);//411页

	//dm9000 参考Application Notes Ver.pdf 22页
	iow(0x1f,0x00);
	iow(0x00,1);
	delay(10);
	iow(0x00,0);
	iow(0xff,(1<<7));//4
	//5 如果有EEPROM(即买了MAC),cpu写读出来写到第六部,我们没有造假的
	//6 不能用全1,mac地址,mac的第一个地址位1必须是0
	iow(0x10,0x00);
	iow(0x11,0x11);
	iow(0x12,0x22);
	iow(0x13,0x33);
	iow(0x14,0x44);
	iow(0x15,0x55);
	//7 不写或全写1 以太网规定
	//8 清除
	iow(0x01,(1<<2)|(1<<3)|(1<<5));
	iow(0xfe,0xff); //27 FE 
	//9 处理中断函数,已有dm9000_isr
	//10
	iow(0xff,(1<<7)|(1<<1)|(1<<0));//(1<<7)要保留下来是第四步的
		
}
