#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main () {
    FILE *arq;
    char nome_arq[25];
    char alterar[5];
    int opcao;
    int rrn;
    int cont_reg;

    printf("Informe o nome do arquivo: ");
    input(nome_arq, 25);

    // if ((arq = fopen(arq, "a+")) == NULL) {
    //     fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
    //     return EXIT_FAILURE;    
    // }

    printf("\n\n    PROGRAMA PARA INSERCAO E ALTERACAO DE REGISTROS\n\n");
    printf("Suas opcoes sao:\n\n");
    printf("    1. Inserir um novo registro\n");
    printf("    2. Buscar um registro por RRn para alteracoes\n");
    printf("    3. Terminar o programa");
    printf("\n\n Digite o numero da sua escolha: ");
    scanf("%d", &opcao);

    while (opcao < 3) {
        switch (opcao) {
            case 1:
                escreve_registros(nome_arq, arq);
                /*
                 * TODO: CALCULE O OFFSET DE GRAVAÇÃO
                 *       FAZER SEEK PARA OFFSET E ESCREVER BUFFER EM ARQ
                 *       INCREMENTAR CAB.CONT_REG
                */ 
            break;

            case 2:
                printf("Digite o RRN do registro: ");
                scanf("%d", &rrn);
                if (rrn >= cont_reg){
                    printf("Esse registro não existe.");
                    return EXIT_FAILURE;   
                }
                /*
                 * TODO: CALCULE O OFFSET DE GRAVAÇÃO
                 *       FAZER SEEK PARA OFFSET E ESCREVER BUFFER EM ARQ
                */
                le_registros(nome_arq, arq, rrn);
                printf("Deseja modificar esse registro?");
                printf("    Responda S ou N, seguido de <ENTER> ->");
                input(strtolower(alterar), 5);

                if (alterar == 's') {
                    escreve_registros(nome_arq, arq);
                }
                /*
                 * TODO: CALCULE O OFFSET DE GRAVAÇÃO
                 *       FAZER SEEK PARA OFFSET E ESCREVER BUFFER EM ARQ
                */
            break;
        }

        printf("\n\n    PROGRAMA PARA INSERCAO E ALTERACAO DE REGISTROS\n\n");
        printf("Suas opcoes sao:\n\n");
        printf("    1. Inserir um novo registro\n");
        printf("    2. Buscar um registro por RRn para alteracoes\n");
        printf("    3. Terminar o programa");
        printf("\n\n Digite o numero da sua escolha: ");
        scanf("%d", &opcao);
    }

    /*
    * TODO: FAZER SEEK PARA INICIO DE ARQ
    *       ESCREVA CAB EM ARQ
    */

    fclose(arq);

    return EXIT_SUCCESS;
}