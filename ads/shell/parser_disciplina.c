/*
 * parser_disciplina.c
 */

#include "parser_disciplina.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <malloc.h>



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
int *lerHorario(const char *horarios) {

	char *source, *pch, hor[4];
	int *currPlace, current, horPosition, cont;
	int *result = (int *) malloc(sizeof(int *));

	source = (char *) malloc(sizeof(char) * (strlen(horarios)+1));
	strcpy(source, horarios);

	cont = 0;
	hor[3] = '\0';

	pch=strtok(source, ",");

	while(pch != NULL) {

		if( strlen(pch) != 4 ) {
			fprintf(stderr, "Não foi possível compreender o horário '%s'.\n", pch);
			exit(1);
		}

		if( (horPosition=atoi(&pch[3])) ) {

			if( horPosition > 2 || horPosition < 1 ) {
				fprintf(stderr, "Os horários possíveis são apenas 1 ou 2.\n");
				exit(1);
			}

			strncpy(hor, pch, 3);

			if( !strcmp(hor, "seg") )
				current = 1;
			else if( !strcmp(hor, "ter") )
				current = 3;
			else if( !strcmp(hor, "qua") )
				current = 5;
			else if( !strcmp(hor, "qui") )
				current = 7;
			else if( !strcmp(hor, "sex") )
				current = 9;
			else {
				fprintf(stderr, "Não foi possível compreender o horário '%s'.\n", hor);
				exit(1);
			}


			if( horPosition == 2 )
				current++;

			result = (int *) realloc(result, sizeof(int)*(cont+1));
			result[cont] = current;
			cont++;

			pch=strtok(NULL, ",");

		}

	}


	result = (int *) realloc(result, sizeof(int)*(cont+1));
	result[cont] = 0;
	free(source);

	return result;

}



Disciplina *parseDiscAdicionar( int argc, const char **argv, int **horarios ) {

	int arg;

	Disciplina *disc;
	int fName=0, fProf=0, fMail=0, fHorario=0;
	char *name, *prof, *mail, *hora;



	while( (arg=_getopt(argc, argv, ":n:p:m:h::a", "npm")) != -1 ) {

		switch( arg ) {
			case 'a':
				break;

			case 'n':
				fName = 1;
				name = optarg;
				break;

			case 'p':
				fProf = 1;
				prof = optarg;
				break;

			case 'm':
				fMail = 1;
				mail = optarg;
				break;

			case 'h':
				fHorario = 1;
				printf("O ARGUMENTO ERA: %s\n", optarg);
				if( optarg && *optarg != '-' )
					hora = optarg;
				else {
					hora = NULL;
				}


				break;

		}

	}


	if( !(fName && fProf && fMail) ) {
		fprintf(stderr, "As opções -m -p e -n são obrigatórias. Digite \"ads ajuda\" para obter ajuda.");
		exit(1);
	}


	if( fHorario && hora )
		*horarios = lerHorario(hora);

	else
		*horarios = NULL;


	disc = (Disciplina *) malloc(sizeof(Disciplina));
	disc->email = mail;
	disc->nome = name;
	disc->professor = prof;

	return disc;

}

