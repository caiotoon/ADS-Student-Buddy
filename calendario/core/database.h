/*
 * database.h
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdlib.h>
#include "../lib/sqlite3.h"



// Defition of the data type expected in the extraction.
struct _DataBuffer {

	int length;							// the ammount of elements extracted.
	void **elements;					// a pointer to the elements pointer.
	size_t typeSize; 					// the size of each individual item extracted in bytes.
	int (*extractor)(void *, void **);	// the function that should be used to extract the item from
										// the ResultSet in a callback. It is expected that the function
										// is familiar with the order and content of the columns of the
										// ResultSet. Returns 0 if the extraction occurs with success.

};

typedef struct _DataBuffer DataBuffer;




/*
 * Resolves the path to the database
 */
static char *db_resolvePath(void);



/*
 * Returns a physical connection to the database. If the database is not found,
 * a new one is created.
 */
static sqlite3 *db_connect(void);


/*
 * Close the database connection if no one more is using it. Every time the method db_connect is executed
 * the method db_close needs to be invoked in order to properly close the connection, otherwise, a connection
 * would be left opened, causing memory problems.
 */
void db_close(void);


/*
 * Close all connections to the database.
 */
void db_close_all(void);


/*
 * Start a database structere in a given path.
 */
static void db_init( char *path );


/*
 * Query the database
 */
int db_query(void *link, sqlite3_callback callback, char *sql);


/*
 * Returns the last ID inserted
 */
int db_getLastInsertId( void );


/* 
 * Query the database and parse the result in an array of multiple items. The items are extracted
 * by the method "extraction". A NULL pointer must be returned in case fo any error. The items 
 * array must be ended by a NULL pointer.
 *
 * It's indicated the use of "db_listFree" for memory cleanup after the list has been used.
 *
 * extractor	function that will be used to fetch a result from the ResultSet. The extractor is
 * 				suposed to know the ResultSet internal structure.
 * sql			SQL that will be realized in the database to bring the results.
 */
void **db_list( size_t typeSize, int (*extractor)(void *, void **), char *sql );


/*
 * Cleanup the memory used by a list created with the function "db_list".
 *
 * Returns 0 if no error occurs.
 */
int db_listFree( void **list );


/* 
 * Try reading the String in "from", if it's NULL, then NULL is returned, otherwise,
 * memory is allocated dynamically to it and the string is copied to this new address.
 */
void *rs_readStringOrNull( const void *from );


/* 
 * Writes a string prepared to be inserted in the database or a 'NULL' string when the pointer is NULL and return the
 * pointer to this STRING.
 *
 * The allocated memory must be manaualy cleaned up.
 */
char *rs_prepareStringOrNull( const char *raw );

#endif
