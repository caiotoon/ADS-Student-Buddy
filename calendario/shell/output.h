/*
 * output.h
 *
 * Concentrate all output messages, except for errors.
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <time.h>
#include "../core/atividade.h"
#include "../core/horario.h"
#include "../core/disciplina.h"
#include "../core/tipo_atividade.h"



/*
 * Write the type of activities informed.
 *
 * param tipos	pointer to the types that should be listed.
 */
void outListarTiposAtividades( const TipoAtividade **tipos );



/*
 * Write the discipline informed.
 *
 * param disciplinas	a pointer the disciplines that should be listed.
 */
void outListarDisciplinas( const Disciplina **disciplinas );



/*
 * Write the schedules informed.
 *
 * param horarios	pointer to the schedules that should be listed.
 */
void outListarHorarios( const Horario **horarios );


/*
 * Write a list with all available activities.
 *
 * param atividades	pointer to the activities that should be listed.
 */
void outListarAtividades( const time_t *dataInicial, const time_t *dataFinal, const Atividade **atividades );


/*
 * Writes the header of the day.
 */
static void outEscreverCabecalhoDia( const time_t *dia );


/*
 * Writes a complete activity.
 */
static void outEscreverAtividade(const Atividade *atividade);


/*
 * Calculates the difference between a specific date and the system date and writes a string representing the relative time between them.
 * The string will be written to the [target] pointer, and the possible values are:
 *
 * hoje (today)
 * ontem (yesterday)
 * há 5 dias (5 days ago)
 * há 1 semana (1 week ago)
 * há 2 semanas (2 weeks ago)
 * daqui a 4 dias (in 4 days)
 * daqui a 1 semana (in 1 week)
 * daqui a mais de 6 meses (6+ months ahead)
 * há mais de 6 meses (6+ months ago)
 */
static void getDataRef( const time_t *data, char *target );



#endif /* OUTPUT_H_ */
