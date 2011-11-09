/*
 * atividade.h
 */

#ifndef _ATIVIDADE_H
#define _ATIVIDADE_H


#include <time.h>

struct _Atividade {

	int codigo;
	char *titulo;
	char *descricao;
	time_t data;
	float pontos;

	char tipoAtividade[3];
	int disciplina;
	int horario; // 0 indica que não há aulas desta matéria no dia marcado.

};

typedef struct _Atividade Atividade;




/*
 * Adiciona uma nova atividade no banco e preenche o ID da atividade apontada.
 * Retorna 0 se nenhum erro ocorrer e algum número diferente disso.
 */
int ativAdicionar( Atividade *atividade );


/*
 * Atualiza uma entidade no banco de dados. Todas as informações serão alteradas no banco.
 * Retorna 0 se nenhum erro ocorrer e um valor diferente deste no caso contrário.
 */
int ativAtualizar( const Atividade *atividade );


/*
 * Procura no banco a atividade que possui o ID informado e retorna um ponteiro para a entidade
 * recuperada. Caso uma atividade não seja encontrada com este ID, um ponteiro nulo será retornado.
 */
Atividade *ativPegar( int codAtividade );


/*
 * Consulta todas as atividades compreendidas em ume escopo de datas.
 *
 * Retornará um ponteiro para um vetor de atividades finalizado por um ponteiro nulo. Um ponteiro
 * nulo será retornado caso ocorra algum erro.
 */
Atividade **ativListar( time_t dataInicial, time_t dataFinal );


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida por esta função.
 */
static int ativExtrair(void *target, void **columnsData);


/*
 * Remove uma atividade do banco de dados e retorna 0 se nenhum erro ocorrer. Retorna um valor
 * diferente de 0 no caso de erros.
 */
int ativRemover( int codAtividade );



#endif
