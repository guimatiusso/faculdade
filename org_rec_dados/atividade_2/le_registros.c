#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
    FILE *entrada;
    char nome_arq[25];
    char *campo;
    char buffer[TAM_BUFFER];
    short comp_reg;
    int i, j;

    printf("Informe o nome do arquivo que será lido: ");
    input(nome_arq, 25);

    if ((entrada = fopen(nome_arq, "r")) == NULL) {
        fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
        return EXIT_FAILURE;
    }

    i = 0;
    while((leia_reg(buffer, TAM_BUFFER, entrada)) > 0) {
        printf("Registro %d\n", ++i);
        j = 0;
        campo = strtok(buffer, "|");
        while(campo != NULL) {
            printf("    Campo #%d: %s\n", ++j, campo);
            campo = strtok(NULL, "|");
        }
    }

    fclose(entrada);

    return EXIT_SUCCESS;
}