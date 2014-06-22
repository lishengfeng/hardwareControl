#ifndef __REGS_H__
#define __REGS_H__

#define NF_BASE 0x70200000

#define GPOCON *(volatile unsigned long*)0x7F008140 
#define GPPCON *(volatile unsigned long*)0x7F008160 
#define NFCONF *(volatile unsigned long*)(NF_BASE+0x00) 
#define NFCONT *(volatile unsigned long*)(NF_BASE+0x04) 
#define NFCMMD *(volatile unsigned long*)(NF_BASE+0x08) 
#define NFADDR *(volatile unsigned long*)(NF_BASE+0x0c) 
#define NFDATA *(volatile unsigned long*)(NF_BASE+0x10) 
#define NFSTAT *(volatile unsigned long*)(NF_BASE+0x28) 


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
