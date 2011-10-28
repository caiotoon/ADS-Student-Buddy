/*
 * parser_consulta.h
 */

#ifndef PARSER_CONSULTA_H_
#define PARSER_CONSULTA_H_


/*
 * Interpreta o comando e consulta e escreve as datas iniciais e finais nos ponteiros informados como parâmetros.
 */
void parseCons( int argc, char **argv, time_t *dataInicial, time_t *dataFinal );


#endif /* PARSER_CONSULTA_H_ */
