#include <vmem/vmem.h>
#include <vmem/vmem_ram.h>
#include <param/param.h>
#include <stdio.h>
#include "param_config.h"

/* Ringbuffer */
#ifndef STDBUF_SIZE
#define STDBUF_SIZE 1024 * 10
#endif

uint8_t vmem_stdbuf_heap[STDBUF_SIZE] __attribute__((section(".noinit")));
VMEM_DEFINE_STATIC_RAM_ADDR(stdbuf, "stdbuf", STDBUF_SIZE, vmem_stdbuf_heap);
uint16_t _stdbuf_in = 0;
uint16_t _stdbuf_out = 0;

PARAM_DEFINE_STATIC_RAM(PARAMID_STDBUF_IN, stdbuf_in, PARAM_TYPE_UINT16, 0, 0, PM_ERRCNT, NULL, "", &_stdbuf_in, NULL);
PARAM_DEFINE_STATIC_RAM(PARAMID_STDBUF_OUT, stdbuf_out, PARAM_TYPE_UINT16, 0, 0, PM_ERRCNT, NULL, "", &_stdbuf_out, NULL);

void _putchar(unsigned char character) {

	/* Place in vmem ringbuffer */
	((unsigned char *) vmem_stdbuf.vaddr)[_stdbuf_in++] = character;

	/* Increment (and truncate) input */
	_stdbuf_in %= STDBUF_SIZE;

	/* Push output pointer if input reaches output */
	if (_stdbuf_in == _stdbuf_out) {
		_stdbuf_out++;
		_stdbuf_out %= STDBUF_SIZE;
	}

	if (character == '\n') {
		_putchar('\r');
	}
}

int puts(const char * string) {
    int i = 0;
    while(string[i] != '\0') {
        _putchar(string[i]);
        i++;
    }
    _putchar('\n');
    return 0;
}
