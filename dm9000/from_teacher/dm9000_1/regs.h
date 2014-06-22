#ifndef __REGS_H__
#define __REGS_H__
//DM9000
#define SROM_BW *(volatile unsigned long*)0x70000000 
#define DM9000_INDEX	*(volatile unsigned short*)0x18000000
#define DM9000_DATA8	*(volatile unsigned char *)0x18000004
#define DM9000_DATA16	*(volatile unsigned short *)0x18000004
//TS
#define ADCCON 			*(volatile unsigned long*)0x7E00B000 
#define ADCTSC 			*(volatile unsigned long*)0x7E00B004 
#define ADCDLY 			*(volatile unsigned long*)0x7E00B008 
#define ADCDAT0 		*(volatile unsigned long*)0x7E00B00C 
#define ADCDAT1 		*(volatile unsigned long*)0x7E00B010 
#define ADCUPDN 		*(volatile unsigned long*)0x7E00B014 
#define ADCCLRINT 		*(volatile unsigned long*)0x7E00B018 
#define ADCCLRINTPNDNUP *(volatile unsigned long*)0x7E00B020 
 
//LCD
//GPI  GPJ  GPE0 GPF14
#define GPECON 			*(volatile unsigned long*)0x7F008080 
#define GPEDAT 			*(volatile unsigned long*)0x7F008084 
#define GPFCON 			*(volatile unsigned long*)0x7F0080A0 
#define GPFDAT 			*(volatile unsigned long*)0x7F0080A4 
#define GPICON 			*(volatile unsigned long*)0x7F008100 
#define GPJCON 			*(volatile unsigned long*)0x7F008120 
 
#define MOFPCON 		*(volatile unsigned long*)0x7410800C
#define SPCON 			*(volatile unsigned long*)0x7F0081A0
 
#define VIDCON0  		*(volatile unsigned long*)0x77100000	
#define VIDCON1  		*(volatile unsigned long*)0x77100004	
#define VIDCON2  		*(volatile unsigned long*)0x77100008	
 
#define VIDTCON0 		*(volatile unsigned long*)0x77100010 
#define VIDTCON1 		*(volatile unsigned long*)0x77100014 
#define VIDTCON2 		*(volatile unsigned long*)0x77100018 
 
#define WINCON0  		*(volatile unsigned long*)0x77100020 
#define WINCON1  		*(volatile unsigned long*)0x77100024 
 
#define VIDOSD0A 		*(volatile unsigned long*)0x77100040 
#define VIDOSD0B 		*(volatile unsigned long*)0x77100044 
#define VIDOSD0C 		*(volatile unsigned long*)0x77100048 
 
#define VIDOSD1A 		*(volatile unsigned long*)0x77100050 
#define VIDOSD1B 		*(volatile unsigned long*)0x77100054 
#define VIDOSD1C 		*(volatile unsigned long*)0x77100058 
 
#define VIDW00ADD0B0	*(volatile unsigned long*)0x771000A0
#define VIDW01ADD0B0    *(volatile unsigned long*)0x771000A8
 
#define VIDW00ADD1B0  	*(volatile unsigned long*)0x771000D0
#define VIDW01ADD1B0  	*(volatile unsigned long*)0x771000D8
 
#define W1KEYCON0   	*(volatile unsigned long*)0x77100140
#define W1KEYCON1   	*(volatile unsigned long*)0x77100144

//DDR
//MEM_SYS_CFG &= ~(1 << 7)
#define MEM_SYS_CFG *(volatile unsigned long*)0x7E00F120 
#define P1MEMSTAT 	*(volatile unsigned long*)0x7E001000 
#define P1MEMCCMD 	*(volatile unsigned long*)0x7E001004
#define P1DIRECTCMD *(volatile unsigned long*)0x7E001008
#define P1MEMCFG 	*(volatile unsigned long*)0x7E00100C
#define P1REFRESH 	*(volatile unsigned long*)0x7E001010 
#define P1CASLAT 	*(volatile unsigned long*)0x7E001014 
#define P1T_DQSS 	*(volatile unsigned long*)0x7E001018 
#define P1T_MRD 	*(volatile unsigned long*)0x7E00101C
#define P1T_RAS 	*(volatile unsigned long*)0x7E001020 
#define P1T_RC 		*(volatile unsigned long*)0x7E001024 
#define P1T_RCD 	*(volatile unsigned long*)0x7E001028 
#define P1T_RFC 	*(volatile unsigned long*)0x7E00102C 
#define P1T_RP 		*(volatile unsigned long*)0x7E001030 
#define P1T_RRD 	*(volatile unsigned long*)0x7E001034 
#define P1T_WR 		*(volatile unsigned long*)0x7E001038 
#define P1T_WTR 	*(volatile unsigned long*)0x7E00103C 
#define P1T_XP 		*(volatile unsigned long*)0x7E001040 
#define P1T_XSR 	*(volatile unsigned long*)0x7E001044 
#define P1T_ESR 	*(volatile unsigned long*)0x7E001048 
#define P1MEMCFG2 	*(volatile unsigned long*)0x7E00104C 

