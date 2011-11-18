/*
 * docs.c
 */

#include "docs.h"
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"


void escreverErro( EDocErro erro, char *args[] ) {

	switch( erro ) {

		case ERR_SEM_COMANDO:
			printf("Não foi identificado um comando.\n");
			break;

		case ERR_SEM_ACAO:
			printf("Ação não informada.\n");
			break;

		case ERR_EXCESSO_PARAMETROS:
			puts("Muitos parâmetros foram informados.\n");
			break;

		case ERR_FALTA_PARAMETROS:
			puts("Alguns parâmetros obrigatórios não foram informados.\n");
			break;

		case ERR_COMANDO_NAO_IDENTIFICADO:
			puts("Comando inválido. Deve ser utilizado um dos comandos: atividade, disciplina, horario, tipos ou ajuda.\n");
			break;

	}


	printf("Digite \"ads ajuda\" para obter mais informações sobre o programa.\n");
	exit(EXIT_FAILURE);

}



void escreverDoc() {


}



void docHora( EAcao acao ) {

	switch( acao ) {

		case AC_LISTAR:
			printf("horario -l\n");
			break;

	}

}


void docTipo( EAcao acao ) {

	switch( acao ) {

		case AC_LISTAR:
			printf("tipo -l\n");
			break;

	}

}


void docDisc( EAcao acao ) {

	switch( acao ) {

		case AC_LISTAR:
			printf("\ndisciplina -l\n");
			break;

		case AC_EDITAR:
			printf(
					"\ndisciplina -e -c codigo_disciplina\n"
					"           [-n nome_disciplina]\n"
					"           [-p nome_professor]\n"
					"           [-m email_professor]\n"
					"           [-h horario1,horario2,...]\n\n");
			break;

		case AC_ADICIONAR:
			printf(
					"\ndisciplina -a \n"
					"           -n nome_disciplina\n"
					"           -p nome_professor\n"
					"           -m email_professor\n"
					"           [-h horario1,horario2,...]\n\n");
			break;


		case AC_REMOVER:
			printf(
					"\ndisciplina -r -c codigo_disciplina\n\n"
			);
			break;

	}

}






void docAtiv( EAcao acao ) {

	switch( acao ) {

		case AC_EDITAR:
			printf(
					"\n"
					"atividade -e -c codigo_atividade\n"
					"          [-n titulo_atividade]\n"
					"          [-i codigo_disciplina]\n"
					"          [-d data_dd-mm-aaaa]\n"
					"          [-p pontos]\n"
					"          [-t tipo_atividade]\n\n");
			break;

		case AC_ADICIONAR:
			printf(
					"\n"
					"atividade -e \n"
					"          -n titulo_atividade\n"
					"          -i codigo_disciplina\n"
					"          -d data_dd-mm-aaaa\n"
					"          -p pontos\n"
					"          -t tipo_atividade\n\n");
			break;


		case AC_REMOVER:
			printf(
					"\natividade -r -c codigo_atividade\n\n"
			);
			break;

	}

}
