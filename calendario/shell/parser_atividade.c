/*
 * parser_atividade.c
 */

#include "parser_atividade.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "docs.h"
#include "../lib/date_utils.h"



/**
 * Parse an activity addition and returns a pointer to the activity strucuture 
 * created.
 *
 * An error must exit the program.
 */
Atividade *parseAtivAdicionar( int argc, const char **argv ) {

	Atividade *ativ;

	int opt;
	char *placer;
	int fTipo=0, fDisc=0, fData=0, fPontos=0, fTitulo=0;
	char *tipo, *titulo;
	int disc;
	float pontos;
	struct tm ___d;
	struct tm *data;
	time_t time_temp;
	int days, mons, years;



	while( (opt=opt_get(argc, argv, "tidnp", "atidnp", &placer)) != -1 ) {

		switch(opt) {

			case 't':
				fTipo = 1;
				tipo = placer;
				break;

			case 'i':
				fDisc = 1;
				disc = atoi(placer);
				break;

			case 'd':

				fData = strptime(placer, "%d-%m-%Y", &___d);

				if( !fData ) {
					fprintf(stderr, "O formato da data é inválido. Digite a data no formato dd-mm-aaaa.\n");
					exit(1);
				}

				time_temp = time(NULL);
				data = localtime(&time_temp);

				days = ___d.tm_mday;
				mons = ___d.tm_mon;
				years = ___d.tm_year;

				tmcpy(&___d, data);
				___d.tm_mday = days;
				___d.tm_mon = mons;
				___d.tm_year = years;

				break;

			case 'n':
				fTitulo = 1;
				titulo = placer;
				break;

			case 'p':
				fPontos = 1;
				pontos = atof(placer);
				break;

		}

	}


	if( !(fTipo && fDisc && fData && fTitulo && fPontos) ) {
		fprintf(stderr, "Todas as opções são obrigatórias. Digite 'calendario -h' para obter ajuda.\n");
		docAtiv(AC_ADICIONAR);
		exit(1);
	}


	ativ = (Atividade *) malloc(sizeof(Atividade));
	ativ->codigo = 0;
	ativ->data = mktime(&___d);
	ativ->titulo = titulo;
	ativ->descricao = NULL;
	ativ->disciplina = disc;
	ativ->pontos = pontos;
	strcpy(ativ->tipoAtividade, tipo);


	return ativ;

}



/*
 * Parse an activity edition command and returns the pointer to the structure mounted
 * by this function.
 *
 * In the mounted strucutre, the information sent by the user must be filled and the info
 * no sent must be nulled, where numbers will be 0 and string will become null pointers.
 *
 * A parser error must exit the program.
 */
Atividade *parseAtivEditar( int argc, const char **argv ) {

	Atividade *ativ;

	int opt;
	char *placer;
	int fTipo=0, fDisc=0, fData=0, fPontos=0, fTitulo=0;
	char *tipo, *titulo;
	int disc, codigo=0;
	float pontos;
	struct tm ___d;
	struct tm *data;
	time_t time_temp;
	int days, mons, years;


	while( (opt=opt_get(argc, argv, "tidnpc", "etidnpc", &placer)) != -1 ) {

		switch(opt) {

			case 't':
				fTipo = 1;
				tipo = placer;
				break;

			case 'i':
				fDisc = 1;
				disc = atoi(placer);
				break;

			case 'd':

				fData = strptime(placer, "%d-%m-%Y", &___d);

				if( !fData ) {
					fprintf(stderr, "O formato da data é inválido. Digite a data no formato dd-mm-aaaa.\n");
					exit(1);
				}

				time_temp = time(NULL);
				data = localtime(&time_temp);

				days = ___d.tm_mday;
				mons = ___d.tm_mon;
				years = ___d.tm_year;

				tmcpy(&___d, data);
				___d.tm_mday = days;
				___d.tm_mon = mons;
				___d.tm_year = years;

				break;

			case 'n':
				fTitulo = 1;
				titulo = placer;
				break;

			case 'p':
				fPontos = 1;
				pontos = atof(placer);
				break;

			case 'c':
				codigo = atoi(placer);
				break;

		}

	}


	if( !codigo ) {
		fprintf(stderr, "O código é obrigatório. Digite 'calendario -h' para obter ajuda.\n");
		docAtiv(AC_EDITAR);
		exit(1);
	}


	ativ = ativPegar(codigo);


	if( fData )
		ativ->data = mktime(&___d);

	if( fTitulo )
		ativ->titulo = titulo;

	if( fDisc )
		ativ->disciplina = disc;

	if( fPontos)
		ativ->pontos = pontos;

	if( fTipo )
		strcpy(ativ->tipoAtividade, tipo);



	return ativ;

}



/*
 * Returns the code to the activity that should be removed from the database.
 *
 * A parser error must stop the program.
 */
int parseAtivRemover( int argc, char **argv ) {

	int opt;
	char *placer;
	int codigo=0;


	while( (opt=opt_get(argc, argv, "c", "rc", &placer)) != -1 ) {

		switch(opt) {

			case 'c':
				codigo = atoi(placer);
				break;

		}

	}



	if( !codigo ) {
		fprintf(stderr, "O código é obrigatório. Digite 'calendario -h' para obter ajuda.\n");
		docAtiv(AC_REMOVER);
		exit(1);
	}

	return codigo;

}
