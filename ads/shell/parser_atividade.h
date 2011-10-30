/*
 * parser_atividade.h
 */

#ifndef _PARSER_ATIVIDADE_H
#define _PARSER_ATIVIDADE_H



#include "../core/atividade.h"

/**
 * Realiza a interpretação de adição de uma atividade e retorna um ponteiro
 * para a atividade montada.
 *
 * Um erro deve interromper o programa imediatamente.
 */
Atividade *parseAtivAdicionar( int argc, char **argv );



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
Atividade *parseAtivEditar( int argc, char **argv );



/*
 * Retorna o código da atividade que deve ser removida do banco de dados.
 *
 * Um erro de parser deve interromper a execução do programa imediatamente.
 */
int parseAtivRemover( int argc, char **argv );


#endif
