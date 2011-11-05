/*
 * disciplina.c
 */

#include "disciplina.h"
#include "database.h"
#include "../lib/utils.h"
#include <stdio.h>
#include <strings.h>
#include <malloc.h>


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

