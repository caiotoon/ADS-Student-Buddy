/*
 * horario.h
 */

#ifndef _HORARIO_H
#define _HORARIO_H



#include "disciplina.h"
#include <time.h>

/*
 * Toda função que retornar um horário deve associar a disciplina ao horário ou colocar um
 * ponteiro nulo como [disciplina] para indicar que não há disciplina associada a este horário.
 */

struct _Horario {

	int codigo;
	char diaSemana[3];
	Disciplina *disciplina;
	time_t horaInicial;
	time_t horaFinal;

};

typedef struct _Horario Horario;



/*
 * Retornará um ponteiro para um vetor de horários finalizado por um ponteiro nulo. Um ponteiro nulo será retornado
 * caso ocorra algum erro.
 */
Horario **horaListar(void);


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida por esta função.
 */
static int horaExtrair(void *target, void **columnsData);


/*
 * Associa uma disciplina à um determinado horário e retorna 0 se nenhum erro ocorrer.
 */
int horaAssociarDisciplina( int codHorario, int codDisciplina );


/*
 * Retorna um horário baseado no dia da semana e na posicao do horário. [diaSemana] será um array de caracteres que
 * conterá as três primeiras letras do dia semana, e [horario] será 1 ou 2, significando, respectivamente, o primeiro
 * ou o segundo horário. A consulta deve ser feita baseando-se nos horários de início e término da aula.
 *
 * Um ponteiro nulo será retornado caso não seja possível encontrar este horário.
 */
Horario *horaPegar( char diaSemana[3], int horario );




#endif
