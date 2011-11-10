/*
 * output.h
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#ifndef SECS_IN_DAY
#define SECS_IN_DAY 86400
#endif

#include <time.h>
#include "../core/atividade.h"
#include "../core/horario.h"
#include "../core/disciplina.h"
#include "../core/tipo_atividade.h"



/*
 * Escreve a lista de tipos disponíveis.
 *
 * param tipos	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarTiposAtividades( const TipoAtividade **tipos );



/*
 * Escreve a lista de disciplinas disponíveis.
 *
 * param disciplinas	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarDisciplinas( const Disciplina **disciplinas );



/*
 * Escreve a lista de horários disponíveis.
 *
 * param horarios	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarHorarios( const Horario **horarios );


/*
 * Escreve a lista de atividades disponíveis.
 *
 * param atividades	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarAtividades( const Atividade **atividades );


/*
 * Escreve o cabeçalho do dia, com informação de data e cabeçalho.
 */
static void outEscreverCabecalhoDia( const time_t *dia );


/*
 * Escreve uma atividade completa.
 */
static void outEscreverAtividade(const Atividade *atividade);


/*
 * Calcula a diferença entre uma data e a data atual do sistema e escreve uma string representando
 * esta diferença no argumento "target". A string será em dias, em semanas ou em meses. Exs.:
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
static void getDataRef( const time_t *data, char *target );



#endif /* OUTPUT_H_ */
