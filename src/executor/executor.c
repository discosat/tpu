#include <param/param.h>
#include "../param_config.h"
#include "../vmem_config.h"


/* Define a tpu_run parameter */
static uint16_t _tpu_run = 0;
PARAM_DEFINE_STATIC_RAM(PARAMID_TPU_RUN, tpu_run, PARAM_TYPE_UINT8, -1, 0, PM_CONF, NULL, NULL, &_tpu_run,"Set the tpu to execute the file");

/* Define a persisten target file to run */
PARAM_DEFINE_STATIC_VMEM(PARAMID_RUN_FILE, target_file, PARAM_TYPE_STRING, 200 ,0, PM_CONF, NULL, NULL, config,VMEM_CONF_RUNFILE_ADDR, NULL);

/* Define a run on boot parameter */
PARAM_DEFINE_STATIC_VMEM(PARAMID_RUN_ONBOOT , tpu_run_onboot, PARAM_TYPE_UINT8, -1 ,0, PM_CONF, NULL, NULL, config,VMEM_CONF_RUNONBOOT_ADDR, NULL);

void check_run(void) {
    uint8_t do_run = param_get_uint8(&tpu_run);
    if(do_run > 0){
        run_file();
        param_set_uint8(&tpu_run,0);
    }
}

void run_file(void) {
	char buf[100];
	param_get_data(&target_file, buf, 100);
	int len = strnlen(buf, 100);
	printf("Running file: %s %u\n", buf, len);
        system(buf);
}

void check_run_onboot(void) {
    uint8_t do_run = param_get_uint8(&tpu_run_onboot);
    if(do_run > 0){
        run_file();
        // This should probably run on every boot
        param_set_uint8(&tpu_run,0);
    }
}
