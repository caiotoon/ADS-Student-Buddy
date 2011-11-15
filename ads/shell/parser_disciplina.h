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
 *
 * param argc		Número de argumentos no vetor argv
 * param argv		Argumentos passados para o programa argv
 * param horarios	Um ponteiro que apontará para um vetor de horários que foram
 * 					informados pelo usuário. Este ponteiro será apontado para um
 * 					vetor no caso do usuário ter informado ou será apontado para
 * 					NULL caso o usuário não tenha informado a opção 'h'.
 */
Disciplina *parseDiscAdicionar( int argc, const char **argv, int *horarios );



/**
 * Realiza a interpretação de edição de uma disciplina e retorna um ponteiro para
 * a disciplina.
 *
 * Na disciplina informada, as informações fornecidas pelo usuário deverão estar
 * preenchidas e as informações não fornecidas devem se mostrar como nulas. Os números
 * serão 0 e qualquer string será um ponteiro nulo.
 *
 * Um erro de parser deve parar imediatamente a execução do programa.
 *
 * param argc		Número de argumentos no vetor argv
 * param argv		Argumentos passados para o programa argv
 * param horarios	Um ponteiro que apontará para um vetor de horários que foram
 * 					informados pelo usuário. Este ponteiro será apontado para um
 * 					vetor no caso do usuário ter informado ou será apontado para
 * 					NULL caso o usuário não tenha informado a opção 'h'.
 */
Disciplina *parseDiscEditar( int argc, const char **argv, int *horarios );



/*
 * Retorna o código da disciplina que deve ser removida do banco de dados.
 *
 * Um erro de parser deve interromper a execução do programa imediatamente.
 */
int parseDiscRemover( int argc, char **argv );



#endif
