/*
 * tipo_atividade.c
 */

#include <string.h>
#include "tipo_atividade.h"
#include "database.h"


/*
 * Retornará um ponteiro para um vetor de tipos de atividades, finalizado com um ponteiro nulo.
 * Um ponteiro nulo será retornado caso ocorra algum erro.
 */
TipoAtividade **tipoListar() {

	TipoAtividade sample;
	return (TipoAtividade **) db_list(&sample, tipoExtrair, "SELECT * FROM tipo_atividade");

}


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida.
 */
static int tipoExtrair(void *target, void **columnsData) {

	TipoAtividade *tipo = (TipoAtividade *) target;

	strcpy(tipo->codigo, columnsData[0]);
	tipo->descricao = malloc(sizeof(strlen(columnsData[1])));
	strcpy(tipo->descricao, columnsData[1]);

	return 0;

}
