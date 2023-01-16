#include "stdbuf_server.h"

#include <stdio.h>

#ifndef STDBUF_SIZE
#define STDBUF_SIZE 1024 * 10
#endif

extern char vmem_stdbuf_heap[STDBUF_SIZE];
extern uint16_t _stdbuf_in;
extern uint16_t _stdbuf_out;

#define STDBUF_MTU (CSP_BUFFER_SIZE - 16)

void stdbuf_serve(csp_packet_t * request) {
    printf("STDBUFF!!\n");
    int again;

    do {
        again = 0;

        int from = _stdbuf_out;
        int to = _stdbuf_in - 1;
        if (to < 0) {	
            to = STDBUF_SIZE;		           
        }
        if (to > STDBUF_SIZE) {				            
            break;				            
        }

        /* Wrap around */
        if (from > to) {			            
            to = STDBUF_SIZE;
            again = 1;
        }

        /* Truncate */
        if (to - from > STDBUF_MTU) {
            to = from + STDBUF_MTU;
            again = 1;
        }

        /* Increment */
        _stdbuf_out = (to) % STDBUF_SIZE;

        int len = to - from;
        csp_packet_t * packet = csp_buffer_get(STDBUF_MTU);
        if (packet == NULL)
            continue;

        memcpy(&packet->data[1], &vmem_stdbuf_heap[from], len);
        packet->data[0] = again;
        packet->length = len + 1;
        csp_sendto_reply(request, packet, CSP_O_CRC32);
    } while (again);
    csp_buffer_free(request);
}
