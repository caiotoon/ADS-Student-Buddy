/*
 * atividade.h
 */

#ifndef _ATIVIDADE_H
#define _ATIVIDADE_H


#include <time.h>

struct _Atividade {

	int codigo;
	char *titulo;
	char *descricao;
	time_t data;
	float pontos;

	char tipoAtividade[3];
	int disciplina;
	int horario; // 0 indicates that there is no classes of this activity.

};

typedef struct _Atividade Atividade;




/*
 * Adds a new activity to the database and fill the ID of the activity pointed by [atividade].
 * Returns 0 if no error occur, and a different number otherwise.
 */
int ativAdicionar( Atividade *atividade );


/*
 * Update a entity in the database. All properties will be persisted.
 * Returns 0 if no error occur, and a different number otherwise.
 */
int ativAtualizar( const Atividade *atividade );


/*
 * Search the database for an activity that matches the ID informed and return a pointer to the found one.
 * If no activity has been found, a null pointer will be returned.
 */
Atividade *ativPegar( int codAtividade );


/*
 * Query all activities in a date interval.
 *
 * Returns the pointer to a vector with all activities ended by a null pointer. A null pointer will
 * be returned in case of errors.
 */
Atividade **ativListar( const time_t *dataInicial, const time_t *dataFinal );


/*
 * Extract a row from the resultset to the memory pointed by [target].
 * It's expected that this function knows the resultset columns.
 */
static int ativExtrair(void *target, void **columnsData);


/*
 * Removes an activity from the database and returns 0 if no error occurs, a different number will
 * be returned otherwise.
 */
int ativRemover( int codAtividade );



#endif
