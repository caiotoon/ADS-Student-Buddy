/*
 * shell.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "docs.h"
#include "../lib/utils.h"


/*
 * System start point.
 *
 * This method identify the command and action from the user input. After the identification, it
 * will pass the arguments to the correct function, so it could finish the processing.
 */
int main(int argc, char **argv) {

	parse(argc, argv);
	return EXIT_SUCCESS;

}

