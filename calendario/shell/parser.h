

/*
 * interpretador.h
 */

#ifndef __PARSER_H
#define __PARSER_H


/*
 * A enumeration of the existing commands.
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
 * Enumeration of existing actions.
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
 * Starts the command parsing.
 */
void parse(int argc, char **argv);


/**
 * Reads the command and return the matching command.
 */
EComando lerComando( char *name );


/*
 * Validate the action of a command and return an identified action. In case of invalid action,
 * or more than one action is asked, the software must stop and inform the error.
 *
 * The list of allowing actions must be ended by -1.
 */
EAcao parseAcao( int argc, char **argv, const EAcao acoesPermitidas[] );


/*
 * Parse and execute a activity command.
 */
void execComandoAtiv( int argc, char **argv, EAcao acao );


/*
 * parse and execute a schedule command.
 */
void execComandoHora( int argc, char **argv, EAcao acao );


/*
 * Parse and execute a activity type command.
 */
void execComandoTipo( int argc, char **argv, EAcao acao );


/*
 * Parse and execute a discipline command.
 */
void execComandoDisc( int argc, char **argv, EAcao acao );


/*
 * Parse and execute a help command.
 */
void execComandoAjuda( int argc, char **argv, EAcao acao );


/*
 * Parse and execute a query command.
 */
void execComandoConsulta( int argc, char **argv );



/*
 * Returns the option or null.
 */
int opt_get( int argc, const char **argv, const char *mandatoryOpts, const char *validOpts, char **argplacer );


/*
 * Reset option parser.
 */
void opt_reset( void );



#endif
