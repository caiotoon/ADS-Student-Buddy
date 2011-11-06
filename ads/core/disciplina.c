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


Disciplina **discListar() {

	return db_list(sizeof(Disciplina), discExtrair, "SELECT * FROM disciplina");

}



Disciplina *discPegar(int codigo) {

	Disciplina **result, *disc;

	char sql[100];

	snprintf(sql, 100, "SELECT coddisc, nome, nome_prof, email_prof FROM disciplina WHERE coddisc = %d;", codigo);
	result = (Disciplina **) db_list(sizeof(Disciplina), discExtrair, sql);

	disc = *result;
	free(result);

	return disc;

}



static int discExtrair(void *target, void **columnsData) {

	Disciplina *disc = (Disciplina *) target;

	disc->codigo = atoi(columnsData[0]);
	disc->nome = (char *) malloc(sizeof(char) * (strlen(columnsData[1])+2));
	disc->professor = (char *) malloc(sizeof(char) * (strlen(columnsData[2])+2));
	disc->email = (char *) malloc(sizeof(char) * (strlen(columnsData[3])+1));;

	strcpy(disc->nome, columnsData[1]);
	strcpy(disc->professor, columnsData[2]);
	strcpy(disc->email, columnsData[3]);

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

	sprintf(query, "DELETE FROM disciplina WHERE coddisc = %d;", codigo);

	return db_query(NULL, NULL, query) != SQLITE_OK;

}


