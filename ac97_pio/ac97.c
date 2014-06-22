#include "regs.h"
unsigned long music_start,music_offset,music_end;
void __attribute__((interrupt("IRQ")))ac97_isr(void)
{
	AC_GLBCTRL |=(1<<29);//clear
	AC_PCMDATA = *(unsigned long*)(music_start+music_offset);
	music_offset+=4;
	if(music_start+music_offset>=music_end){
		//停止 AC_GLBCTRL [21] [13:12]
		//循环播放
		music_offset = 0;
	}
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}
void ac97_init(void) //在6410上
{
	GPDCON=0x444444;
	//看状态图1150页到active 
	//1143页
	AC_GLBCTRL=1;//cold reset
	delay(10);
	AC_GLBCTRL = 0;//normal
	AC_GLBCTRL = (1<<1);//warm reset
	delay(10);	
	AC_GLBCTRL = 0;
	AC_GLBCTRL = (1<<2);
	delay(10);
	AC_GLBCTRL |= (1<<3);
	AC_CODEC_CMD = (1<<23);//读一次AC_DODEC 激活
	while(!((AC_GLBSTAT&0x7)==0x3));//active
	uart_printf("ac97 active\n");
}
void write_wm9714(unsigned char index,unsigned short data)
{
	AC_CODEC_CMD = (index<<16)|(data);
	delay(10);//延时 ac_link发送数据需要时间
}
void wm9714_init(void)//编解码器 在mainboard上
{
	//9714手册AUDIO DACS----38(数字转换成模拟)//根据音乐来配置声道个数
	//76---给模块加电
	//输出部分
	//38 15耳机混音 14扬声器混音 13单声道 12:8左声道音量 0:4右声道音量
	write_wm9714(0x0c,(0x10<<8)|(0x10<<0));
	write_wm9714(0x5c,(1<<7));//自动静音
	//43 采样率
	write_wm9714(0x2a,1);
	write_wm9714(0x2c,0xac44);
	//54 PGA自动增益控制 音乐
	write_wm9714(0x1c,(2<<6)|(2<<4)|(3<<11)|(3<<8));
	//55 音量
	write_wm9714(0x04,0);//headphone volume
	write_wm9714(0x02,0);//spead volume
	//60 检测耳机插入4使能 7:6 哪个引脚控制(我们的已经被接到speaker)  DETECT 原理图 GPIO1/PCMCLK
	write_wm9714(0x24,(1<<4));
	//70 Low Battery alarm delay control
	write_wm9714(0x5a,0);
	//76 电源控制
	write_wm9714(0x26,0);
	write_wm9714(0x3c,0);
	write_wm9714(0x3e,0);
	
	
}
void play_sound(unsigned long addr,int size)
{
	music_start = addr;
	music_offset = 0;
	music_end = addr+size;
	vic_request(36,ac97_isr);
	//搬数据模式,中断模式,当FIFO空发送中断
	AC_GLBCTRL|=(1<<12)|(1<<21);
}
