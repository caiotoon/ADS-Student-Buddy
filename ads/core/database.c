/*
 * database.c
 */

#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#include "horario.h"
#include "../lib/sqlite3.h"



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

	FILE *dbFile;
	sqlite3 *db;
	char *error = NULL;
	int rc;


	rc = sqlite3_open( path, &db );

	// Tenta abrir o banco de dados.
	if( rc ) {
		printf("Não foi possível inicializar o banco de dados: %s.", sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}


	// Cria o banco de dados.
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



	// Popula tabela tipos de atividades
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


	// Cria os horários.
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

}


/*
 * Realiza um query no banco.
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




static int db_callback( void *extractor, int argc, char **argv, char **cols ) {

	DataBuffer *buffer = (DataBuffer *) extractor;
	void *data;

	// Aloca memória para o objeto da linha.
	data = malloc(buffer->typeSize);

	if( data == NULL ) {
		fprintf(stderr, "Não foi possível alocar memória.");
		return 1;
	}


	// Executa o extrator de resultado.
	buffer->extractor( data, (void**) argv );


	// Verifica a inicialização do array e aloca a memória ou redimensiona-a.
	if( buffer->length == 0 )
		buffer->elements = malloc(sizeof(void *));

	else
		buffer->elements = (void **) realloc(buffer->elements, sizeof(void *) * (buffer->length+1));

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
void **db_list( size_t typeSize, int (*extractor)(void *, void **), char *sql ) {

	DataBuffer data;

	data.length = 0;
	data.typeSize = typeSize;
	data.extractor = extractor;

	if( db_query(&data, db_callback, sql) != SQLITE_OK )
		printf("Erro de chamada.\n");

	if( data.length == 0 )
		data.elements = malloc(sizeof(NULL));

	data.elements[data.length++] = malloc(sizeof(NULL));
	data.elements[data.length-1] = NULL;
	return data.elements;

}


/*
 * Libera a memória utilizada por uma lista que tenha sido gerada com a função "db_list".
 *
 * Retorna 0 se nenhum erro ocorrer.
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

