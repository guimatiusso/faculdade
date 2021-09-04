#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_BUFFER 120

int input (char str[], int size) {
    int i = 0;
    char c = getchar();
    while (c != '\n') {
        if (i <size-1) {
            str[i] = c;
            i++;
        }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

short leia_reg(char buffer[], int tam, FILE *entrada){
    short comp_reg;

    if ((fread(&comp_reg ,sizeof(short), 1, entrada)) > 0 && comp_reg < tam) {
        fread(buffer, sizeof(char), comp_reg, entrada);
        buffer[comp_reg] = '\0';
        return comp_reg;
    }
}

int main () {
    FILE *entrada;
    char nome_arq[25];
    char sobrenome_busca[25];
    char *sobrenome;
    char buffer[TAM_BUFFER];
    char *campo;
    bool achou = false;
    short comp_reg;
    int i;

    printf("Informe o nome do arquivo: ");
    input(nome_arq, 25);

    if ((entrada = fopen(nome_arq, "r")) == NULL) {
        fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
        return EXIT_FAILURE;    
    }

    printf("Informe o sobrenome para busca no arquivo: ");
    input(sobrenome_busca, 25);

    while (!achou && (leia_reg(buffer, TAM_BUFFER, entrada)) > 0) {
        sobrenome = strtok(buffer, "|");  

        if (strcmp(sobrenome,sobrenome_busca) == 0){
            achou = true;
        }
    }

    if (!achou) {
        printf("\n\nRegistro nao encontrado.\n\n");
        return EXIT_FAILURE; 
    }

    if (achou) {
        printf("\n\nRegistro encontrado:\n\n");
        i = 1;
        printf("    Campo #%d: %s \n", i, sobrenome);
        campo = strtok(NULL, "|");

        while (campo != NULL) {
            printf("    Campo #%d: %s \n", ++i, campo);
            campo = strtok(NULL, "|");
        }
    }

    fclose(entrada);

    return EXIT_SUCCESS;
}