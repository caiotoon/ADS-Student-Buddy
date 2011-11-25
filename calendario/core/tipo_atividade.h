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
 * Retornará um ponteiro para um vetor de tipos de atividades finalizado com um ponteiro nulo.
 * Um ponteiro nulo será retornado caso ocorra algum erro.
 */
TipoAtividade **tipoListar();


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida por esta função.
 */
static int tipoExtrair(void *target, void **columnsData);



#endif
