/*
 * atividade.c
 */

#include "atividade.h"

#include <stdlib.h>
#include <string.h>
#include "database.h"



/*
 * Adiciona uma nova atividade no banco e preenche o ID da atividade apontada.
 * Retorna 0 se nenhum erro ocorrer e algum número diferente disso em caso de erros.
 */
int ativAdicionar( Atividade *atividade ) {

	char query[1024*5];
	char sqlTemplate[] =
		" INSERT INTO atividade(codtipoatividade, coddisc, nome, data, pontos, descricao) "
		"	VALUES('%s', %d, '%s', strftime('%%Y-%%m-%%d', %d, 'unixepoch'), %f, '%s'); ";


	sprintf(query, sqlTemplate, atividade->tipoAtividade, atividade->disciplina, atividade->titulo
			, atividade->data, atividade->pontos, atividade->descricao);
	db_query(NULL, NULL, query);

	atividade->codigo = db_getLastInsertId();


	return atividade;

}


/*
 * Atualiza uma entidade no banco de dados. Todas as informações serão alteradas no banco.
 * Retorna 0 se nenhum erro ocorrer e um valor diferente deste no caso contrário.
 */
int ativAtualizar( const Atividade *atividade ) {

	int result;
	char *titulo, *descricao;
	const size_t charSize = sizeof(char);
	char query[1024*5];
	const char *sqlTemplate =
		"	UPDATE atividade SET "
		"		nome = %s, "
		"		descricao = %s, "
		"		data = strftime('%%Y-%%m-%%d', %d, 'unixepoch'), "
		"		pontos = %f, "
		"		codtipoatividade = '%s', "
		"		coddisc = %d "
		"	WHERE codatividade = %d; ";

	titulo = rs_prepareStringOrNull(atividade->titulo);
	descricao = rs_prepareStringOrNull(atividade->descricao);


	sprintf(query, sqlTemplate, titulo, descricao, atividade->data, atividade->pontos,
		atividade->tipoAtividade, atividade->disciplina, atividade->codigo);
	result = db_query(NULL, NULL, query);


	free(titulo);
	free(descricao);

	return result != SQLITE_OK;

}


/*
 * Procura no banco a atividade que possui o ID informado e retorna um ponteiro para a entidade
 * recuperada. Caso uma atividade não seja encontrada com este ID, um ponteiro nulo será retornado.
 */
Atividade *ativPegar( int codAtividade ) {

	Atividade **ativs, *ativ;

	char sqlTemplate[] =
		" SELECT codatividade, nome, descricao, data, pontos, codtipoatividade, coddisc "
		" 	FROM atividade "
		"	WHERE codatividade = %d; ";

	char query[strlen(sqlTemplate)+40];
	sprintf(query, sqlTemplate, codAtividade);

	ativs = db_list(sizeof(Atividade), ativExtrair, query);
	ativ = *ativs;
	free(ativs);

	return ativ;

}


/*
 * Consulta todas as atividades compreendidas em ume escopo de datas.
 *
 * Retornará um ponteiro para um vetor de atividades finalizado por um ponteiro nulo. Um ponteiro
 * nulo será retornado caso ocorra algum erro.
 */
Atividade **ativListar( time_t dataInicial, time_t dataFinal ) {

	char sqlTemplate[] =
		" SELECT codatividade, nome, descricao, data, pontos, codtipoatividade, coddisc"
		" 	FROM atividade "
		"	WHERE data BETWEEN strftime('%%Y-%%m-%%d', %d, 'unixepoch') AND strftime('%%Y-%%m-%%d', %d, 'unixepoch') "
		"	ORDER BY data, coddisc, nome; ";

	char query[strlen(sqlTemplate)+40];


	sprintf(query, sqlTemplate, dataInicial, dataFinal);
	return db_list(sizeof(Atividade), ativExtrair, query);

}


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida por esta função.
 */
static int ativExtrair(void *target, void **columnsData) {

	Atividade *atividade = (Atividade *) target;

	atividade->codigo = atoi(columnsData[0]);
	atividade->titulo = rs_readStringOrNull(columnsData[1], atividade->titulo);
	atividade->descricao = rs_readStringOrNull(columnsData[2], atividade->descricao);
	atividade->data = atoi(columnsData[3]);
	atividade->pontos = atof(columnsData[4]);
	strcpy(atividade->tipoAtividade, columnsData[5]);
	atividade->disciplina = atoi(columnsData[6]);

	return 0;

}


/*
 * Remove uma atividade do banco de dados e retorna 0 se nenhum erro ocorrer. Retorna um valor
 * diferente de 0 no caso de erros.
 */
int ativRemover( int codAtividade ) {

	char query[70];

	sprintf(query, "DELETE FROM atividade WHERE codatividade = %d;", codAtividade);
	return db_query(NULL, NULL, query) != SQLITE_OK;

}
