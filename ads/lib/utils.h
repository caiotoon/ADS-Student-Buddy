/*
 * utils.h
 */

#ifndef _UTILS_H
#define _UTILS_H

struct GenericArray {

	int length;
	void **elements;

};

typedef struct GenericArray GenericArray;


/*
 * Converte uma string para letras minúsculas.
 */
void strToLower( char *str );




#endif
