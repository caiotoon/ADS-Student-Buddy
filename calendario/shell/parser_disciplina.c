/*
 * parser_disciplina.c
 */

#include "parser_disciplina.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <malloc.h>

#include "parser.h"
#include "docs.h"







/*
 * Returns 0 if no error happens.
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

	int opt;

	Disciplina *disc;
	int fName=0, fProf=0, fMail=0, fHorario=0;
	char *name, *prof, *mail, *hora;
	char *placer;



	while( (opt=opt_get(argc, argv, "npm", "anpmh", &placer)) != -1 ) {

		switch( opt ) {
			case 'a':
				break;

			case 'n':
				fName = 1;
				name = placer;
				break;

			case 'p':
				fProf = 1;
				prof = placer;
				break;

			case 'm':
				fMail = 1;
				mail = placer;
				break;

			case 'h':
				fHorario = 1;
				hora = placer;
				break;

		}

	}


	if( !(fName && fProf && fMail) ) {
		fprintf(stderr, "As opções -m -p e -n são obrigatórias. Digite \"calendario -h\" para obter ajuda.\n");
		docDisc(AC_ADICIONAR);
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



Disciplina *parseDiscEditar( int argc, const char **argv, int **horarios ) {

	int opt;

	Disciplina *disc;
	int fName=0, fProf=0, fMail=0, fHorario=0;
	int codigo=0;
	char *name, *prof, *mail, *hora;
	char *placer;



	while( (opt=opt_get(argc, argv, "npmc", "enpmhc", &placer)) != -1 ) {

		switch( opt ) {
			case 'e':
				break;

			case 'n':
				fName = 1;
				name = placer;
				break;

			case 'p':
				fProf = 1;
				prof = placer;
				break;

			case 'm':
				fMail = 1;
				mail = placer;
				break;

			case 'h':
				fHorario = 1;
				hora = placer;
				break;

			case 'c':
				codigo = atoi(placer);
				break;

		}

	}


	if( !codigo ) {
		fprintf(stderr, "A opção -c é obrigatória. Digite \"calendario -h\" para obter ajuda.\n");
		docDisc( AC_EDITAR );
		exit(1);
	}


	disc = discPegar(codigo);

	if( !disc ) {
		fprintf(stderr, "Não existe uma disciplina com o código %d.\n", codigo);
		exit(1);
	}


	if( fName )
		disc->nome = name;

	if( fProf )
		disc->professor = prof;

	if( fMail )
		disc->email = mail;


	if( fHorario && hora )
		*horarios = lerHorario(hora);

	else
		*horarios = NULL;



	return disc;

}


int parseDiscRemover( int argc, char **argv ) {

	int opt;

	int codigo=0;
	char *placer;



	while( (opt=opt_get(argc, argv, "c", "rc", &placer)) != -1 ) {

		switch( opt ) {

			case 'd':
				break;

			case 'c':
				codigo = atoi(placer);
				break;

		}

	}


	if( !codigo ) {
		fprintf(stderr, "O código é obrigatório.\n");
		docDisc(AC_REMOVER);
		exit(1);
	}



	return codigo;

}

