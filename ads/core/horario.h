/*
 * horario.h
 *
 *  Created on: Oct 26, 2011
 *      Author: caiotoon
 */

#include "disciplina.h"

/*
 * Toda função que retornar um horário deve associar a disciplina ao horário ou colocar um
 * ponteiro nulo como [disciplina] para indicar que não há disciplina associada a este horário.
 */

struct Horario {

	char codigo[2];
	char diaSemana[3];
	Disciplina disciplina;
	int horaInicial;
	int horaFinal;

};

typedef struct Horario Horario;



/*
 * Retornará um ponteiro para um vetor de horários e colocará no ponteiro informado por
 * [qtde] o número de horários neste vetor. Um ponteiro nulo será retornado caso ocorra
 * algum erro.
 */
Horario *horaListar( int *qtde );


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
