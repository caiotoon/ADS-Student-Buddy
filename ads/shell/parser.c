/*
 * parser.c
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser_atividade.h"
#include "parser_disciplina.h"
#include "parser_consulta.h"
#include "output.h"
#include "docs.h"

#include "../lib/utils.h"

#include "../core/atividade.h"
#include "../core/disciplina.h"
#include "../core/horario.h"
#include "../core/tipo_atividade.h"
#include "../core/database.h"



const char ACOES[]					= {'a', 'e', 'l', 'r'};

const EAcao AC_VALIDAS_ATIVIDADE[] 	= {AC_ADICIONAR, AC_EDITAR, AC_REMOVER, -1};
const EAcao AC_VALIDAS_DISCIPLINA[] = {AC_ADICIONAR, AC_EDITAR, AC_LISTAR, AC_REMOVER, -1};
const EAcao AC_VALIDAS_TIPO_ATIV[]	= {AC_LISTAR, -1};
const EAcao AC_VALIDAS_HORARIO[]	= {AC_LISTAR, -1};




#define CONT_COMANDOS 20;
static char *COMANDOS[]		= {
	"disciplina", "disc", "disciplinas", "discs",
	"atividade", "ativ", "atividades", "ativs",
	"horario", "horarios", "hora", "horas",
	"tipos", "tipo",
	"ajuda", "ontem", "hoje", "amanha", "semana", "mes"
};

static EComando MAPA_COMANDOS[]	= {
	COM_DISCIPLINA, COM_DISCIPLINA, COM_DISCIPLINA, COM_DISCIPLINA,
	COM_ATIVIDADE, COM_ATIVIDADE, COM_ATIVIDADE, COM_ATIVIDADE,
	COM_HORARIO, COM_HORARIO, COM_HORARIO, COM_HORARIO,
	COM_TIPO_ATIVIDADE, COM_TIPO_ATIVIDADE,
	COM_AJUDA,
	COM_CONSULTA, COM_CONSULTA, COM_CONSULTA, COM_CONSULTA, COM_CONSULTA
};



static EAcao findAction(int argc, char **argv);



/*
 * Identifica o comando baseado na lista de comandos existentes no vetor acima.
 */
EComando lerComando(char *comando) {

	time_t t;
	int i, iLimit;
	struct tm *refDate;

	strToLower(comando);
	iLimit = CONT_COMANDOS;

	for(i=0; i < iLimit; i++)
		if(!strcmp(comando, COMANDOS[i]))
			return MAPA_COMANDOS[i];


	t = time(NULL);
	refDate = localtime(&t);

	if( strptime(comando, "%d-%m-%Y", refDate) )
		return COM_CONSULTA;

	escreverErro(ERR_COMANDO_NAO_IDENTIFICADO, NULL);
	return -1;

}



EAcao parseAcao( int argc, char **argv, const EAcao acoesPermitidas[] ) {

	register int i = 0;
	EAcao acao = findAction(argc, argv);

	while(acoesPermitidas[i] >= 0) {

		if( acoesPermitidas[i++] == acao )
			return acao;

	}


	fprintf(stderr, "Nenhuma ação válida para o comando foi informada.\n");
	exit(1);

}


static EAcao findAction(int argc, char **argv) {

	register int i;

	for(i=0; i<argc; i++) {

		if( argv[i][0] == '-' ) {

			switch(argv[i][1]) {

				case 'a':
					return AC_ADICIONAR;

				case 'e':
					return AC_EDITAR;

				case 'l':
					return AC_LISTAR;

				case 'r':
					return AC_REMOVER;

			}

		}


	}


	return AC_NONE;

}


void parse(int argc, char **argv) {

	EComando com;
	EAcao acao;


	if( argc < 2 )
		escreverErro( ERR_SEM_COMANDO, NULL );

	// Identifica o comando.
	com = lerComando(argv[1]);

	if( com != COM_CONSULTA && com != COM_AJUDA && argc < 3 )
		escreverErro( ERR_SEM_ACAO, NULL );


	switch( com ) {

		case COM_DISCIPLINA:
			acao = parseAcao(argc, argv, AC_VALIDAS_DISCIPLINA);
			execComandoDisc(argc, argv, acao);
			break;

		case COM_HORARIO:
			acao = parseAcao(argc, argv, AC_VALIDAS_HORARIO);
			execComandoHora(argc, argv, acao);
			break;

		case COM_ATIVIDADE:
			acao = parseAcao(argc, argv, AC_VALIDAS_ATIVIDADE);
			execComandoAtiv(argc, argv, acao);
			break;

		case COM_TIPO_ATIVIDADE:
			execComandoTipo(argc, argv, parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV));
			break;

		case COM_CONSULTA:
			execComandoConsulta(argc, argv, parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV));
			break;

		case COM_AJUDA:
			escreverDoc();
			break;

	}

}


