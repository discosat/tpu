#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vmem_config.h"
#include <vmem/vmem_file.h>
#include <param/param.h>
#include "disintegrator_state.h"

int main(int argc, char **argv){

	vmem_file_init(&vmem_config);

	int16_t value = (int16_t) atoi(argv[1]);
	param_set_int16(&disintegrator_state, value);

	return 0;
}
