/*
 * docs.h
 */

#ifndef _DOCS_H
#define _DOCS_H

#include "parser.h"



enum DocErro {
	ERR_SEM_COMANDO,
	ERR_SEM_ACAO,
	ERR_EXCESSO_PARAMETROS,
	ERR_FALTA_PARAMETROS,
	ERR_COMANDO_NAO_IDENTIFICADO
};

typedef enum DocErro EDocErro;




/**
 * Writes the help on console.
 */
void escreverDoc();



/**
 * Writes a generic error on console.
 *
 * [args] are options that might be needed for a specific kind of error.
 */
void escreverErro( EDocErro erro, char *args[] );


void docHora( EAcao acao );
void docTipo( EAcao acao );
void docDisc( EAcao acao );
void docAtiv( EAcao acao );



#endif
