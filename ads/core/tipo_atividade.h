/*
 * tipo_atividade.h
 */

struct TipoAtividade {

	char codigo[2];
	char *descricao;

};

typedef struct TipoAtividade TipoAtividade;



/*
 * Retornará um ponteiro para um vetor de tipos de atividades e colocará no ponteiro informado por
 * [qtde] o número de tipos de atividades neste vetor. Um ponteiro nulo será retornado caso ocorra
 * algum erro.
 */
TipoAtividade *tipoListar( int *qtde );
