#include <stdio.h>
#include <pthread.h>
#include <csp_ftp/ftp_server.h>
#include "telem.h"
#include "executor/executor.h"

bool first_run = true;
void hook_onehz(void) {
    if(first_run){
        check_run_onboot();
        //tlm_onehz();
    }
    check_run();
    tlm_onehz();
    first_run = false;
}

/* 
void hook_gndreset(void) {
}
*/


/* This is at the beginning of the main routine, before usart and peripherals are inited */
void hook_init_early(void) {
}

/* This is at the end of the main routine */
void hook_init(void) {
	static pthread_t ftp_server_handle;
	pthread_create(&ftp_server_handle, NULL, &ftp_server_loop, NULL);
}
