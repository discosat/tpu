#include <param/param.h>
#include <stdio.h>
#include <string.h>
#include "param_config.h"

static uint8_t _tlm_temp = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+0, tlm_temp, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_temp,"Temperature");

static uint8_t _tlm_used_mem = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+1, tlm_used_mem, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_used_mem,"Used memory");

static uint8_t _tlm_user_util = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+2, tlm_user_util, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_user_util,"User CPU util");

static uint8_t _tlm_sys_util = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+3, tlm_sys_util, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_sys_util,"User CPU util");

static uint8_t _tlm_stor_use = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+4, tlm_stor_use, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_stor_use,"Storage use");

void tlm_onehz(void){
    FILE *test = popen("/home/mendel/metrics","r");
    char name[30];
    char val_buf[30];

    uint8_t TEMP = 0;
    uint8_t USED_MEM = 0;
    uint8_t USER_UTIL = 0;
    uint8_t SYS_UTIL = 0;
    uint8_t STOR_USE = 0;
    while(fscanf(test,"%s %s",name,val_buf)==2){
        uint8_t val;
        sscanf(val_buf,"%d",&val);

        if(strcmp(name,"TEMP")==0){
            TEMP = val;
        }
        if(strcmp(name,"USED_MEM")==0){
            USED_MEM = val;
        }
        if(strcmp(name,"USER_UTIL")==0){
            USER_UTIL = val;
        }
        if(strcmp(name,"SYS_UTIL")==0){
            SYS_UTIL = val;
        }
        if(strcmp(name,"STOR_USE")==0){
            STOR_USE = val;
        }
    }

    param_set_uint8(&tlm_temp,TEMP);
    param_set_uint8(&tlm_used_mem,USED_MEM);
    param_set_uint8(&tlm_user_util,USER_UTIL);
    param_set_uint8(&tlm_sys_util,SYS_UTIL);
    param_set_uint8(&tlm_stor_use,STOR_USE);
    pclose(test);
}
