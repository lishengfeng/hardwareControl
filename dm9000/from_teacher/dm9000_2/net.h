#ifndef __NET_H__
#define __NET_H__
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define ETH_ALEN 6

struct ethhdr {
		unsigned char   h_dest[ETH_ALEN];   /* destination eth addr */
		unsigned char   h_source[ETH_ALEN]; /* source ether addr    */
		u16      h_proto;        /* packet type ID field */
} __attribute__((packed));

#define ARP_P	0x0806

#define ARPOP_REQUEST   1       /* ARP request          */
#define ARPOP_REPLY 2       /* ARP reply            */
#define ARPHRD_ETHER    1       /* Ethernet 10Mbps      */
#define IP_P	0x0800
struct arphdr {
		u16      ar_hrd;     /* format of hardware address   */
		u16      ar_pro;     /* format of protocol address   */
		unsigned char   ar_hln;     /* length of hardware address   */
		unsigned char   ar_pln;     /* length of protocol address   */
		u16      ar_op;      /* ARP opcode (command)     */

		unsigned char       ar_sha[ETH_ALEN];   /* sender hardware address  */
		unsigned char       ar_sip[4];      /* sender IP address        */
		unsigned char       ar_tha[ETH_ALEN];   /* target hardware address  */
		unsigned char       ar_tip[4];      /* target IP address        */
};




#endif
