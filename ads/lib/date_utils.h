/*
 * date_utils.h
 *
 *  Created on: Nov 10, 2011
 *      Author: caiotoon
 */

#ifndef DATE_UTILS_H_
#define DATE_UTILS_H_

#ifndef SECS_IN_DAY
#define SECS_IN_DAY 86400
#endif



#include <time.h>

/*
 * Retorna o número de dias de diferença entre as duas datas. Indica que a data inicial é menor que a final.
 */
int diffdays( const time_t *startDate, const time_t *endDate);


/*
 * Calcula a diferença de meses entre duas datas. Um valor negativo indica que a data inicial é menor que a final.
 */
int diffmonths( const time_t *startDate, const time_t *endDate );


/*
 * Copia uma estrutura de data para outra.
 */
void tmcpy( struct tm *dest, const struct tm* src );



#endif /* DATE_UTILS_H_ */
