/*
 * parser_disciplina.h
 */

#ifndef _PARSER_DISCIPLINA_H
#define _PARSER_DISCIPLINA_H



#include "../core/disciplina.h"

/**
 * Realiza a interpretação de adição de uma disciplina e retorna um ponteiro
 * para a disciplina montada.
 *
 * Um erro deve interromper o programa imediatamente.
 */
Disciplina *parseDiscAdicionar( int argc, char **argv );



/**
 * Realiza a interpretação de edição de uma disciplina e retorna um ponteiro para
 * a disciplina.
 *
 * Na disciplina informada, as informações fornecidas pelo usuário deverão estar
 * preenchidas e as informações não fornecidas devem se mostrar como nulas. Os números
 * serão 0 e qualquer string será um ponteiro nulo.
 *
 * Um erro de parser deve parar imediatamente a execução do programa.
 */
Disciplina *parseDiscEditar( int argc, char **argv );



/*
 * Retorna o código da disciplina que deve ser removida do banco de dados.
 *
 * Um erro de parser deve interromper a execução do programa imediatamente.
 */
int parseDiscRemover( int argc, char **argv );


#endif
