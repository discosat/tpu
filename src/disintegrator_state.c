#include <param/param.h>
#include <stdio.h>
#include <string.h>
#include "param_config.h"
#include "vmem_config.h"

PARAM_DEFINE_STATIC_VMEM(PARAMID_DISINTEGRATOR_STATE, disintegrator_state, PARAM_TYPE_INT16, -1 ,0, PM_DEBUG, NULL, NULL, config,VMEM_CONF_DISINTEGRATOR_STATE_ADDR, NULL);
