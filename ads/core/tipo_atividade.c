/*
 * tipo_atividade.c
 */

#include <strings.h>
#include "tipo_atividade.h"
#include "database.h"


/*
 * Retornará um ponteiro para um vetor de ti>pos de atividades, finalizado com um ponteiro nulo.
 * Um ponteiro nulo será retornado caso ocorra algum erro.
 */
TipoAtividade **tipoListar() {

	return (TipoAtividade **) db_list(sizeof(TipoAtividade), tipoExtrair, "SELECT * FROM tipo_atividade");

}


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida.
 */
static int tipoExtrair(void *target, void **columnsData) {

	TipoAtividade *tipo = (TipoAtividade *) target;

	strcpy(tipo->codigo, columnsData[0]);
	tipo->descricao = rs_readStringOrNull(columnsData[1], tipo->descricao);

	return 0;

}
