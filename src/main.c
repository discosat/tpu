#include <stdio.h>
#include <csp/csp.h>
#include <stdio.h>
#include <unistd.h>
#include <param/param_server.h>
#include <pthread.h>
#include "hooks.h"
#include <vmem/vmem_server.h>
#include <vmem/vmem_file.h>
#include "bootcnt.h"
#include "vmem_config.h"
#include <csp/drivers/usart.h>
#include <csp_ftp/ftp_server.h>
#include "stdbuf_server.h"

csp_conf_t csp_conf = {
	.version = 2,
	.hostname = "IPU",
	.model = "",
	.revision = "",
	.conn_dfl_so = CSP_O_NONE,
	.dedup = CSP_DEDUP_OFF
};


void * vmem_server_task(void * param) {
	vmem_server_loop(param);
	return NULL;
}

void * ftp_server_task(void * param) {
	ftp_server_loop(param);
	return NULL;
}

void * router_task(void * param) {
	while(1) {
		csp_route_work();
	}
	return NULL;
}

static void * onehz_task(void * param) {
	while(1) {
		hook_onehz();
		sleep(1);
	}
	return NULL;
}

static void iface_init(void){
    csp_iface_t * iface = NULL;
    char* kiss_device = "/dev/ttyS1";


    // KISS setup
    csp_usart_conf_t conf = {
        .device = kiss_device,
        .baudrate = 115200,
        .databits = 8,
        .stopbits = 1,
        .paritysetting = 0,
        .checkparity = 0};

    int error = csp_usart_open_and_add_kiss_interface(&conf, CSP_IF_KISS_DEFAULT_NAME,  &iface);
    if (error != CSP_ERR_NONE) {
        csp_print("failed to add KISS interface [%s], error: %d\n", kiss_device, error);
        exit(1);
    }
    
/*
    int error = csp_can_socketcan_open_and_add_interface("vcan0", "CAN", 0, true, &iface);
    if (error != CSP_ERR_NONE) {
        csp_print("failed to add CAN interface [%s], error: %d\n", "vcan0", error);
        return;
    }
  */  
	//csp_zmqhub_init_filter2("ZMQ", "localhost", 3, 8, true, &iface);

    iface->addr = 162;
    iface->netmask = 8;
    iface->name = "KISS";
    csp_rtable_set(0, 0, iface, CSP_NO_VIA_ADDRESS);
	csp_iflist_set_default(iface);

}
int fd[2];

extern void _putchar(unsigned char character);
void bufread(void){
    char c;
    ssize_t rc;
    while ((rc = read(fd[0], &c, sizeof c)) > 0){
        _putchar(c);
    }
}

int main(void){
    pipe(fd);
    dup2(fd[1],1);
    dup2(fd[1],2);
	printf("\nbootmsg\n");

	srand(time(NULL));
	
	void serial_init(void);
	serial_init();

	/* Gndwdt
	gndwdt_init();
    */

	/* Init CSP with */
	csp_conf.hostname = HOSTNAME;
	csp_init();

	/* Interfaces */
    iface_init();
    csp_print("Connection table\r\n");
    csp_conn_print_table();

    csp_print("Interfaces\r\n");
    csp_iflist_print();

    csp_print("Route table\r\n");
    csp_rtable_print();

    //server_start();
	//kiss_init();
	hook_init_early();
	/*csp_rt_init(); ROUTING TABLE?? */

	csp_bind_callback(csp_service_handler, CSP_ANY);
	csp_bind_callback(param_serve, PARAM_PORT_SERVER);
	csp_bind_callback(stdbuf_serve, 15);

	vmem_file_init(&vmem_config);

	static pthread_t router_handle;
	pthread_create(&router_handle, NULL, &router_task, NULL);

	static pthread_t vmem_server_handle;
	pthread_create(&vmem_server_handle, NULL, &vmem_server_task, NULL);

	static pthread_t ftp_server_handle;
	pthread_create(&ftp_server_handle, NULL, &ftp_server_task, NULL);

	static pthread_t onehz_handle;
	pthread_create(&onehz_handle, NULL, &onehz_task, NULL);

	static pthread_t buf_handle;
	pthread_create(&buf_handle, NULL, &bufread, NULL);

	hook_init();
	while (1){
        sleep(10*1000); //TODO: Handle kbd interupt
    }

	//pthread_cancel(router_handle);
	//pthread_cancel(onehz_handle);
	//pthread_cancel(vmem_server_handle);
	//ptrhead_cancel(ftp_server_handle);

	//pthread_join(router_handle,NULL);
	//pthread_join(onehz_handle,NULL);
	//pthread_join(vmem_server_handle,NULL);
	//pthread_join(ftp_server_handle);
	
	return 0;
}
