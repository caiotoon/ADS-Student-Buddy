/*
 * output.c
 */

/*
 * output.h
 */

#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../lib/date_utils.h"
#include "../core/atividade.h"
#include "../core/horario.h"
#include "../core/disciplina.h"
#include "../core/tipo_atividade.h"



/*
 * Write the type of activities informed.
 *
 * param tipos	pointer to the types that should be listed.
 */
void outListarTiposAtividades( const TipoAtividade **tipos ) {

	TipoAtividade **atual = tipos;

	printf("Tipos de atividades disponíveis:\n\n");

	for(; *atual; atual++)
		printf("[%s] %s\n", (*atual)->codigo, (*atual)->descricao);

}



/*
 * Write the discipline informed.
 *
 * param disciplinas	a pointer the disciplines that should be listed.
 */
void outListarDisciplinas( const Disciplina **disciplinas ) {

	const Disciplina **atual, *disc;
	char email[300];

	atual = disciplinas;

	printf("Disciplinas disponíveis:\n\n");

	for(; (disc=*atual); atual++) {

		sprintf(email, disc->email ? "(%s)" : "", disc->email);

		printf("%3.3d. %s - %s %.30s\n",
				disc->codigo, disc->nome,
				disc->professor, email);

	}

}



/*
 * Write the schedules informed.
 *
 * param horarios	pointer to the schedules that should be listed.
 */
void outListarHorarios( const Horario **horarios ) {

	const Horario **atual, *hora;
	char ultimoDia[4];
	char inicial[6], final[6];

	atual = horarios;
	strcpy(ultimoDia, "");

	printf("Grade de horários:\n\n");
	printf("       Horário           Disciplina\n");

	for(; (hora=*atual); atual++) {

		strftime(inicial, 6, "%H:%M", localtime(&hora->horaInicial));
		strftime(final, 6, "%H:%M", localtime(&hora->horaFinal));

		if( hora->disciplina ) {

			printf("%s[%s%d] %s às %s    %3d. %.55s\n",
				strcmp(ultimoDia, hora->diaSemana) ? "\n" : "",
				hora->diaSemana, ((hora->codigo-1)%2)+1,
				inicial, final,
				hora->disciplina->codigo,
				hora->disciplina->nome
			);

		} else {

			printf("%s[%s%d] %s às %s         ---\n",
				strcmp(ultimoDia, hora->diaSemana) ? "\n" : "",
				hora->diaSemana, ((hora->codigo-1)%2)+1,
				inicial, final
			);

		}

		strcpy(ultimoDia, hora->diaSemana);

	}


}


/*
 * Write a list with all available activities.
 *
 * param atividades	pointer to the activities that should be listed.
 */
void outListarAtividades( const time_t *dataInicial, const time_t *dataFinal, const Atividade **atividades ) {

	const Atividade **atual, *ativ;
	char init[20], final[20];
	time_t *lastDate = NULL;


	strftime(init, 11, "%d-%m-%Y", localtime(dataInicial));
	strftime(final, 11, "%d-%m-%Y", localtime(dataFinal));

	atual = atividades;

	if( *atual ) {

		if( *dataInicial == *dataFinal )
			printf("Atividades em %s.\n", init);
		else
			printf("Atividades entre %s à %s.\n", init, final);


		for( ; (ativ=*atual); atual++ ) {

			if( !lastDate || diffdays(&ativ->data, lastDate) != 0 )
				outEscreverCabecalhoDia(lastDate=&ativ->data);

			outEscreverAtividade(ativ);

		}

	} else {

		if( *init == *final )
			printf("Não existem atividades em %s.\n", init);
		else
			printf("Não existem atividades entre os dias %s e %s.\n", init, final);

	}


}


/*
 * Writes the header of the day.
 */
static void outEscreverCabecalhoDia( const time_t *dia ) {

	struct tm *data = localtime(dia);
	char diaSemana[15], dataExtenso[11], dataRef[30];


	strftime(diaSemana, 15, "%A", data);
	strftime(dataExtenso, 11, "%d-%m-%Y", data);
	getDataRef(dia, dataRef);


	printf( "\n%s - %s (%s)\n", dataExtenso, diaSemana, dataRef );

}


/*
 * Writes a complete activity.
 */
static void outEscreverAtividade(const Atividade *atividade) {

	Disciplina *disc = discPegar(atividade->disciplina);
	printf( "%5d. %-20.20s  [%s] %s (%.1f pts)\n", atividade->codigo/*atividade->horario ? 2-(atividade->horario%2) : 0*/, disc->nome, atividade->tipoAtividade, atividade->titulo, atividade->pontos );

}



/*
 * Calculates the difference between a specific date and the system date and writes a string representing the relative time between them.
 * The string will be written to the [target] pointer, and the possible values are:
 *
 * hoje (today)
 * ontem (yesterday)
 * há 5 dias (5 days ago)
 * há 1 semana (1 week ago)
 * há 2 semanas (2 weeks ago)
 * daqui a 4 dias (in 4 days)
 * daqui a 1 semana (in 1 week)
 * daqui a mais de 6 meses (6+ months ahead)
 * há mais de 6 meses (6+ months ago)
 */
static void getDataRef( const time_t *date, char *target ) {

	time_t now = time(NULL);
	struct tm ref, *current;
	long int diff, absDiff;

	long int finalDiffValue;
	char unity[8];
	int maxReach=0;


	diff = diffdays(&now, date);
	absDiff = abs(diff);

	current = localtime(date);
	tmcpy(&ref, current);
	current = localtime(&now);

	ref.tm_hour = 5;
	current->tm_hour = 5;


	// Find the correct scale.
	if( absDiff == 0 ) {
		strcpy(target, "hoje");
		return;
	} else if( diff == 1 ) {
		strcpy(target, "amanhã");
		return;
	} else if( diff == -1 ) {
		strcpy(target, "ontem");
		return;
	} else if( absDiff < 7 ) {

		finalDiffValue = absDiff;
		sprintf(unity, "%s%s", "dia", finalDiffValue == 1 ? "" : "s");

	} else if( (current->tm_mon == ref.tm_mon && current->tm_year == ref.tm_year)|| absDiff < 35 ) {

		finalDiffValue = ceil(absDiff / 7);
		sprintf(unity, "%s%s", "semana", finalDiffValue == 1 ? "" : "s");

	} else {

		diff = diffmonths(&now, date);
		finalDiffValue = abs(diff);

		if( finalDiffValue > 6 ) {
			maxReach = 1;
			finalDiffValue = 6;
		}


		sprintf(unity, "%s", finalDiffValue == 1 ? "mês" : "meses");

	}


	if( diff < 0 )
		sprintf( target, maxReach ? "há mais de %d %s" : "há %d %s", finalDiffValue, unity );

	else
		sprintf( target, maxReach ? "daqui a mais de %d %s" : "daqui a %d %s", finalDiffValue, unity );

}



