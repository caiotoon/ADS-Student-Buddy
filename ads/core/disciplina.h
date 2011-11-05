/*
 * disciplina.h
 */

#ifndef _DISCIPLINA_H
#define _DISCIPLINA_H



struct _Disciplina {

	int codigo;
	char *nome;
	char *professor;
	char *email;

};

typedef struct _Disciplina Disciplina;




/*
 * Adiciona uma nova disciplina no banco e preenche o ID da disciplina apontada.
 * Retorna 0 se nenhum erro ocorrer ou algum número diferente disso caso ocorra
 * erro.
 */
int discAdicionar( Disciplina *disciplina );


/*
 * Atualiza uma entidade no banco de dados. Todas as informações serão alteradas no banco.
 * Retorna 0 se nenhum erro ocorrer e um valor diferente deste no caso contrário.
 */
int discAtualizar( const Disciplina *disciplina );


/*
 * Procura no banco a disciplina que possui o ID informado e retorna um ponteiro para a entidade
 * recuperada. Caso uma disciplina não seja encontrada com este ID, um ponteiro nulo será retornado.
 */
Disciplina *discPegar( int codigo );


/*
 * Retornará um ponteiro para um vetor de disciplinas finalizado por um ponteiro nulo. Um ponteiro
 * nulo será retornado caso ocorra algum erro.
 */
Disciplina **discListar( void );


/*
 * Extrai um resultado de um resultset para um objeto apontado por "target".
 * Espera-se que a ordem das colunas seja conhecida por esta função.
 */
static int discExtrair(void *target, void **columnsData);


/*
 * Remove uma disciplina do banco de dados e retorna 0 se nenhum erro ocorrer. Retorna um valor
 * diferente de 0 no caso de erros.
 */
int discRemover( int codigo );


#endif
