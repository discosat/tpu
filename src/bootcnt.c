#include <vmem/vmem_file.h>
#include <param/param.h>
#include "vmem_config.h"

#include "param_config.h"

//Example of creating a parameter in config file
PARAM_DEFINE_STATIC_VMEM(PARAMID_BOOTCNT, boot_cnt, PARAM_TYPE_UINT16, -1 ,0, PM_SYSINFO, NULL, NULL, config,VMEM_CONF_BOOTCNT_ADDR, NULL);
