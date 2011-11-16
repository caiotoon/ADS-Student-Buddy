/*
 * disciplina.c
 */

#include "disciplina.h"

#include <stdio.h>
#include <strings.h>
#include <malloc.h>

#include "database.h"
#include "../lib/utils.h"
#include "../lib/sqlite3.h"



// Declara a estrutura que irá conter a lista de disciplinas lá carregadas.

struct {

	int length;
	Disciplina **discs;

} DISCIPLINAS;


/*
 * Busca uma disciplina no array. Os algoritimos de ordenação e pesquisa precisam
 * ser melhorados no futuro.
 */
static Disciplina *searchDisciplina( int codigo ) {

	register int i, iLimit;

	iLimit = DISCIPLINAS.length;
	for(i=0; i<iLimit; i++)
		if( DISCIPLINAS.discs[i]->codigo == codigo )
			return DISCIPLINAS.discs[i];


	return NULL;

}

static void addDisciplina( Disciplina *disc ) {

	if( DISCIPLINAS.length == 0 )
		DISCIPLINAS.discs = (Disciplina *) malloc(sizeof(Disciplina));

	else
		DISCIPLINAS.discs = realloc(DISCIPLINAS.discs, sizeof(Disciplina)*DISCIPLINAS.length);


	DISCIPLINAS.discs[DISCIPLINAS.length] = disc;
	DISCIPLINAS.length++;

}


Disciplina **discListar() {
	return db_list(sizeof(Disciplina), discExtrair, "SELECT * FROM disciplina");
}



Disciplina *discPegar(int codigo) {

	Disciplina **result, *disc;

	if( (disc=searchDisciplina(codigo)) )
		return disc;


	char sql[100];

	snprintf(sql, 100, "SELECT coddisc, nome, nome_prof, email_prof FROM disciplina WHERE coddisc = %d;", codigo);
	result = (Disciplina **) db_list(sizeof(Disciplina), discExtrair, sql);

	disc = *result;

	if( !disc ) {
		fprintf(stderr, "Não foi encontrada a disciplina com o código %d.\n", codigo);
		exit(1);
	}


	free(result);
	addDisciplina(disc);


	return disc;

}



static int discExtrair(void *target, void **columnsData) {

	Disciplina *disc = (Disciplina *) target;

	disc->codigo = atoi(columnsData[0]);
	disc->nome = rs_readStringOrNull(columnsData[1], disc->nome);
	disc->professor = rs_readStringOrNull(columnsData[2], disc->professor);
	disc->email = rs_readStringOrNull(columnsData[3], disc->email);

	return 0;

}


int discAdicionar( Disciplina *disciplina ) {

	char sqlTemplate[] =
		" INSERT INTO disciplina	"
		"	(nome, nome_prof, email_prof) "
		"	VALUES('%s', '%s', %s);	";

	char email[300];
	char query[5000];

	sprintf(email, disciplina->email == NULL ? "NULL" : "'%s'", disciplina->email);
	sprintf(query, sqlTemplate, disciplina->nome, disciplina->professor, email);

	if( db_query(NULL, NULL, query) != SQLITE_OK )
		return 1;

	disciplina->codigo = db_getLastInsertId();

	return 0;

}


int discAtualizar( const Disciplina *disciplina ) {

	char sqlTemplate[] =
		"UPDATE disciplina SET "

		"	nome = '%s', "
		"	nome_prof = '%s', "
		"	email_prof = %s "

		"	WHERE coddisc = %d";

	char email[300];
	char query[5000];

	sprintf(email, disciplina->email == NULL ? "NULL" : "'%s'", disciplina->email);
	sprintf(query, sqlTemplate, disciplina->nome, disciplina->professor, email, disciplina->codigo);


	return db_query(NULL, NULL, query) != SQLITE_OK;

}


int discRemover( int codigo ) {

	char query[70];

	sprintf(query, "DELETE FROM atividade WHERE coddisc = %d;", codigo);

	if( db_query(NULL, NULL, query) == SQLITE_OK ) {

		sprintf(query, "DELETE FROM disciplina WHERE coddisc = %d;", codigo);
		return db_query(NULL, NULL, query) != SQLITE_OK;

	} else
		return 1;

}


