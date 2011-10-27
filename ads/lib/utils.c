/*
 * utils.c
 *
 *  Created on: Oct 26, 2011
 *      Author: caiotoon
 */

#include <ctype.h>


void strToLower( char *str ) {

	register char *ptr = str;

	for(ptr=str; *ptr; ptr++)
		if( !islower(*ptr) )
			*ptr = tolower((unsigned char)*ptr);

}
