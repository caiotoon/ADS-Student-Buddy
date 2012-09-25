/*
 * parser_atividade.h
 */

#ifndef _PARSER_ATIVIDADE_H
#define _PARSER_ATIVIDADE_H



#include "../core/atividade.h"

/**
 * Parse an activity addition and returns a pointer to the activity strucuture 
 * created.
 *
 * An error must exit the program.
 */
Atividade *parseAtivAdicionar( int argc, const char **argv );



/*
 * Parse an activity edition command and returns the pointer to the structure mounted
 * by this function.
 *
 * In the mounted strucutre, the information sent by the user must be filled and the info
 * no sent must be nulled, where numbers will be 0 and string will become null pointers.
 *
 * A parser error must exit the program.
 */
Atividade *parseAtivEditar( int argc, const char **argv );



/*
 * Returns the code to the activity that should be removed from the database.
 *
 * A parser error must stop the program.
 */
int parseAtivRemover( int argc, char **argv );


#endif
