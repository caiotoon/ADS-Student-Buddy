/*
 * horario.h
 */

#ifndef _HORARIO_H
#define _HORARIO_H



#include "disciplina.h"
#include <time.h>

/*
 * Every function that returns a schedule must associate the discipline to the schedule or put
 * a null pointer as [disciplina] to indicate that no discipline is associated to that schedule.
 */

struct _Horario {

	int codigo;
	char diaSemana[4];
	Disciplina *disciplina;
	time_t horaInicial;
	time_t horaFinal;

};

typedef struct _Horario Horario;



/*
 * Returns a pointer to a vector of schedules ended by a null pointer. A null pointer will be returned in case any
 * error occur.
 */
Horario **horaListar(void);


/*
 * Extracts a row from the resultset to the memory pointed by "target".
 * It's expected that this function know the resultset columns.
 */
static int horaExtrair(void *target, void **columnsData);


/*
 * Bind a discipline to a specific schedule and returns 0 if no error occurs.
 *
 * In case of [codDisciplina] is 0, any discipline binded to that schedule will be 
 * unbind.
 */
int horaAssociarDisciplina( int codHorario, int codDisciplina );



/*
 * Unbind a discipline from any schedule it may be bound.
 */
int horaDesassociarDisciplina( int codDisciplina );


/*
 * Returns an schedule based on the week day and the schedule position. [diaSemana] will be an array of chars that
 * will contain the three first letters of the week day (Brazillian (from monday): seg, ter, qua, qui, sex), and [horario]
 * must be 1 or 2, indicating, respectively, the first or second schedule time. The query must be done according to the 
 * start and end time of the class.
 *
 * A null pointer will be returned if its not possible to find the schedule specified.
 */
Horario *horaPegar( const char diaSemana[4], int horario );


/*
 * Writes the time in the format HH:MM. If a [destino] is pointed, the result will be
 * written direct to this pointer. If not, the memory will be allocated and a pointer to
 * it will be returned. In the second option, the responsability of deallocating the memory
 * is from the caller of this method.
 */
char *horaEscreverHora( const time_t horaUnix, char *destino );


#endif
