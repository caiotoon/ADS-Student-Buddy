/*
 * horario.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "database.h"
#include "horario.h"
#include "disciplina.h"




Horario **horaListar(void) {
	return (Horario **) db_list(sizeof(Horario), horaExtrair, "SELECT codhorario, coddiasemana, coddisc, strftime('%s', hora_inicial), strftime('%s', hora_final)  FROM horario");
}


static int horaExtrair(void *target, void **columnsData) {

	Disciplina *discPtr;
	time_t dt;
	struct tm *ttt;
	char dateStr[100];
	Horario *horario = (Horario *) target;

	horario->codigo = atoi(columnsData[0]);
	strcpy(horario->diaSemana, columnsData[1]);
	horario->disciplina = columnsData[2] ? discPegar(atoi(columnsData[2])) : NULL;
	horario->horaInicial = atoi(columnsData[3]);
	horario->horaFinal = atoi(columnsData[4]);

	return 0;

}


int horaAssociarDisciplina( int codHorario, int codDisciplina ) {

	char query[150];


	// Verifica se um horário foi informado.
	if( codHorario == 0 ) {
		fprintf(stderr, "Horário não informado.");
		return 1;
	}


	// Verifica se uma disciplina foi informada.
	if( codDisciplina == 0 )
		sprintf(query, "UPDATE horario SET coddisc = NULL where codhorario = %d;", codHorario);

	else
		sprintf(query, "UPDATE horario SET coddisc = %d where codhorario = %d;", codDisciplina, codHorario);


	// Executa a query e verifica o retorno.
	if( db_query(NULL, NULL, query) == SQLITE_OK )
		return 1;


	return 0;

}



Horario *horaPegar( const char diaSemana[4], int horario ) {

	Horario **horarios, *hor;
	char query[500];

	sprintf(query,
		"SELECT "
		"	codhorario, "
		"	coddiasemana, "
		"	coddisc, "
		"	strftime('%%s', hora_inicial), "
		"	strftime('%%s', hora_final) "
		"FROM horario "
		"WHERE coddiasemana = '%s' "
		"ORDER BY codhorario %s "
		"LIMIT 1", diaSemana, horario == 1 ? "ASC" : "DESC");


	horarios = db_list(sizeof(Horario), horaExtrair, query);
	hor = *horarios;

	free(horarios);
	return hor;

}


char *horaEscreverHora( const time_t hroaUnix, char *destino ) {

	if( destino == NULL )
		destino = (char *) malloc(sizeof(char)*6);

	strcpy(destino, "Teste");
	return destino;

}
