#include <stdio.h>
#include "vmem_config.h"
#include <vmem/vmem_file.h>
#include <param/param.h>
#include "bootcnt.h"

void main(void){
	vmem_file_init(&vmem_config);
    printf("increamenting bootcounter!!\n");
    uint16_t count = param_get_uint16(&boot_cnt);
    printf("Current: %d\n",count);
    count=count+1;
    printf("new: %d\n",count);
    param_set_uint16(&boot_cnt,count);
}
