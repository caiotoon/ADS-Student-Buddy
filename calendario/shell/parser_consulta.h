/*
 * parser_consulta.h
 */

#ifndef PARSER_CONSULTA_H_
#define PARSER_CONSULTA_H_

#include <time.h>

/*
 * Parse a schedule query and write the start and end date to the pointers informed.
 */
void parseCons( int argc, char **argv, time_t *dataInicial, time_t *dataFinal );


#endif /* PARSER_CONSULTA_H_ */
