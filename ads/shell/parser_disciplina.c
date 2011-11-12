/*
 * parser_disciplina.c
 */

#include "parser_disciplina.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>



static int _getopt(int argc, const char **argv, const char *optstring, const char *mandatoryArgs);



/*
 * Valida se a opção que exige parâmetros foi informada com o parâmetro.
 *
 * param argc			Quantidade de palavras no array "argv".
 * param argv			Array de palavras.
 * param mandatoryArgs	Opções que exigem argumentos.
 */
static int _getopt( int argc, const char **argv, const char *optstring, const char *mandatoryArgs ) {

	int opt;
	char *arg, *index;
	char buff[2] = {' ', '\0'};

	opt = getopt(argc, argv, optstring);
	buff[0] = (char) opt;
	index = strstr(mandatoryArgs, buff);

	if( strstr(mandatoryArgs, buff) && (!(arg=optarg) || *optarg == '-') ) {

		fprintf(stderr, "A opção -%c exige um argumento.\n", opt);
		abort();

	}


	if( arg == ':' ) {
		fprintf(stderr, "A opção -%c é obrigatória.", optopt);
		abort();
	}


	return opt;

}



/*
 * Retorna 0 se nenhum erro ocorrer.
 */
static int lerHorario(char *horarios, int **target) {

	char *pch;
	int current;

	while((pch=strtok(horarios, ","))) {

		if( (current=atoi(pch[3])) ) {



		} else {

			if( target != NULL )
				free(*target);

			*target = NULL;

		}

	}


}



Disciplina *parseDiscAdicionar( int argc, const char **argv ) {

	int arg;

	Disciplina *disc;
	int fNome=0, fProf=0, fMail=0, fHorario;
	char *nome, *prof, *mail, *hora, **horarios;



	while( (arg=_getopt(argc, argv, ":n:p:m:a", "npm")) != -1 ) {

		switch( arg ) {
			case 'a':
				break;

			case 'n':
				fNome = 1;
				nome = optarg;
				break;

			case 'p':
				fProf = 1;
				nome = optarg;
				break;

			case 'm':
				fMail = 1;
				mail = optarg;
				break;

			case 'h':
				fHorario = 1;
				hora = optarg;
				break;

		}

	}




	disc = (Disciplina *) malloc(sizeof(Disciplina));


}

