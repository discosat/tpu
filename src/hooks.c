#include <stdio.h>
#include <pthread.h>
#include <ftp_server.h>

void hook_onehz(void) {
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
	pthread_create(&, NULL, &ftp_server, NULL);
}