void execComandoDisc( int argc, char **argv, EAcao acao ) {

	Disciplina *disc, **discs;
	int *hor=NULL, *horPtr=NULL, codigo;


	switch( acao ) {

		case AC_ADICIONAR:

			disc = parseDiscAdicionar(argc, argv, &hor);

			if( discAdicionar(disc) ) {
				fprintf(stderr, "Não foi possível adicionar a disciplina informada.\n");
				exit(1);
			}


			if( hor ) {

				for(horPtr=hor; *horPtr; horPtr++)
					horaAssociarDisciplina(*horPtr, disc->codigo);

			}

			free(disc);
			free(hor);

			break;

		case AC_EDITAR:

			disc = parseDiscEditar(argc, argv, &hor);

			if( discAtualizar(disc) ) {
				fprintf(stderr, "Não foi possível adicionar a disciplina informada.\n");
				exit(1);
			}

			if( hor ) {

				horaDesassociarDisciplina(disc->codigo);

				for(horPtr=hor; *horPtr; horPtr++)
					horaAssociarDisciplina(*horPtr, disc->codigo);

			}


			free(disc);
			free(hor);

			break;

		case AC_LISTAR:

			discs = discListar();
			outListarDisciplinas(discs);

			db_listFree(discs);

			break;

		case AC_REMOVER:

			codigo = parseDiscRemover(argc, argv);
			discRemover(codigo);

			break;

	}

}


void execComandoAtiv( int argc, char **argv, EAcao acao ) {

	Atividade *ativ;
	int codigo;


	switch( acao ) {

		case AC_ADICIONAR:

			ativ = parseAtivAdicionar(argc, argv);

			if( ativAdicionar(ativ) ) {
				fprintf(stderr, "Não foi possível adicionar a atividade informada.\n");
				exit(1);
			}


			free(ativ);

			break;

		case AC_EDITAR:

			ativ = parseAtivEditar(argc, argv);

			if( ativAtualizar(ativ) ) {
				fprintf(stderr, "Não foi possível editar a atividade informada.\n");
				exit(1);
			}


			free(ativ);

			break;

		case AC_REMOVER:

			codigo = parseAtivRemover(argc, argv);
			ativRemover(codigo);

			break;

	}

}


void execComandoHora( int argc, char **argv, EAcao acao ) {

	Horario **horas;

	switch( acao ) {

		case AC_LISTAR:

			horas = horaListar();
			outListarHorarios(horas);

			db_listFree(horas);

			break;

	}

}


void execComandoTipo( int argc, char **argv, EAcao acao ) {

	TipoAtividade **tipos;

	switch( acao ) {

		case AC_LISTAR:

			tipos = tipoListar();
			outListarTiposAtividades(tipos);

			db_listFree(tipos);

			break;

	}

}


void execComandoConsulta( int argc, char **argv, EAcao acao ) {

	Atividade **ativs;
	time_t start, end;
	parseCons(argc, argv, &start, &end);

	if( start == 0 || end == 0 ) {
		fprintf(stderr, "Não foi possível realizar a busca.\n");
		exit(1);
	}


	ativs = ativListar(&start, &end);
	outListarAtividades(&start, &end, ativs);

	db_listFree(ativs);

}







static int opt_current = 1;

int opt_get( int argc, const char **argv, const char *mandatoryOpts, const char *validOpts, char **argplacer ) {

	int opt;
	char *arg;
	char optNeedle[2] = {' ', '\0'};


	if( opt_current >= argc )
		return -1;

	for( ; opt_current < argc && *argv[opt_current] != '-'; opt_current++ );

	if( opt_current == argc ) {

		opt_reset();

		*argplacer = NULL;
		return -1;

	}

	opt = argv[opt_current][1];
	optNeedle[0] = opt;

	if( !strstr(validOpts, optNeedle) ) {
		fprintf(stderr, "Opção '-%c' não reconhecida.\n", opt);
		exit(1);
	}

	if( opt_current < argc-1 && *argv[opt_current+1] != '-' ) {

		*argplacer = argv[opt_current+1];
		opt_current += 2;

	} else {

		if( strstr(mandatoryOpts, optNeedle) ) {

			fprintf(stderr, "A opção -%c exige um argumento.\n", opt);
			exit(1);

		}

		*argplacer = NULL;
		opt_current++;

	}


	return opt;

}


void opt_reset( void ) {
	opt_current = 1;
}
