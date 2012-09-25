/*
 * parser_disciplina.h
 */

#ifndef _PARSER_DISCIPLINA_H
#define _PARSER_DISCIPLINA_H



#include "../core/disciplina.h"

/**
 * Parse the addition of a discipline and returns a pointer to a discipline structure.
 *
 * In case of error the system must exit.
 *
 * param argc		
 * param argv		
 * param horarios	A pointer that will point to a schedule array that has been 
 * 					informed by the user. If the user has not informed any schedule, 
 * 					then a null pointer is returned.
 */
Disciplina *parseDiscAdicionar( int argc, const char **argv, int **horarios );



/**
 * Parse the edition of a discipline and returns a pointer to the structure that holds the
 * discipline informed by the user.
 *
 * All info passed by the user should be present on the returned structure, and the missing
 * must be a null pointer when a string or a 0 when a number.
 *
 * In case of error the system must exit.
 *
 * param argc		
 * param argv		
 * param horarios	A pointer that will point to a schedule array that has been 
 * 					informed by the user. If the user has not informed any schedule, 
 * 					then a null pointer is returned.
 */
Disciplina *parseDiscEditar( int argc, const char **argv, int **horarios );



/*
 * Returns the code of the discipline that should be removed from the database.
 * In case of error the system must exit.
 */
int parseDiscRemover( int argc, char **argv );



#endif
