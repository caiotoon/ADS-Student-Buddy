/*
 * docs.h
 */

enum DocErro {
	ERR_SEM_COMANDO,
	ERR_SEM_ACAO,
	ERR_EXCESSO_PARAMETROS,
	ERR_FALTA_PARAMETROS,
	ERR_COMANDO_NAO_IDENTIFICADO
};

typedef enum DocErro EDocErro;




/**
 * Escreve a ajuda na tela.
 */
void escreverDoc();



/**
 * Escreve um erro na tela.
 *
 * Apenas determinados tipos de erros irão recorrer ao ponteiro de argumentos adicionais. E estes já saberão o que há no
 * endereço informado.
 */
void escreverErro( EDocErro erro, char *args[] );


