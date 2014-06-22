#include "setup.h"

char *bootargs = "root=/dev/nfs nfsroot=192.168.1.10:/uplooking,rw ip=192.168.1.20 console=ttySAC0,115200";//长度得加\0 
int str_len(char *str)
{
	int i=0;
	while(*str++){
		i++;
	}	
	return i+1;// "\0"
}

void str_cpy(char *to,char* from){
	while(*to++=*from++);
}

tag_init(){
	unsigned long *tag_addr = (void *)0x50000100;
	//core
	struct tag *tag;
	tag = (void *)tag_addr;
	tag->hdr.size = 5;
	tag->hdr.tag = ATAG_CORE;
	tag->u.core.pagesize = 0;
	tag->u.core.rootdev=0;

	tag_addr+=tag->hdr.size;
	//mem
	tag = (void *)tag_addr;
	tag->hdr.size = 4;
	tag->hdr.tag = ATAG_MEM;
	tag->u.mem.size = 128*1024*1024;
	tag->u.mem.start=0x50000000;
	
	tag_addr+=tag->hdr.size;
	//cmdline
	tag = (void *)tag_addr;
	tag->hdr.size = 2+(str_len(bootargs)+3)/4;
	tag->hdr.tag = ATAG_CMDLINE;
	str_cpy(tag->u.cmdline.cmdline,bootargs);

	tag_addr+=tag->hdr.size;
	//none
	tag = (void *)tag_addr;
	tag->hdr.size = 0;
	tag->hdr.tag = ATAG_NONE;
}
void do_bootm(unsigned long addr)
{
	tag_init();
	//svc mmu cache(不用操作)
	//r0 = 0 r1=1626 r2=0x50000100;
	//pc = addr
	void (*kernel)(int , int ,int )=(void *)addr;
	kernel(0,1626,0x50000100);
}
