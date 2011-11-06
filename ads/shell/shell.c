/*
 * shell.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "docs.h"
#include "../lib/utils.h"
#include "../test/tests.h"


/*
 * Ponto de entrada do programa.
 *
 * Este método tem a responsabilidade de identificar o comando e a ação da linha de código. Após a identificação,
 * ele deve passar os argumentos para a função adequada, a fim de finalizar o pedido.
 */
int main(int argc, char **argv) {

	//parse(argc, argv);


//	setHorarios();
//	exit(0);

//	traceAllAtivs();
//	traceAllDiscs();
//	traceAllHorarios();
	testHorarios(FALSE);

	return EXIT_SUCCESS;

}
