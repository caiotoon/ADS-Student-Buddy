/*
 * database.h
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "../lib/sqlite3.h"


/*
 * Retorna uma conexão ao banco de dados. Caso o banco de dados não seja encontrado, um
 * novo banco é criado.
 */
sqlite3 *connect();


#endif /* DATABASE_H_ */
