#include "regs.h"
#include "net.h"

char send_buf[1024];

#define swap(a,b) { typeof(a) c = a; a = b;b = c;}
u16 htons(u16 hostshort)
{
	u16 tmp = hostshort;
	char *p = (void*)&tmp;
	swap(p[0],p[1]);
	return tmp;
}
u32 htonl(u32 hostlong)
{
	u32 tmp = hostlong;
	char *p = (void *)&tmp;
	swap(p[0],p[3]);
	swap(p[1],p[2]);
	return tmp;
}
void memcpy(char *to,char *from,int size)
{
	while(size--)
		*to++ = *from++;
}
char arm_mac[6] = {0x00,0x11,0x22,0x33,0x44,0x55};
char bd_mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
u32 arm_ip = (192 << 24)|(168 << 16)|(1 << 8)|(30 << 0);
u32 target_ip = (192 << 24)|(168 << 16)|(1 << 8)|(10 << 0);
int main()
{

	uart_init();
	
	uart_printf("main\n");

	dm9000_init();

	struct arphdr *arpp = (void *)(send_buf + sizeof(struct ethhdr));
	arpp->ar_hrd = htons(ARPHRD_ETHER);
	arpp->ar_pro = htons(IP_P);
	arpp->ar_hln = 6;
	arpp->ar_pln = 4;
	arpp->ar_op = htons(ARPOP_REQUEST);
	memcpy(arpp->ar_sha,arm_mac,6);
	*(u32 *)(arpp->ar_sip) = htonl(arm_ip);
	*(u32 *)(arpp->ar_tip) = htonl(target_ip);
	
	struct ethhdr *ethp = (void *)send_buf;
	memcpy(ethp->h_dest,bd_mac,6);
	memcpy(ethp->h_source,arm_mac,6);
	ethp->h_proto = htons(ARP_P);
	

	while(1){
//		dm9000_send((unsigned long)send_buf,sizeof(struct ethhdr) + sizeof(struct arphdr));
		delay(100);
	}
}




