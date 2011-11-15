/*
 * shell.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/sqlite3.h"
#include "../lib/utils.h"
#include "../lib/date_utils.h"
#include "../core/horario.h"
#include "../core/tipo_atividade.h"
#include "../core/disciplina.h"
#include "../core/atividade.h"
#include "../shell/output.h"
#include "../shell/parser_disciplina.h"



static void traceDisc(Disciplina *disc);
void setHorarios(void);
void traceAllAtivs(void);
void traceAllDiscs(void);
void traceAllHorarios(void);
void testHorarios(int update);
void discNova(void);
void ativTest(void);

void parseTest(void);





void testAll( void ) {

	traceAllAtivs();
	traceAllDiscs();
	traceAllHorarios();

}


void setHorarios( void ) {

	printf("Iniciado gravação de horas.\n");

	int i5;
	time_t nowTime;
	struct tm *cur;
	char sql[1000];

	nowTime = time(NULL);
	cur = localtime(&nowTime);
	cur->tm_sec = 0;

	for( i5=0; i5<10; i5++ ) {

		if(i5%2) {
			cur->tm_hour = 21;
			cur->tm_min = 00;
		}else {
			cur->tm_hour = 19;
			cur->tm_min = 00;
		}

		sprintf(sql, "UPDATE horario SET hora_inicial = strftime('%%H:%%M', %d, 'unixepoch') WHERE codhorario = %d;", mktime(cur), i5+1);
		printf("%d, %d - %s\n", i5+1, SQLITE_OK == db_query(NULL, NULL, sql), asctime(cur));

	}

}

void traceAllAtivs(void) {

	TipoAtividade **atividades, **ptr;


	atividades = tipoListar();

	for( ptr = atividades; *ptr; ptr++ )
		printf(":: [%s] %s\n", (*ptr)->codigo, (*ptr)->descricao);


	db_listFree(atividades);

}


void traceAllDiscs(void) {

	printf("Fim dos tipos de atividades -----------------------------\n");

	Disciplina **discs, **ptrD, *disc;

	disc = discPegar(1);
	traceDisc(disc);

	free(disc);

	printf("Fim da disciplina de código 1 -------------------------------\n");

	discs = discListar();
	for(ptrD=discs; *ptrD; ptrD++)
		traceDisc(*ptrD);

	db_listFree(discs);

	printf("Fim das disciplinas-----------------------------\n");


}


void traceAllHorarios(void) {

	Horario **horarios, **ptrH;
	Horario *curHor;
	char hourFinalOutput[6], hourInitialOutput[6];

	horarios = horaListar();

	for( ptrH=horarios; *ptrH; ptrH++ ) {

		curHor = *ptrH;

		strftime(hourInitialOutput, 6, "%H:%M", localtime(&curHor->horaInicial));
		strftime(hourFinalOutput, 6, "%H:%M", localtime(&curHor->horaFinal));

		printf(":: [%d] %s (%s, %s)\n", curHor->codigo, curHor->diaSemana, hourInitialOutput, hourFinalOutput);

		if(curHor->disciplina) {
			printf("\t");
			traceDisc(curHor->disciplina);
		}

	}

	db_listFree(horarios);


}


static void traceDisc(Disciplina *disc) {

	if( disc )
		printf("%d - %s (%s, %s)\n", disc->codigo, disc->nome, disc->professor, disc->email);
	else
		printf("NULL\n");

}


void testHorarios(int update) {

	if( update )
		setHorarios();

	//horaAssociarDisciplina(2, 1);
	horaAssociarDisciplina(1, NULL);
	traceAllHorarios();

}



void discNova(void) {

	Disciplina disc;

	disc.professor = "Caio Cunha";
	disc.nome = "Office 2005";
	disc.email = "caio@caiotoon.com";

	/* CRIA UMA NOVA DISCIPLINA
	if(!discAdicionar(&disc))
		printf("Codigo: %d.", disc.codigo);
	else
		fprintf(stderr, "Não foi possível criar a nova disciplina.");
	*/

	disc.codigo = 2;
	disc.professor = "Adamastor";

	discAtualizar(&disc);


	discRemover(3);
	discRemover(4);
	discRemover(5);


}



void ativTest(void) {

	/*
	Atividade atividade;

	atividade.data = time(0);
	atividade.titulo = "Atividade de teste";
	atividade.descricao = "Essa é a descrição da atividade";
	atividade.disciplina = 1;
	atividade.pontos = 30.0;
	strcpy(atividade.tipoAtividade, "PR");


	ativAdicionar(&atividade);
	printf("Atividade adicionada: %d.", atividade.codigo);
	*/

	Atividade *ativ = ativPegar(1);

	strcpy(ativ->titulo, "Nome alterado");
	ativ->data = time(0);
	ativAtualizar(ativ);
	printf("Atividade: %d. %s - %s (horário: %d [%d])\n", ativ->codigo, ativ->titulo, asctime(localtime(&ativ->data)), ativ->horario, ativ->horario ? (ativ->horario%2 == 0)+1 : 0);

}



void outTiposAtividades() {

	TipoAtividade **tipos = tipoListar();
	outListarTiposAtividades(tipos);

	db_listFree(tipos);

}

void outDiscs() {

	Disciplina **values = discListar();
	outListarDisciplinas(values);

	db_listFree(values);

}


void outHoras() {

	Horario **values = horaListar();
	outListarHorarios(values);

	db_listFree(values);

}


void outAtividades() {

	time_t from, to;
	Atividade **values;

	from = time(NULL)-SECS_IN_DAY*300;
	to = time(NULL)+SECS_IN_DAY*300;

	values = ativListar(&from, &to);

	outListarAtividades(&from, &to, values);


}




int outputTest() {

//	outTiposAtividades();
//	outDiscs();
//	outHoras();
	outAtividades();

}




void parseTest(void) {
/*
	char horarios[] = "seg1,sex2";
	int *hor;

	hor = lerHorario(horarios);

	if(!hor)
		printf("Nenhum horário.\n");

	else {

		for(; *hor; hor++)
			printf("%d\n", *hor);

	}


	printf("\nfim do teste.\n");
	exit(0);
*/
	char command[][100] = {"ads", "disciplina",
			"-r",
			"-c", "1",
//			"-p", "Carlos",
//			"-n", "Programacao Estruturada",
//			"-h", "seg1,seg2,sex2",
//			"-m", "carlinhos@prof.una.br",
			"---"};
	char **at;
	char **str = (char **) malloc(sizeof(char *));
	int i, cmds=0;

	for(i=0; strcmp(command[i], "---"); i++) {

		cmds++;
		str = realloc(str, sizeof(char *)*(i+1));
		str[i] = (char *) malloc(sizeof(char)*(strlen(command[i])+1));
		strcpy(str[i], command[i]);

	}


	int *hor = NULL;
	Disciplina *disc;

	//disc =
	printf(">> %d", parseDiscRemover(cmds, str/*, &hor*/));

	if( hor )
		for(; *hor; hor++)
			printf("%d\n", *hor);

	else
		printf("Remover todos os horários.\n");


	printf("%s, %s, %s", disc->nome, disc->professor, disc->email);

}
