/*
 * tipo_atividade.c
 */

#include <strings.h>
#include "tipo_atividade.h"
#include "database.h"


/*
 * Returns a pointer to the vector of activity types ended by a null pointer.
 * A null pointer will be returned in case of error.
 */
TipoAtividade **tipoListar() {

	return (TipoAtividade **) db_list(sizeof(TipoAtividade), tipoExtrair, "SELECT * FROM tipo_atividade");

}


/*
 * Extract a row from the resultset to the memory pointed by [target].
 * It's expected that the order of the columns is know by this function.
 */
static int tipoExtrair(void *target, void **columnsData) {

	TipoAtividade *tipo = (TipoAtividade *) target;

	strcpy(tipo->codigo, columnsData[0]);
	tipo->descricao = rs_readStringOrNull(columnsData[1]);

	return 0;

}
