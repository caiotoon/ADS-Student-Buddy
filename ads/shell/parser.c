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
