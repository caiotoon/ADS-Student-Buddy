

/*
 * interpretador.h
 */

#ifndef __PARSER_H
#define __PARSER_H


/*
 * Enumeração de comandos existentes.
 */
enum _Comando {
	COM_DISCIPLINA,
	COM_ATIVIDADE,
	COM_HORARIO,
	COM_CONSULTA,
	COM_TIPO_ATIVIDADE,
	COM_AJUDA
};

typedef enum _Comando EComando;


/*
 * Enumeração de ações existentes no programa.
 */
enum _Acao {
	AC_ADICIONAR,
	AC_EDITAR,
	AC_LISTAR,
	AC_REMOVER,
	AC_NONE
};

typedef enum _Acao EAcao;


/*
 * Inicia a interpretação do comando.
 */
void parse(int argc, char **argv);


/**
 * Lê o comando e retorna o comando adequado.
 */
EComando lerComando( char *name );


/*
 * Valida a ação de um comando e retorna a ação identificada. Caso seja solicitada uma ação não permitida, ou
 * caso mais de uma ação seja pedida, o programa deve ser finalizado com mensagem de erro.
 *
 * A lista de açoes permitidas será finalizada com o número -1.
 */
EAcao parseAcao( int argc, char **argv, const EAcao acoesPermitidas[] );


/*
 * Executa um comando de atividade.
 */
void execComandoAtiv( int argc, char **argv, EAcao acao );


/*
 * Executa um comando de horário.
 */
void execComandoHora( int argc, char **argv, EAcao acao );


/*
 * Executa um comando de tipo de atividade.
 */
void execComandoTipo( int argc, char **argv, EAcao acao );


/*
 * Executa um comando de disciplina.
 */
void execComandoDisc( int argc, char **argv, EAcao acao );


/*
 * Executa o comando de ajuda.
 */
void execComandoAjuda( int argc, char **argv, EAcao acao );


/*
 * Executa um comando de consulta.
 */
void execComandoConsulta( int argc, char **argv );



/*
 * Retorna uma opção ou nulo.S
 */
int opt_get( int argc, const char **argv, const char *mandatoryOpts, const char *validOpts, char **argplacer );


/*
 * Reseta o parser de opções.
 */
void opt_reset( void );



#endif
