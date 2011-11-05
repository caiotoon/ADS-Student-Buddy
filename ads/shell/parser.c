/*
 * parser.c
 */

#include "parser.h"
#include "docs.h"
#include <stdlib.h>
#include <string.h>
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
