/*
 * tipo_atividade.h
 */

#ifndef TIPO_ATIVIDADE_H
#define TIPO_ATIVIDADE_H



struct TipoAtividade {

	char codigo[3];
	char *descricao;

};

typedef struct TipoAtividade TipoAtividade;


/*
 * Returns a pointer to the vector of activity types ended by a null pointer.
 * A null pointer will be returned in case of error.
 */
TipoAtividade **tipoListar();


/*
 * Extract a row from the resultset to the memory pointed by [target].
 * It's expected that the order of the columns is know by this function.
 */
static int tipoExtrair(void *target, void **columnsData);



#endif
