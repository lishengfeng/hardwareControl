#include "regs.h"
void lcd_init(void) //window 0 RGB565
{


	GPECON &=~0xf;
	GPECON |=1;
	GPEDAT |=1;//GPE0 high
	GPFCON &=~(3<<28);
	GPFCON |=(1<<28);
	GPFDAT |=(1<<14);//GPF14 high
	GPICON = 0xaaaaaaaa;
	GPJCON = 0xaaaaaa;
	
	MOFPCON &=~(1<<3);
	SPCON &=~0x3;
	SPCON |=1;
	
	VIDCON1 =(1<<6)|(1<<5);
	VIDCON2 = 0; //省电
	
	VIDTCON0 =(1<<16)|(1<<8)|(9); //看6410 485页,日立13，14页垂直的，帧	
	VIDTCON1 =(1<<16)|(1<<8)|(40);
	
	VIDTCON2 = (271<<11)|(479); //行列数

//window0
	WINCON0 = (1<<16)|(5<<2)|(1);//[20]确定缓存位置,[2] 我们是565
	
//配置位置
	VIDOSD0A=0;
	VIDOSD0B=(479<<11)|(271);

//配置buffer位置
	VIDW00ADD0B0 = 0x50000000;//0x550000000之前都是空的
	VIDW00ADD1B0 = 0x50000000 + 480*272*2;//565一个像素占16位,所以16/8 = 2;

	VIDCON0 = (14<<6)|(1<<4)|(1<<1)|(1<<0);//配置好后,最后在显示
}
void draw_rgb565(int x,int y, int color)
{
	*((unsigned short*)0x50000000 + y*480 +x) = color; //short* 长度为2字节,一个像素刚好2个字节,所以直接+y*480+x

}
