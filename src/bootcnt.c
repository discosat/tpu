#include <vmem/vmem_file.h>
#include <param/param.h>
#include "vmem_config.h"

//Define file to store persisten params
VMEM_DEFINE_FILE(config, "config", "config.vmem", 5000);
//Example of creating a parameter in config file
PARAM_DEFINE_STATIC_VMEM(1, boot_cnt, PARAM_TYPE_UINT16, -1 ,0, PM_SYSINFO, NULL, NULL, config,VMEM_CONF_BOOTCNT_ADDR, NULL);
