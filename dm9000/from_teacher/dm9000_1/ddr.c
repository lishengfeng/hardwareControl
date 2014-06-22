#include "regs.h"
void ddr_init(void)
{
	MEM_SYS_CFG &= ~(1 << 7);
	
	P1MEMCCMD = 4;
	P1MEMCFG = (2 << 15)|(0 << 6)|(2 << 3)|(2 << 0);
	P1REFRESH = 1040;
	P1CASLAT = (3 << 1);
	P1T_DQSS = 1;
	P1T_MRD = 2;
	P1T_RAS = 6;
	P1T_RC = 9;
	P1T_RCD = 3;
	P1T_RFC = (11 << 0)|(8 << 5);
	P1T_RP = 3;
	P1T_RRD = 2;
	P1T_WR = 2;
//	P1T_WTR
//	P1T_XP = 
	P1T_XSR = 16;
//	P1T_ESR 
	P1MEMCFG2 = (1 << 11)|(3 << 8)|(1 << 6)|(1 << 1)|(1 << 0);

	P1DIRECTCMD = (2 << 18);
	P1DIRECTCMD = (0 << 18);
	P1DIRECTCMD = (3 << 18);
	P1DIRECTCMD = (3 << 18);
	P1DIRECTCMD = (2 << 18)|(2 << 16);
	P1DIRECTCMD = (2 << 18)|(3 << 4)|(2 << 0);
	P1MEMCCMD = 0;
	while((P1MEMSTAT & 0x3) != 1);
}
	



