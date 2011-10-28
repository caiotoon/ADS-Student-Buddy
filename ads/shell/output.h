/*
 * output.h
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <time.h>
#include "../core/atividade.h"
#include "../core/horario.h"
#include "../core/disciplina.h"
#include "../core/tipo_atividade.h"



/*
 * Escreve a lista de tipos disponíveis.
 *
 * param cont	número de itens no vetor informado.
 * param tipos	ponteiro para um vetor com os itens.
 */
void outListarTiposAtividades( int cont, TipoAtividade tipos[] );



/*
 * Escreve a lista de disciplinas disponíveis.
 *
 * param cont			número de itens no vetor informado.
 * param disciplinas	ponteiro para um vetor com os itens.
 */
void outListarDisciplinas( int cont, Disciplina disciplinas[] );



/*
 * Escreve a lista de horários disponíveis.
 *
 * param cont		número de itens no vetor informado.
 * param horarios	ponteiro para um vetor com os itens.
 */
void outListarHorarios( int cont, Horario horarios[] );


/*
 * Escreve a lista de atividades disponíveis.
 *
 * param cont		número de itens no vetor informado.
 * param atividades	ponteiro para um vetor com os itens.
 */
void outListarAtividades( int cont, Atividade atividades[] );


/*
 * Esvreve o cabeçalho do dia, com informação de data e cabeçalho.
 */
static void outEscreverCabecalhoDia( time_t dia );


/*
 * Escreve uma atividade completa.
 */
static void outEscrever(Atividade *atividade);


/*
 * Calcula a diferença entre uma data e a data atual do sistema e retorna uma string representando
 * esta diferença. A string será em dias, em semanas ou em meses. Exs.:
 *
 * hoje
 * ontem
 * há 5 dias
 * há 1 semana
 * há 2 semanas
 * daqui a 4 dias
 * daqui a 1 semana
 * daqui a mais de 6 meses
 * há mais de 6 meses
 */
static char *getDataRef( time_t data );



#endif /* OUTPUT_H_ */
