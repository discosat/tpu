#include "stdbuf_server.h"

#include <stdio.h>

#ifndef STDBUF_SIZE
#define STDBUF_SIZE 1024 * 10
#endif

extern char live_stdbuf[STDBUF_SIZE];
extern unsigned short live_stdbuf_in;
extern unsigned short live_stdbuf_out;

#define STDBUF_MTU (CSP_BUFFER_SIZE - 16)

void stdbuf_serve(csp_packet_t * request) {

	int again;

	do {
		again = 0;

		int from = live_stdbuf_out;
		int to = live_stdbuf_in - 1;
		if (to < 0) {	
			to = STDBUF_SIZE;		           
	       	}
		if (to > STDBUF_SIZE) {				            
			break;				            
		}
	
	       	/* Wrap around */
	        if (from > to) {			            
			to = STDBUF_SIZE;								again = 1;
		}

		/* Truncate */
		if (to - from > STDBUF_MTU) {
			to = from + STDBUF_MTU;
			again = 1;
		}

		/* Increment */
		live_stdbuf_out = (to) % STDBUF_SIZE;

		int len = to - from;

		printf("F%u T%u O%u I%u\n", from, to, live_stdbuf_out, live_stdbuf_in);
												csp_packet_t * packet = csp_buffer_get(STDBUF_MTU);
												if (packet == NULL)
			continue;
		
		memcpy(&packet->data[1], &live_stdbuf[from], len);
		packet->data[0] = again;
		packet->length = len + 1;
		csp_sendto_reply(request, packet, CSP_O_CRC32);
	} while (again);
											csp_buffer_free(request);
}
