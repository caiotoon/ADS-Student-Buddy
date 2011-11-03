/*
 * database.c
 */


#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"
#include "database.h"


/*
 * Retorna o caminho para o banco de dados.
 */
static char *db_resolvePath(void) {
	return "./agenda.sqlite";
}


/*
 * Retorna uma conexão ao banco de dados. Caso o banco de dados não seja encontrado, um
 * novo banco é criado.
 */
static sqlite3 *db_connect(void) {

	FILE *dbFile;
	sqlite3 *db;
	char *dbPath;
	int rc;


	dbPath = db_resolvePath();

	if( (dbFile = fopen(dbPath, "r")) == NULL )
		db_init(dbPath);

	else
		fclose(dbFile);


	rc = sqlite3_open( dbPath, &db );

	// Tenta abrir o banco de dados.
	if( rc ) {
		printf("Não foi possível abrir o banco: %s.", sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}


	// Retorna o banco de dados.


	return db;

}


/*
 * Inicializa o banco de dados em um caminho definido.
 */
static void db_init( char *path ) {
	fprintf(stderr, "Não foi possível encontrar o banco de dados.");
	exit(EXIT_FAILURE);
}


/*
 * Realiza um query no banco.
 */
int db_query(void *link, sqlite3_callback xCallback, char *sql) {

	char *errMsg = 0;
	int rc;

	rc = sqlite3_exec(db_connect(), sql, xCallback, link, &errMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL Error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}


	return rc;

}




static int db_callback( void *extractor, int argc, char **argv, char **cols ) {

	DataBuffer *buffer = (DataBuffer *) extractor;
	void *data;

	// Aloca memória para o objeto da linha.
	data = malloc(sizeof(*buffer->typeSample));

	if( data == NULL ) {
		fprintf(stderr, "Não foi possível alocar memória.");
		return 1;
	}


	// Executa o extrator de resultado.
	buffer->extractor( data, (void**) argv );


	// Verifica a inicialização do array e aloca a memória ou redimensiona-a.
	if( buffer->length == 0 )
		buffer->elements = malloc(sizeof(buffer->typeSample));

	else
		buffer->elements = realloc(buffer->elements, sizeof(buffer->typeSample) * buffer->length);

	// Adiciona o elemento no array.
	buffer->elements[buffer->length] = data;
	buffer->length++;

	return 0;

}



/*
 * Realiza uma query no banco e efetua o parseamento do resultado em um array de diversos
 * items. Os itens são extraídos através da função "extraction". Um ponteiro nulo será retornado
 * caso ocorra algum erro. O array de itens será finalizado com um ponteiro nulo.
 *
 * É indicado o uso da funçao "db_listFree" para desalocar a memória gasta pela lista gerada por
 * esta função.
 *
 * extractor	função utilizada para extrair um conteúdo de uma linha do ResultSet.
 * 				O extrator é suposto a conhecer a estrutura do resultado.
 * sql			SQL que será realizada no banco para trazer os resultados.
 */
void **db_list( void *typeSample, int (*extractor)(void *, void **), char *sql ) {

	DataBuffer data;

	data.length = 0;
	data.typeSample = typeSample;
	data.extractor = extractor;

	if( db_query(&data, db_callback, sql) != SQLITE_OK )
		printf("Erro de chamada.\n");


	data.elements[++data.length] = NULL;
	return data.elements;

}


/*
 * Libera a memória utilizada por uma lista que tenha sido gerada com a função "db_list".
 *
 * Retorna 0 se nenhum erro ocorrer.
 */
int db_listFree( void **list ) {

	void *ptr = *list;

	while(ptr)
		free(ptr++);

	free(list);


	return 0;

}