//NAND  
//GPO0   GPP3~7
#define GPOCON 	*(volatile unsigned long*)0x7F008140 
#define GPPCON 	*(volatile unsigned long*)0x7F008160 
 
#define NFCONF  *(volatile unsigned long*)(0x70200000+0x00)  
#define NFCONT  *(volatile unsigned long*)(0x70200000+0x04) 
#define NFCMMD  *(volatile unsigned long*)(0x70200000+0x08) 
#define NFADDR  *(volatile unsigned long*)(0x70200000+0x0c) 
#define NFDATA  *(volatile unsigned long*)(0x70200000+0x10) 
#define NFSTAT  *(volatile unsigned long*)(0x70200000+0x28) 


//EINT
#define EINT0CON0 *(volatile unsigned long*)0x7F008900 
#define EINT0MASK *(volatile unsigned long*)0x7F008920 
#define EINT0PEND *(volatile unsigned long*)0x7F008924 

//Watch Dog
#define WTCON 		*(volatile unsigned long*)0x7E004000 
#define WTDAT 		*(volatile unsigned long*)0x7E004004 
#define WTCNT 		*(volatile unsigned long*)0x7E004008 
#define WTCLRINT 	*(volatile unsigned long*)0x7E00400C 

//VIC
#define VIC0_BASE 0x71200000
#define VIC1_BASE 0x71300000

#define VIC0INTENABLE 		*(volatile unsigned long*)(VIC0_BASE + 0x010) 
#define VIC0INTENCLEAR 		*(volatile unsigned long*)(VIC0_BASE + 0x014) 
#define VIC0SOFTINT 		*(volatile unsigned long*)(VIC0_BASE + 0x018) 
#define VIC0SOFTINTCLEAR 	*(volatile unsigned long*)(VIC0_BASE + 0x01C) 
#define VIC0VECTADDR0 		*(volatile unsigned long*)(VIC0_BASE + 0x100) 
#define VIC0ADDRESS 		*(volatile unsigned long*)(VIC0_BASE + 0xF00) 

#define VIC1INTENABLE 		*(volatile unsigned long*)(VIC1_BASE + 0x010) 
#define VIC1INTENCLEAR 		*(volatile unsigned long*)(VIC1_BASE + 0x014) 
#define VIC1SOFTINT 		*(volatile unsigned long*)(VIC1_BASE + 0x018) 
#define VIC1SOFTINTCLEAR 	*(volatile unsigned long*)(VIC1_BASE + 0x01C) 
#define VIC1VECTADDR0 		*(volatile unsigned long*)(VIC1_BASE + 0x100) 
#define VIC1ADDRESS 		*(volatile unsigned long*)(VIC1_BASE + 0xF00) 


//uart
#define GPACON 		*(volatile unsigned long*)0x7F008000 

#define ULCON0 		*(volatile unsigned long*)0x7F005000 
#define UCON0 		*(volatile unsigned long*)0x7F005004 
#define UFCON0 		*(volatile unsigned long*)0x7F005008 
#define UMCON0 		*(volatile unsigned long*)0x7F00500C 
#define UTRSTAT0	*(volatile unsigned long*)0x7F005010
#define UERSTAT0	*(volatile unsigned long*)0x7F005014
#define UFSTAT0 	*(volatile unsigned long*)0x7F005018 
#define UMSTAT0 	*(volatile unsigned long*)0x7F00501C 
#define UTXH0 		*(volatile unsigned long*)0x7F005020  
#define URXH0 		*(volatile unsigned long*)0x7F005024  
#define UBRDIV0 	*(volatile unsigned long*)0x7F005028 
#define UDIVSLOT0 	*(volatile unsigned long*)0x7F00502C 

//clock
#define APLL_LOCK 	*(volatile unsigned long*)0x7E00F000 
#define MPLL_LOCK 	*(volatile unsigned long*)0x7E00F004 
#define APLL_CON 	*(volatile unsigned long*)0x7E00F00C 
#define MPLL_CON 	*(volatile unsigned long*)0x7E00F010 
#define CLK_SRC 	*(volatile unsigned long*)0x7E00F01C 
#define CLK_DIV0 	*(volatile unsigned long*)0x7E00F020 
#define HCLK_GATE 	*(volatile unsigned long*)0x7E00F030 
#define PCLK_GATE 	*(volatile unsigned long*)0x7E00F034 
#define MISC_CON 	*(volatile unsigned long*)0x7E00F838 
#define OTHERS 		*(volatile unsigned long*)0x7E00F900 


#define GPMCON *(volatile unsigned long*)0x7F008820 
#define GPMDAT *(volatile unsigned long*)0x7F008824 
#define GPMPUD *(volatile unsigned long*)0x7F008828 

#define GPNCON *(volatile unsigned long*)0x7F008830 
#define GPNDAT *(volatile unsigned long*)0x7F008834 

#endif
