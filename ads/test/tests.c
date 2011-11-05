/*
 * shell.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/sqlite3.h"
#include "../lib/utils.h"
#include "../core/horario.h"
#include "../core/tipo_atividade.h"
#include "../core/disciplina.h"



static void traceDisc(Disciplina *disc);
void setHorarios(void);
void traceAllAtivs(void);
void traceAllDiscs(void);
void traceAllHorarios(void);




void testAll( void ) {

	traceAllAtivs();
	traceAllDiscs();
	traceAllHorarios();

}


void setHorarios( void ) {

	printf("Iniciado gravação de horas.\n");

	int i5;
	time_t nowTime;
	struct tm *cur;
	char sql[1000];

	nowTime = time(NULL);
	cur = localtime(&nowTime);
	cur->tm_sec = 0;

	for( i5=0; i5<10; i5++ ) {

		if(i5%2) {
			cur->tm_hour = 21;
			cur->tm_min = 00;
		}else {
			cur->tm_hour = 19;
			cur->tm_min = 00;
		}

		sprintf(sql, "UPDATE horario SET hora_inicial = strftime('%%H:%%M', %d, 'unixepoch') WHERE codhorario = %d;", mktime(cur), i5+1);
		printf("%d, %d - %s\n", i5+1, SQLITE_OK == db_query(NULL, NULL, sql), asctime(cur));

	}

}

void traceAllAtivs(void) {

	TipoAtividade **atividades, **ptr;


	atividades = tipoListar();

	for( ptr = atividades; *ptr; ptr++ )
		printf(":: [%s] %s\n", (*ptr)->codigo, (*ptr)->descricao);


	db_listFree(atividades);

}


void traceAllDiscs(void) {

	printf("Fim dos tipos de atividades -----------------------------\n");

	Disciplina **discs, **ptrD, *disc;

	disc = discPegar(1);
	traceDisc(disc);

	free(disc);

	printf("Fim da disciplina de código 1 -------------------------------\n");

	discs = discListar();
	for(ptrD=discs; *ptrD; ptrD++)
		traceDisc(*ptrD);

	db_listFree(discs);

	printf("Fim das disciplinas-----------------------------\n");


}


void traceAllHorarios(void) {

	Horario **horarios, **ptrH;
	Horario *curHor;
	char hourFinalOutput[6], hourInitialOutput[6];

	horarios = horaListar();

	for( ptrH=horarios; *ptrH; ptrH++ ) {

		curHor = *ptrH;

		strftime(hourInitialOutput, 6, "%H:%M", localtime(&curHor->horaInicial));
		strftime(hourFinalOutput, 6, "%H:%M", localtime(&curHor->horaFinal));

		printf(":: [%d] %s (%s, %s)\n", curHor->codigo, curHor->diaSemana, hourInitialOutput, hourFinalOutput);

		if(curHor->disciplina) {
			printf("\t");
			traceDisc(curHor->disciplina);
		}

	}

	db_listFree(horarios);


}


static void traceDisc(Disciplina *disc) {

	if( disc )
		printf("%d - %s (%s, %s)\n", disc->codigo, disc->nome, disc->professor, disc->email);
	else
		printf("NULL\n");

}
