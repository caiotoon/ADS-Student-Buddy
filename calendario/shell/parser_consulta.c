/*
 * parser_consulta.c
 */

#include "parser_consulta.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/date_utils.h"


static void get_yesterday(time_t *startDate, time_t *endDate);
static void get_today(time_t *startDate, time_t *endDate);
static void get_tomorrow(time_t *startDate, time_t *endDate);
static void get_week(time_t *startDate, time_t *endDate);
static void get_month(time_t *startDate, time_t *endDate);
static void get_interval(int argc, char **argv, time_t *startDate, time_t *endDate);



void parseCons( int argc, char **argv, time_t *dataInicial, time_t *dataFinal ) {

	char *comm = argv[1];

	if( !strcmp(comm, "hoje") )
		get_today(dataInicial, dataFinal);
	else if( !strcmp(comm, "amanha") )
		get_tomorrow(dataInicial, dataFinal);
	else if( !strcmp(comm, "ontem") )
		get_yesterday(dataInicial, dataFinal);
	else if( !strcmp(comm, "semana") )
		get_week(dataInicial, dataFinal);
	else if( !strcmp(comm, "mes") )
		get_month(dataInicial, dataFinal);
	else
		get_interval(argc, argv, dataInicial, dataFinal);

}


static void get_yesterday(time_t *startDate, time_t *endDate) {

	time_t t = time(NULL);
	t -= SECS_IN_DAY;

	*startDate = t;
	*endDate = t;

}


static void get_today(time_t *startDate, time_t *endDate) {

	time_t t = time(NULL);
	*startDate = t;
	*endDate = t;

}


static void get_tomorrow(time_t *startDate, time_t *endDate) {

	time_t t = time(NULL);
	t += SECS_IN_DAY;

	*startDate = t;
	*endDate = t;

}


static void get_week(time_t *startDate, time_t *endDate) {

	time_t t = time(NULL);
	struct tm *d;

	d = localtime(&t);
	t -= SECS_IN_DAY * d->tm_wday;

	*startDate = t;
	*endDate = t + SECS_IN_DAY*6;

}



static void get_month(time_t *startDate, time_t *endDate) {

	time_t t = time(NULL);
	struct tm *d = localtime(&t);


	d->tm_mday = 1;
	*startDate = mktime(d);

	d->tm_mon++;
	d->tm_mday = 0;
	*endDate = mktime(d);

}



static void get_interval(int argc, char **argv, time_t *startDate, time_t *endDate) {

	time_t t;
	struct tm *refDate;
	int tday, tmon, tyear;

	if( argc == 2 ) {

		t = time(NULL);
		refDate = localtime(&t);

		if( strptime(argv[1], "%d-%m-%Y", refDate) ) {

			*startDate = mktime(refDate);
			*endDate = *startDate;

		} else {

			*startDate = 0;
			*endDate = 0;

		}

	} else if (argc == 3 ) {

		t = time(NULL);
		refDate = localtime(&t);

		*startDate	= strptime(argv[1], "%d-%m-%Y", refDate) ? mktime(refDate) : 0;
		*endDate	= strptime(argv[2], "%d-%m-%Y", refDate) ? mktime(refDate) : 0;

	} else {

		*startDate = 0;
		*endDate = 0;

	}



	if( !*startDate )
		fprintf(stderr, "Formato de data inválido para '%s'. A data deve ser informada no formato dd-mm-aaaa.\n", argv[1]);

	else if(!*endDate)
		fprintf(stderr, "Formato de data inválido para '%s'. A data deve ser informada no formato dd-mm-aaaa.\n", argv[2]);


}
