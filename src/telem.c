#include <param/param.h>
#include <stdio.h>
#include <string.h>
#include "param_config.h"

static uint8_t _tlm_temp = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+0, tlm_temp, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_temp,"Temperature");

static uint8_t _tlm_free_mem = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+1, tlm_free_mem, PARAM_TYPE_UINT8, -1, 0, PM_TELEM, NULL, NULL, &_tlm_free_mem,"Free memory");

static float _tlm_user_util = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+2, tlm_user_util, PARAM_TYPE_FLOAT, -1, 0, PM_TELEM, NULL, NULL, &_tlm_user_util,"User CPU util");

static float _tlm_sys_util = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+3, tlm_sys_util, PARAM_TYPE_FLOAT, -1, 0, PM_TELEM, NULL, NULL, &_tlm_sys_util,"User CPU util");

static float _tlm_home_used = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TELEM+4, tlm_home_used, PARAM_TYPE_FLOAT, -1, 0, PM_TELEM, NULL, NULL, &_tlm_home_used,"Home usage");

void tlm_onehz(void){
    FILE *test = popen("./metrics.sh","r");
    char name[30];
    float val;

    uint8_t TEMP = 0;
    uint8_t FREE_MEM = 0;
    float USER_UTIL = 0;
    float SYS_UTIL = 0;
    float HOME_USED = 0;
    while(fscanf(test,"%s\t%f",&name,&val)==2){
        if(strcmp(name,"TEMP")==0){
            TEMP = (uint8_t) val;
        }
        if(strcmp(name,"FREE_MEM")==0){
            FREE_MEM = (uint8_t) val;
        }
        if(strcmp(name,"USER_UTIL")==0){
            USER_UTIL = (float) val;
        }
        if(strcmp(name,"SYS_UTIL")==0){
            SYS_UTIL = (float) val;
        }
        if(strcmp(name,"HOME_USED")==0){
            HOME_USED = (float) val;
        }
    }

    param_set_uint8(&tlm_temp,TEMP);
    param_set_uint8(&tlm_free_mem,FREE_MEM);
    param_set_float(&tlm_user_util,USER_UTIL);
    param_set_float(&tlm_sys_util,SYS_UTIL);
    param_set_float(&tlm_home_used,HOME_USED);
    pclose(test);
}
