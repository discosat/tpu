#include <vmem/vmem_file.h>
#include <param/param.h>
#include "vmem_config.h"

#include "param_config.h"

//Example of creating a parameter in config file
PARAM_DEFINE_STATIC_VMEM(PARAMID_SLOTNAME, slot_name, PARAM_TYPE_STRING, 50 ,0, PM_CONF, NULL, NULL, config,VMEM_CONF_SLOTNAME_ADDR, NULL);
