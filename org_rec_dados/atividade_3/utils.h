#ifndef _UTILS_H_
#define _UTILS_H_ 1

#include <stdio.h>

/*
 * Insere uma string em uma variável
*/
int input (char str[], int size);

/*
 * Concatena duas strings com o separador "|"
*/
void concatenar(char str_1[], char str_2[]);

short leia_reg(char buffer[], int tam, FILE *entrada);

/*
 * Escreve registros em um arquivo binario
*/
int escreve_registros (char nome_arq[], FILE *saida );

/*
 * Le registros em um arquivo binario
*/
int le_registros(char nome_arq[], FILE *entrada);

#endif