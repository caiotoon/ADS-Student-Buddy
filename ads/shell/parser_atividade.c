/*
 * parser_atividade.c
 */

#include "parser_atividade.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "../lib/date_utils.h"



/**
 * Realiza a interpretação de adição de uma atividade e retorna um ponteiro
 * para a atividade montada.
 *
 * Um erro deve interromper o programa imediatamente.
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
					fprintf(stderr, "O formato da data é inválido. Digite a data no formato dd-mm-aaaa.");
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
		fprintf(stderr, "Todas as opções são obrigatórias. Digite 'ads ajuda' para obter ajuda.\n");
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
 * Realiza a interpretação de edição de uma atividade e retorna um ponteiro para
 * a atividade.
 *
 * Na atividade informada, as informações fornecidas pelo usuário deverão estar
 * preenchidas e as informações não fornecidas devem se mostrar como nulas. Os números
 * serão 0 e qualquer string será um ponteiro nulo.
 *
 * Um erro de parser deve parar imediatamente a execução do programa.
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
					fprintf(stderr, "O formato da data é inválido. Digite a data no formato dd-mm-aaaa.");
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
		fprintf(stderr, "O código é obrigatório. Digite 'ads ajuda' para obter ajuda.\n");
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
 * Retorna o código da atividade que deve ser removida do banco de dados.
 *
 * Um erro de parser deve interromper a execução do programa imediatamente.
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
		fprintf(stderr, "O código é obrigatório. Digite 'ads ajuda' para obter ajuda.\n");
		exit(1);
	}

	return codigo;

}
