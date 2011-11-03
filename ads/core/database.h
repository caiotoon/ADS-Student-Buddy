/*
 * database.h
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "../lib/sqlite3.h"
#include <stdlib.h>


// Definição do tipo de dados enviado para extração dos resultados.
struct _DataBuffer {

	int length;							// a quantidade de itens no array de elementos.
	void **elements;					// um ponteiros para os ponteiros dos elementos.
	void *typeSample; 					// um ponteiro para um elemento válido do tipo.
	int (*extractor)(void *, void **);	// a função utilizada para extrair um resultado de um callback.
										// É esperado que a função conheça a ordem das colunas do
										// resultado. Retorna 0 se a extração ocorrer com sucesso.

};

typedef struct _DataBuffer DataBuffer;




/*
 * Retorna o caminho para o banco de dados.
 */
static char *db_resolvePath(void);



/*
 * Retorna uma conexão ao banco de dados. Caso o banco de dados não seja encontrado, um
 * novo banco é criado.
 */
static sqlite3 *db_connect(void);


/*
 * Inicializa o banco de dados em um caminho definido.
 */
static void db_init( char *path );


/*
 * Realiza um query no banco.
 */
int db_query(void *link, sqlite3_callback callback, char *sql);


/*
 * Realiza uma query no banco e efetua o parseamento do resultado em um array de diversos
 * items. Os itens são extraídos através da função "extraction". Um ponteiro nulo será retornado
 * caso ocorra algum erro. O array de itens será finalizado com um ponteiro nulo.
 *
 * typeSample	Passa um ponteiro para um objeto válido que definirá o tipo dos objetos do array
 * 				de retorno.
 * extractor	função utilizada para extrair um conteúdo de uma linha do ResultSet.
 * 				O extrator é suposto a conhecer a estrutura do resultado.
 * sql			SQL que será realizada no banco para trazer os resultados.
 */
void **db_list( void *typeSample, int (*extractor)(void *, void **), char *sql );


/*
 * Libera a memória utilizada por uma lista que tenha sido gerada com a função "db_list".
 */
int db_listFree( void **list );

#endif
