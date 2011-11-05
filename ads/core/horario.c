/*
 * horario.c
 */

#include <stdio.h>
#include <stdlib.h>
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

