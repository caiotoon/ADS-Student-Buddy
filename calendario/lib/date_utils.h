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
 * Returns the difference between two dates in days.
 */
int diffdays( const time_t *startDate, const time_t *endDate);


/*
 * Calculates the difference bewteen two days in months.
 */
int diffmonths( const time_t *startDate, const time_t *endDate );


/*
 * Copy one time structure into another.
 */
void tmcpy( struct tm *dest, const struct tm* src );



#endif /* DATE_UTILS_H_ */
