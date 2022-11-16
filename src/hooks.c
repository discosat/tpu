#include <stdio.h>
#include <pthread.h>
#include <csp_ftp/ftp_server.h>

void hook_onehz(void) {
}

/* 
void hook_gndreset(void) {
}
*/


/* This is at the beginning of the main routine, before usart and peripherals are inited */
void hook_init_early(void) {
	static pthread_t ftp_server_handle;
	pthread_create(&ftp_server_handle, NULL, &ftp_server_loop, NULL);
}

/* This is at the end of the main routine */
void hook_init(void) {
}
