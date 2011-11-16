/*
 * docs.c
 */

#include "docs.h"
#include <stdio.h>
#include <stdlib.h>


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



