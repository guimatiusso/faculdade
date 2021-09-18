#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define COMP_REG 64
#define DELIM_STR "|"

struct {
    int cont_reg;
} cab; //cabeçalho do arquivo - 4 bytes

int main() {
    FILE *arq;
    int i, opcao, rrn;
    int byte_offset;
    char nome_arq[20];
    char buffer[COMP_REG+1];

    printf("Digite o nome do arquivo de registros: ");
    input(nome_arq, 20);

    if ((arq = fopen(nome_arq, "r+b")) == NULL) {
        arq = fopen(nome_arq, "w+b");
        cab.cont_reg = 0;
        fwrite(&cab, sizeof(cab), 1, arq);
    } else {
        fread(&cab, sizeof(cab), 1, arq);
    }

    while ((opcao = menu()) < 3) {

        switch(opcao) {
            case 1: // inserção
                printf("Digite os dados para o novo registro\n\n");
                pedir_campos(buffer);
                byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
                fseek(arq, (long) byte_offset, SEEK_SET);
                fwrite(buffer, COMP_REG, 1, arq);
                cab.cont_reg++;
                break;

            case 2: // busca e alteração
                rrn = pedir_rrn();

                if (rrn >= cab.cont_reg) {
                    printf("O RRN eh muito grande... RRN max = %d", cab.cont_reg-1);
                    printf("... retornando ao menu ...");
                    break;
                }

                byte_offset = rrn * COMP_REG + sizeof(cab);
                fseek(arq, (long) byte_offset, SEEK_SET);

                ler_e_mostrar(arq);

                if (alterar()) {
                    printf("\n\nDigite os novos dados do registro: \n\n");
                    pedir_campos(buffer);
                    fseek(arq, (long) byte_offset, SEEK_SET);
                    fwrite(buffer, COMP_REG, 1, arq);
                }
                break;
        }
    }

    rewind(arq);
    fwrite(&cab, sizeof(cab), 1, arq);

    fclose(arq);

    return EXIT_SUCCESS;
}