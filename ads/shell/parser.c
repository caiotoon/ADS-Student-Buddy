/*
 * parser.c
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "docs.h"
#include "../lib/utils.h"


const char ACOES[]					= {'a', 'e', 'l', 'r'};

const EAcao AC_VALIDAS_ATIVIDADE[] 	= {AC_ADICIONAR, AC_EDITAR, AC_REMOVER, -1};
const EAcao AC_VALIDAS_DISCIPLINA[] = {AC_ADICIONAR, AC_EDITAR, AC_LISTAR, AC_REMOVER, -1};
const EAcao AC_VALIDAS_TIPO_ATIV[]	= {AC_LISTAR, -1};
const EAcao AC_VALIDAS_HORARIO[]	= {AC_LISTAR, -1};




#define CONT_COMANDOS 10;
static char *COMANDOS[]		= {
	"disciplina",
	"atividade",
	"horario",
	"tipos",
	"ajuda",
	"ontem",
	"hoje",
	"amanha",
	"semana",
	"mes"
};

static EComando MAPA_COMANDOS[]	= {
	COM_DISCIPLINA,
	COM_ATIVIDADE,
	COM_HORARIO,
	COM_TIPO_ATIVIDADE,
	COM_AJUDA,
	COM_CONSULTA,
	COM_CONSULTA,
	COM_CONSULTA,
	COM_CONSULTA,
	COM_CONSULTA
};



/*
 * Identifica o comando baseado na lista de comandos existentes no vetor acima.
 */
EComando lerComando(char *comando) {

	int i, iLimit;

	strToLower(comando);
	iLimit = CONT_COMANDOS;

	for(i=0; i < iLimit; i++)
		if(!strcmp(comando, COMANDOS[i]))
			return MAPA_COMANDOS[i];


	escreverErro(ERR_COMANDO_NAO_IDENTIFICADO, NULL);
	return -1;

}



EAcao parseAcao( int argc, char **argv, const EAcao acoesPermitidas[] ) {

	return AC_EDITAR;

}


void parse(int argc, char **argv) {

	EComando com;
	EAcao acao;


	if( argc < 2 )
		escreverErro( ERR_SEM_COMANDO, NULL );

	// Identifica o comando.
	com = lerComando(argv[1]);

	if( com != COM_CONSULTA && argc < 3 )
		escreverErro( ERR_SEM_ACAO, NULL );


	switch( com ) {

		case COM_DISCIPLINA:
			puts("Comando de disciplina.");
			acao = parseAcao(argc, argv, AC_VALIDAS_DISCIPLINA);
			break;

		case COM_HORARIO:
			puts("Comando de horário.");
			acao = parseAcao(argc, argv, AC_VALIDAS_HORARIO);
			break;

		case COM_ATIVIDADE:
			puts("Comando de atividade.");
			acao = parseAcao(argc, argv, AC_VALIDAS_ATIVIDADE);
			break;

		case COM_TIPO_ATIVIDADE:
			puts("Comando de tipos de atividades.");
			acao = parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV);
			break;

		case COM_CONSULTA:
			puts("Comando de consulta.");
			//acao = parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV);
			acao = AC_LISTAR;
			break;

		case COM_AJUDA:
			puts("Comando de ajuda.");
			acao = AC_LISTAR;
			break;

	}

}




static int opt_current = 1;

int opt_get( int argc, const char **argv, const char *mandatoryOpts, const char *validOpts, char **argplacer ) {

	int opt;
	char *arg;
	char optNeedle[2] = {' ', '\0'};


	if( opt_current >= argc )
		return -1;

	for( ; opt_current < argc && *argv[opt_current] != '-'; opt_current++ );

	if( opt_current == argc ) {

		opt_reset();

		*argplacer = NULL;
		return -1;

	}

	opt = argv[opt_current][1];
	optNeedle[0] = opt;

	if( !strstr(validOpts, optNeedle) ) {
		fprintf(stderr, "Opção '-%c' não reconhecida.", opt);
		exit(1);
	}

	if( opt_current < argc-1 && *argv[opt_current+1] != '-' ) {

		*argplacer = argv[opt_current+1];
		opt_current += 2;

	} else {

		if( strstr(mandatoryOpts, optNeedle) ) {

			fprintf(stderr, "A opção -%c exige um argumento.\n", opt);
			exit(1);

		}

		*argplacer = NULL;
		opt_current++;

	}


	return opt;

}


void opt_reset( void ) {
	opt_current = 1;
}
