/*
 * date_utils.c
 */

#include "date_utils.h"

#include <time.h>



/*
 * Retorna o número de dias de diferença entre as duas datas. Indica que a data inicial é menor que a final.
 */
int diffdays( const time_t *startDate, const time_t *endDate) {

	struct tm ref, *current;

	current = localtime(endDate);
	tmcpy(&ref, current);
	ref.tm_sec = 0;
	ref.tm_min = 0;
	ref.tm_hour = 5;

	current = localtime(startDate);
	current->tm_sec = 0;
	current->tm_min = 0;
	current->tm_hour = 5;



	return difftime(mktime(&ref), mktime(current)) / SECS_IN_DAY;

}


/*
 * Calcula a diferença de meses entre duas datas. Um valor negativo indica que a data inicial é menor que a final.
 */
int diffmonths( const time_t *startDate, const time_t *endDate ) {

	struct tm ref, *current;

	current = localtime(endDate);
	tmcpy( &ref, current );
	ref.tm_sec = 0;
	ref.tm_min = 0;
	ref.tm_hour = 5;

	current = localtime(startDate);
	current->tm_sec = 0;
	current->tm_min = 0;
	current->tm_hour = 5;

	return (ref.tm_mon+12*ref.tm_year) - (current->tm_mon+12*current->tm_year);

}


/*
 * Copia uma estrutura de data para outra.
 */
void tmcpy( struct tm *dest, const struct tm* src ) {

	dest->tm_sec = src->tm_sec;
	dest->tm_min = src->tm_min;
	dest->tm_hour = src->tm_hour;
	dest->tm_mday = src->tm_mday;
	dest->tm_mon = src->tm_mon;
	dest->tm_year = src->tm_year;
	dest->tm_wday = src->tm_year;
	dest->tm_yday = src->tm_yday;
	dest->tm_isdst = src->tm_isdst;

}
