/*
 * utils.c
 */

#include <ctype.h>


void strToLower( char *str ) {

	register char *ptr = str;

	for(ptr=str; *ptr; ptr++)
		if( !islower(*ptr) )
			*ptr = tolower((unsigned char)*ptr);

}


void strToUpper( char *str ) {

	register char *ptr = str;

	for(ptr=str; *ptr; ptr++)
		if( !isupper(*ptr) )
			*ptr = toupper((unsigned char)*ptr);

}

