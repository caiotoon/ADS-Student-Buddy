/*
 * disciplina.h
 */

#ifndef _DISCIPLINA_H
#define _DISCIPLINA_H



struct _Disciplina {

	int codigo;
	char *nome;
	char *professor;
	char *email;

};

typedef struct _Disciplina Disciplina;




/*
 * Adds a new discipline to the database and fill the discipline's ID .
 * Returns 0 if no error is found or a different number otherwise.
 */
int discAdicionar( Disciplina *disciplina );


/*
 * Update an entity on the database. All attributes will be persisted overwriting the current.
 * Returns 0 if no error is found or a different number otherwise.
 */
int discAtualizar( const Disciplina *disciplina );


/*
 * Search a discipline in the database that matches the ID and returns a pointer to that entity.
 * In case a discipline is not found, a null pointer will be returned.
 */
Disciplina *discPegar( int codigo );


/*
 * Return a pointer to the disciplines array ended by a null pointer. A null pointer
 * will be returned in case of error.
 */
Disciplina **discListar( void );


/*
 * Extract a row from a resultset and put it to the memory pointed by "target"
 * It's expected that this function knows the column order.
 */
static int discExtrair(void *target, void **columnsData);


/*
 * Removes a discipline from the database and return 0 if no error occur, a different number otherwise.
 */
int discRemover( int codigo );


/*
 * Free all the memory allocated by a discipline.
 */
int discRelease( void *target );


#endif
