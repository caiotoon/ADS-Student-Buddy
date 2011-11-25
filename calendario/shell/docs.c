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
			printf("Ação não informada. A ação deve ser -l, -a, -e ou -r.\n");
			break;

		case ERR_EXCESSO_PARAMETROS:
			puts("Muitos parâmetros foram informados.\n");
			break;

		case ERR_FALTA_PARAMETROS:
			puts("Alguns parâmetros obrigatórios não foram informados.\n");
			break;

		case ERR_COMANDO_NAO_IDENTIFICADO:
			puts("Comando inválido. Deve ser utilizado um dos comandos: atividade, disciplina, horario, tipos ou -h.\n");
			break;

	}


	printf("Digite \"calendario -h\" para obter mais informações sobre o programa.\n");
	exit(EXIT_FAILURE);

}



void escreverDoc() {

	printf(

		"\nA sintaxe geral de uso do programa é\n\n"
		"    calendario COMANDO [-ACAO [-OPCAO1 -OPCAO2 ...]]\n\n\n\n"


		"COMANDO: deve ser um dos 4 comandos de entidades (\"atividades\", \"disciplinas\",\n"
		"        \"horarios\", \"tipos\") ou um comando de CONSULTA.\n\n"


		"ACAO:    deve ser uma das ações: -l (listar), -e (editar), -a (adicionar), -r \n"
		"         (remover). Sempre que a ação -e ou -r forem utilizados deve ser\n"
		"         informada a opção -c CODIGO, onde CODIGO é o código da entidade sendo\n"
		"         removida ou atualizada.\n"


		"\n\n\nDISCIPLINAS\n"
		"   É possível cadastrar, editar, listar ou remover disciplinas. As sintaxes são:\n\n"

	);

	printf("   Para listar disciplinas:\n    ");
	docDisc(AC_LISTAR);

	printf("   Para adicionar disciplinas:\n    ");
	docDisc(AC_ADICIONAR);

	printf("   Para editar disciplinas:\n    ");
	docDisc(AC_EDITAR);

	printf("   Para remover disciplinas:\n    ");
	docDisc(AC_REMOVER);



	printf(
		"\n\nATIVIDADES\n"

		"   É possível adicionar, editar e remover atividades através do comando \"atividade\".\n"
		"   As sintaxes são:\n\n"
	);

	printf("   Para adicionar uma atividade\n    ");
	docAtiv(AC_ADICIONAR);

	printf("   Para editar uma atividade\n    ");
	docAtiv(AC_EDITAR);

	printf("   Para remover uma atividade\n    ");
	docAtiv(AC_REMOVER);


	printf(
		"\n\nCONSULTA DE ATIVIDADES\n"
		"   Para realizar consulta de atividades, deve-se utilizar um dos possíveis \n"
		"comandos de consulta:\n\n"

	);

	docAtiv(AC_LISTAR);


	printf(
		"\nHORARIOS\n"

		"   É possível listar os horários da semana com o comando:\n    "
	);

	docHora(AC_LISTAR);



	printf(
		"\n\n\nTIPOS (de atividades)\n"

		"   É possível listar os tipos de atividades com o comando:\n    "
	);

	docTipo(AC_LISTAR);


	printf("\n");

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
			printf("disciplina -l\n\n");
			break;

		case AC_EDITAR:
			printf(
					"disciplina -e -c codigo_disciplina\n"
					"           [-n nome_disciplina]\n"
					"           [-p nome_professor]\n"
					"           [-m email_professor]\n"
					"           [-h horario1,horario2,...]\n\n");
			break;

		case AC_ADICIONAR:
			printf(
					"disciplina -a \n"
					"           -n nome_disciplina\n"
					"           -p nome_professor\n"
					"           -m email_professor\n"
					"           [-h horario1,horario2,...]\n\n");
			break;


		case AC_REMOVER:
			printf(
					"disciplina -r -c codigo_disciplina\n\n"
			);
			break;

	}

}






void docAtiv( EAcao acao ) {

	switch( acao ) {

		case AC_EDITAR:
			printf(
					"atividade -e -c codigo_atividade\n"
					"          [-n titulo_atividade]\n"
					"          [-i codigo_disciplina]\n"
					"          [-d data_dd-mm-aaaa]\n"
					"          [-p pontos]\n"
					"          [-t tipo_atividade]\n\n");
			break;

		case AC_ADICIONAR:
			printf(
					"atividade -e \n"
					"          -n titulo_atividade\n"
					"          -i codigo_disciplina\n"
					"          -d data_dd-mm-aaaa\n"
					"          -p pontos\n"
					"          -t tipo_atividade\n\n");
			break;


		case AC_REMOVER:
			printf(
					"atividade -r -c codigo_atividade\n\n"
			);
			break;



		case AC_LISTAR:
			printf(
				"   calendario ontem                  Consulta atividades do dia anterior.\n"
				"   calendario hoje                   Consulta atividades do dia atual.\n"
				"   calendario amanha                 Consulta atividades do dia posterior.\n"
				"   calendario semana                 Consulta atividades da semana.\n"
				"   calendario mes                    Consulta atividades do mês.\n"
				"   calendario dd-mm-aaaa             Consulta atividades da data especificada.\n"
				"   calendario dd-mm-aaaa dd-mm-aaaa  Consulta atividades no intervalo das datas\n"
				"                                     informadas.\n\n"
			);
			break;

	}

}
