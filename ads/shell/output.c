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

#include "../core/atividade.h"
#include "../core/horario.h"
#include "../core/disciplina.h"
#include "../core/tipo_atividade.h"



/*
 * Escreve a lista de tipos disponíveis.
 *
 * param tipos	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarTiposAtividades( const TipoAtividade **tipos ) {

	TipoAtividade **atual = tipos;

	printf("Tipos de atividades disponíveis:\n\n");

	for(; *atual; atual++)
		printf("[%s] %s\n", (*atual)->codigo, (*atual)->descricao);

}



/*
 * Escreve a lista de disciplinas disponíveis.
 *
 * param disciplinas	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
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
 * Escreve a lista de horários disponíveis.
 *
 * param horarios	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarHorarios( const Horario **horarios ) {
/*
	const Horario **atual, *hora;
	char ultimoDia[4];
	char inicial[6], final[6];

	atual = horarios;
	strcpy(ultimoDia, "");

	printf("Grade de horários:\n\n");
	printf("       Horário           Disciplina\n");
//	printf("[seg1] 19:00 às 20:00    Sistemas Operacionais Proprietários");

	for(; (hora=*atual); atual++) {

		strftime(inicial, 6, "%H:%M", localtime(&hora->horaInicial));
		strftime(final, 6, "%H:%M", localtime(&hora->horaFinal));

		printf("%s[%s%d] %s às %s    %.55s\n",
			strcmp(ultimoDia, hora->diaSemana) ? "\n" : "",
			hora->diaSemana, ((hora->codigo-1)%2)+1,
			inicial, final,
			hora->disciplina ? hora->disciplina->nome : "---"
		);

		strcpy(ultimoDia, hora->diaSemana);

	}

	*/

	char result[100];
	time_t t, tBuffer;
	char init[11], final[11];
	struct tm *d;
	int i;

	t = time(NULL);
	strftime(init, 11, "%d/%m", localtime(&t));

	for(i=0; i<60; i++) {

		t = time(NULL);

		d = localtime(&t);
		d->tm_mday+=i;
		tBuffer = mktime(d);
		d = localtime(&tBuffer);

		strftime(final, 11, "%d/%m", d);

		tBuffer = mktime(d);

		getDataRef(&tBuffer, result);
		printf("%d: %s - %s  %s\n", i, init, final, result);
	}


}


/*
 * Escreve a lista de atividades disponíveis.
 *
 * param atividades	ponteiro para um vetor com os itens, finalizado com um ponteiro nulo.
 */
void outListarAtividades( const Atividade **atividades );


/*
 * Escreve o cabeçalho do dia, com informação de data e cabeçalho.
 */
static void outEscreverCabecalhoDia( const time_t *dia );


/*
 * Escreve uma atividade completa.
 */
static void outEscreverAtividade(const Atividade *atividade) {



}


/*
 * Calcula a diferença entre uma data e a data atual do sistema e escreve uma string representando
 * esta diferença no argumento "target". A string será em dias, em semanas ou em meses. Exs.:
 *
 * hoje
 * ontem
 * há 5 dias
 * há 1 semana
 * há 2 semanas
 * daqui a 4 dias
 * daqui a 1 semana
 * daqui a mais de 6 meses
 * há mais de 6 meses
 */
static void getDataRef( const time_t *date, char *target ) {

	time_t now = time(NULL);
	struct tm ref, *current;
	long int diff, absDiff;

	long int finalDiffValue;
	char unity[8];
	int maxReach=0;



	current = localtime(date);
	ref.tm_sec = 0;
	ref.tm_min = 0;
	ref.tm_hour = 0;
	ref.tm_mday = current->tm_mday;
	ref.tm_mon = current->tm_mon;
	ref.tm_year = current->tm_year;
	ref.tm_wday = current->tm_year;
	ref.tm_yday = current->tm_yday;
	ref.tm_isdst = current->tm_isdst;

	current = localtime(&now);
	current->tm_sec = 0;
	current->tm_min = 0;
	current->tm_hour = 0;



	diff = difftime(mktime(&ref), mktime(current)) / SECS_IN_DAY;
	absDiff = abs(diff);

	// Encontra a unidade de medida.
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

	} else if( current->tm_mon == ref.tm_mon || absDiff < 28 ) {

		finalDiffValue = ceil(absDiff / 7);
		sprintf(unity, "%s%s", "semana", finalDiffValue == 1 ? "" : "s");

	} else {

		finalDiffValue = ceil(absDiff/28);

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



