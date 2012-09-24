/*
 * database.c
 */

#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <strings.h>
#include <regex.h>

#include "horario.h"
#include "../lib/sqlite3.h"
#include "../lib/utils.h"





// Database connection
static sqlite3 *db;
static long int connLinks = 0;


/*
 * Resolves the path to the database
 */
static char *db_resolvePath(void) {
	return "./agenda.sqlite";
}


/*
 * Returns a physical connection to the database. If the database is not found,
 * a new one is created.
 */
static sqlite3 *db_connect(void) {

	FILE *dbFile;
	char *dbPath;
	int rc;

//	db_close_all();

	if( db != NULL ) {
		connLinks++;
		return db;
	}


	dbPath = db_resolvePath();

	if( (dbFile = fopen(dbPath, "r")) == NULL )
		db_init(dbPath);

	else
		fclose(dbFile);


	rc = sqlite3_open( dbPath, &db );

	// Tries to open the database
	if( rc ) {
		printf("Não foi possível abrir o banco: %s.", sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}


	connLinks++;
	if( atexit(db_close_all) )
		fprintf(stderr, "WARN: não foi possível registrar o link de fechamento automático da "
				"conexão com o banco. Certifique-se de que o banco será finalizado.");

	// Returns the connection.
	return db;

}


/*
 * Close the database connection if no one more is using it. Every time the method db_connect is executed
 * the method db_close needs to be invoked in order to properly close the connection, otherwise, a connection
 * would be left opened, causing memory problems.
 */
void db_close(void) {

	if( !--connLinks ) {

		if(db != NULL ) {
			sqlite3_close(db);
			db = NULL;
			connLinks = 0;
		}

	}

}


/*
 * Close all connections to the database.
 */
void db_close_all(void) {

	if(db != NULL ) {
		sqlite3_close(db);
		db = NULL;
		connLinks = 0;
	}

}


/*
 * Start a database structere in a given path.
 */
static void db_init( char *path ) {

	FILE *dbFile;
	sqlite3 *db;
	char *error = NULL;
	int rc;


	rc = sqlite3_open( path, &db );

	// Tries to open the database.
	if( rc ) {
		printf("Não foi possível inicializar o banco de dados: %s.", sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}


	// Creates the basic database structure.
	char CREATE_QUERY[] =
		"CREATE TABLE `disciplina` ("
		"  `coddisc` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ,"
		"  `nome` TEXT(80) NULL ,"
		"  `nome_prof` TEXT(200) NULL ,"
		"  `email_prof` TEXT(400) NULL );"
		";"
		"CREATE TABLE `tipo_atividade` ("
		"  `codtipoatividade` CHAR(2) NOT NULL ,"
		"  `descricao` TEXT NULL ,"
		"  PRIMARY KEY (`codtipoatividade`) );"
		";"
		"CREATE TABLE `atividade` ("
		"  `codatividade` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ,"
		"  `codtipoatividade` INTEGER NOT NULL ,"
		"  `coddisc` INTEGER NOT NULL ,"
		"  `nome` VARCHAR(45) NOT NULL ,"
		"  `data` TEXT NOT NULL ,"
		"  `pontos` DECIMAL NULL ,"
		"  `descricao` TEXT NULL ,"
		"  CONSTRAINT `fk_atividade_tipo_atividade`"
		"    FOREIGN KEY (`codtipoatividade` )"
		"    REFERENCES `tipo_atividade` (`codtipoatividade` )"
		"    ON DELETE CASCADE"
		"    ON UPDATE CASCADE,"
		"  CONSTRAINT `fk_atividade_disciplina`"
		"    FOREIGN KEY (`coddisc` )"
		"    REFERENCES `disciplina` (`coddisc` )"
		"    ON DELETE CASCADE"
		"    ON UPDATE CASCADE);"
		";"
		"CREATE INDEX `fk_atividade_tipo_atividade` ON `atividade` (`codtipoatividade` ASC);"
		"CREATE INDEX `fk_atividade_disciplina` ON `atividade` (`coddisc` ASC);"
		"CREATE TABLE `diasemana` ("
		"  `coddiasemana` CHAR(3) NOT NULL ,"
		"  `nome` TEXT(45) NULL ,"
		"  PRIMARY KEY (`coddiasemana`) );"
		";"
		"CREATE TABLE horario ("
		"    \"codhorario\" INTEGER NOT NULL,"
		"    \"coddiasemana\" CHAR(3) NOT NULL,"
		"    \"coddisc\" INTEGER,"
		"    \"hora_inicial\" TEXT,"
		"   \"hora_final\" TEXT"
		");"
		"CREATE INDEX `fk_horario_diasemana` ON `horario` (`coddiasemana` ASC);"
		"CREATE INDEX `fk_horario_disciplina` ON `horario` (`coddisc` ASC);";


	if( sqlite3_exec(db, CREATE_QUERY, NULL, NULL, &error) != SQLITE_OK ) {

		fprintf(stderr, "Não foi possível criar o banco de dados: %s.\n", error);
		free(error);
		sqlite3_close(db);
		exit(EXIT_FAILURE);

	}



	// Populate the tasks table
	char INSERT_ACTIVITIES_TYPES[] =
		"INSERT INTO tipo_atividade VALUES ('OU', 'Outras Atividades');"
		"INSERT INTO tipo_atividade VALUES ('PR', 'Prova');"
		"INSERT INTO tipo_atividade VALUES ('EX', 'Exercício avaliativo');"
		"INSERT INTO tipo_atividade VALUES ('TR', 'Entrega de trabalho');";

	if( sqlite3_exec(db, INSERT_ACTIVITIES_TYPES, NULL, NULL, &error) != SQLITE_OK ) {

		fprintf(stderr, "Não foi possível adicionar os tipos padrão de atividades: %s.\n", error);
		fprintf(stderr, "%s\n", INSERT_ACTIVITIES_TYPES);
		sqlite3_free(error);
		sqlite3_close(db);
		remove(path);
		exit(EXIT_FAILURE);

	}


	// Create the schedule
	char INSERT_TIME[1024];
	char weekDays[][4] = {"seg", "seg", "ter", "ter", "qua", "qua", "qui", "qui", "sex", "sex"};
	time_t today = time(NULL);
	struct tm *workingInit = localtime(&today);
	struct tm workingEnd;
	register int i;


	workingEnd.tm_sec = workingInit->tm_sec;
	workingEnd.tm_min = workingInit->tm_min;
	workingEnd.tm_hour = workingInit->tm_hour;
	workingEnd.tm_mday = workingInit->tm_mday;
	workingEnd.tm_mon = workingInit->tm_mon;
	workingEnd.tm_year = workingInit->tm_year;
	workingEnd.tm_wday = workingInit->tm_wday;
	workingEnd.tm_yday = workingInit->tm_yday;
	workingEnd.tm_isdst = workingInit->tm_isdst;


	for(i=0; i<10; i++ ) {

		if( i%2 ) {

			workingInit->tm_sec = 0;
			workingInit->tm_min = 0;
			workingInit->tm_hour= 21;

			workingEnd.tm_sec = 0;
			workingEnd.tm_min = 40;
			workingEnd.tm_hour= 22;

		} else {

			workingInit->tm_sec = 0;
			workingInit->tm_min = 0;
			workingInit->tm_hour= 19;

			workingEnd.tm_sec = 0;
			workingEnd.tm_min = 40;
			workingEnd.tm_hour= 20;

		}


		sprintf(INSERT_TIME,
			"INSERT INTO horario( "
			"	codhorario, coddiasemana, hora_inicial, hora_final)	VALUES("
			"	%d, '%s', strftime('%%H:%%M', %d, 'unixepoch'), strftime('%%H:%%M', %d, 'unixepoch')"
			");",
			i+1, weekDays[i], mktime(workingInit), mktime(&workingEnd)
		);

		if( sqlite3_exec(db, INSERT_TIME, NULL, NULL, &error) != SQLITE_OK ) {
			fprintf(stderr, "Não foi possível criar os horários no banco e dados: %s.\n", error);
			fprintf(stderr, "%s\n", INSERT_TIME);
			sqlite3_free(error);
			sqlite3_close(db);
			remove(path);
			exit(EXIT_FAILURE);
		}

	}


	sqlite3_close(db);

}


/*
 * Query the database
 */
int db_query(void *link, sqlite3_callback xCallback, char *sql) {

	char *errMsg = NULL;
	int rc;

	rc = sqlite3_exec(db_connect(), sql, xCallback, link, &errMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL Error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}


	return rc;

}


/*
 * Returns the last ID inserted
 */
int db_getLastInsertId( void ) {
	return sqlite3_last_insert_rowid(db_connect());
}






static int db_callback( void *extractor, int argc, char **argv, char **cols ) {

	DataBuffer *buffer = (DataBuffer *) extractor;
	void *data;

	// Allocate memory for the row object.
	data = malloc(buffer->typeSize);

	if( data == NULL ) {
		fprintf(stderr, "Não foi possível alocar memória.");
		return 1;
	}


	// Execute the result extractor.
	buffer->extractor( data, (void**) argv );


	// Allocate memory if the array does not exists yet or resize it otherwise.
	// The verification occurs to ensure that the user initialized the elements
	// pointer's pointer with NULL.
	if( buffer->length == 0 )
		buffer->elements = (void **) malloc(sizeof(void *));

	else
		buffer->elements = (void **) realloc(buffer->elements, sizeof(void *) * (buffer->length+1));



	if( buffer->elements == NULL ) {

		fprintf(stderr, "Não há memória suficiente para executar a operação.\n");
		exit(1);

	}


	// Adds an elment to the array
	buffer->elements[buffer->length] = data;
	buffer->length++;

	return 0;

}



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
void **db_list( size_t typeSize, int (*extractor)(void *, void **), char *sql ) {

	DataBuffer data;

	data.length = 0;
	data.typeSize = typeSize;
	data.extractor = extractor;
	data.elements = NULL;

	if( db_query(&data, db_callback, sql) != SQLITE_OK )
		printf("Erro de chamada.\n");


	data.elements = (void **) realloc(data.elements, ++data.length * sizeof(void *));

	if( !data.elements ) {
		fprintf(stderr, "Não há memória suficiente.\n");
		exit(1);
	}

	data.elements[data.length-1] = NULL;
	return data.elements;

}


/*
 * Cleanup the memory used by a list created with the function "db_list".
 *
 * Returns 0 if no error occurs.
 */
int db_listFree( void **list ) {

	void **ptr = list;

	while(*ptr) {
		free(*ptr);
		ptr++;
	}

	free(*ptr);
	free(list);


	return 0;

}


/* 
 * Try reading the String in "from", if it's NULL, then NULL is returned, otherwise,
 * memory is allocated dynamically to it and the string is copied to this new address.
 */
void *rs_readStringOrNull( const void *from ) {

	char *result;

	if( !from )
		return NULL;


	if( !(result= (char *) malloc(sizeof(char)*(strlen((char *)from)+1))) ) {
		fprintf(stderr, "Não há memória suficiente.");
		exit(1);
	}


	strcpy(result, (char *) from);
	return result;

}


/* 
 * Writes a string prepared to be inserted in the database or a 'NULL' string when the pointer is NULL and return the
 * pointer to this STRING.
 *
 * The allocated memory must be manaualy cleaned up.
 */
char *rs_prepareStringOrNull( const char *raw ) {

	char *to = NULL;

	if( raw ) {

		if( (to=(char *) malloc(S_CHAR*(strlen(raw)+3))) != NULL )
				sprintf(to, "'%s'", raw);

	} else {

		if( (to=(char *) malloc(S_CHAR*5)) != NULL )
			strcpy(to, "NULL");

	}


	if( to == NULL ) {
		fprintf(stderr, "Ocorreu um erro durante a preparação da query. Possivelmente não há memória suficiente.");
		exit(1);
	}


	return to;

}
