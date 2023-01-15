/*
 * write.c
 * created on: Jan 24, 2019
 *      Author: johan
 *      
 */

#include <vmem/vmem.h>
#include <vmem/vmem_ram.h>
#include <param/param.h>
#include <stdio.h>
#include "param_config.h"

/* Ringbuffer */
#ifndef STDBUF_SIZE
#define STDBUF_SIZE 1024 * 10
#endif
extern char live_stdbuf[STDBUF_SIZE];
extern unsigned short live_stdbuf_in;
extern unsigned short live_stdbuf_out;

VMEM_DEFINE_STATIC_RAM_ADDR(stdbuf, "stdbuf", STDBUF_SIZE, live_stdbuf);
PARAM_DEFINE_STATIC_RAM(PARAMID_STDBUF_IN, stdbuf_in, PARAM_TYPE_UINT16, 0, 0, PM_DEBUG, NULL, "", &live_stdbuf_in, NULL);
PARAM_DEFINE_STATIC_RAM(PARAMID_STDBUF_OUT, stdbuf_out, PARAM_TYPE_UINT16, 0, 0, PM_DEBUG, NULL, "", &live_stdbuf_out, NULL);

void _putchar(unsigned char character) {

	/* Random data overflow protection */
	if (live_stdbuf_in > STDBUF_SIZE)
		live_stdbuf_in = 1;

	/* Random data overflow protection */
	if (live_stdbuf_out > STDBUF_SIZE)
		live_stdbuf_out = 0;
	/* Place in vmem ringbuffer */
	((unsigned char *) vmem_stdbuf.vaddr)[live_stdbuf_in++] = character;

	/* Increment (and truncate) input */
	live_stdbuf_in %= STDBUF_SIZE;

	/* Push output pointer if input reaches output */
	if (live_stdbuf_in == live_stdbuf_out) {
		live_stdbuf_out++;
		live_stdbuf_out %= STDBUF_SIZE;
	}

	if (character == '\n') {
		_putchar('\r');
	}
 }

static int ao_putc(char c, FILE *ignore) {
	_putchar(c);
	return 0;
}

static const FILE __stdio = {
	.flags = __SWR,
	.put = ao_putc,
	.get = NULL,
	.flush = NULL,
};

#ifdef __strong_reference
#define STDIO_ALIAS(x) __strong_reference(stdin, x);
#else
#define STDIO_ALIAS(x) FILE *const x = &__stdio;
#endif

FILE *const stdin = &__stdio;
STDIO_ALIAS(stdout);
STDIO_ALIAS(stderr);


