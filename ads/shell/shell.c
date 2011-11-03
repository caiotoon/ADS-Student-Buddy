/*
 * shell.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "docs.h"
#include "../lib/sqlite3.h"
#include "../lib/utils.h"
#include "../core/horario.h"
#include "../core/tipo_atividade.h"


extern const char ACOES[];

extern const EAcao AC_VALIDAS_ATIVIDADE[];
extern const EAcao AC_VALIDAS_DISCIPLINA[];
extern const EAcao AC_VALIDAS_TIPO_ATIV[];
extern const EAcao AC_VALIDAS_HORARIO[];

/*
 * Ponto de entrada do programa.
 *
 * Este método tem a responsabilidade de identificar o comando e a ação da linha de código. Após a identificação,
 * ele deve passar os argumentos para a função adequada, a fim de finalizar o pedido.
 */
int main(int argc, char **argv) {

	EComando com;
	EAcao acao;


	if( argc < 2 )
		escreverErro( ERR_SEM_COMANDO, NULL );

	// Identifica o comando.
	com = lerComando(argv[1]);

	if( com != COM_CONSULTA && argc < 3 )
		escreverErro( ERR_SEM_ACAO, NULL );


	switch( com ) {

		case COM_DISCIPLINA:
			puts("Comando de disciplina.");
			acao = parseAcao(argc, argv, AC_VALIDAS_DISCIPLINA);
			break;

		case COM_HORARIO:
			puts("Comando de horário.");
			acao = parseAcao(argc, argv, AC_VALIDAS_HORARIO);
			break;

		case COM_ATIVIDADE:
			puts("Comando de atividade.");
			acao = parseAcao(argc, argv, AC_VALIDAS_ATIVIDADE);
			break;

		case COM_TIPO_ATIVIDADE:
			puts("Comando de tipos de atividades.");
			acao = parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV);
			break;

		case COM_CONSULTA:
			puts("Comando de consulta.");
			//acao = parseAcao(argc, argv, AC_VALIDAS_TIPO_ATIV);
			acao = AC_LISTAR;
			break;

		case COM_AJUDA:
			puts("Comando de ajuda.");
			acao = AC_LISTAR;
			break;

	}


	printf("Ação: -%c\n", ACOES[acao]);

	int a;
	TipoAtividade **atividades, **ptr;
	TipoAtividade *curr;
	atividades = tipoListar(&a);

	for( ptr = atividades; *ptr; *ptr++ ) {

		curr = *ptr;
		printf(":: [%s] %s\n", curr->codigo, curr->descricao);

	}

	db_listFree(atividades);
	printf("Fim.");

	return EXIT_SUCCESS;

}

