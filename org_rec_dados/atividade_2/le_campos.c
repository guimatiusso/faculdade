#include <stdio.h>
#include <stdlib.h>

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

int leia_campo(char str[], int tam, FILE *entrada){
    int i = 0;
    char c = fgetc(entrada);
    while (c != EOF && c != '|') {
        if (i < tam-1) {
            str[i] = c;
            i++;
        }
        c = fgetc(entrada);
    }
    str[i] = '\0';
    return i;
}

int main() {
    FILE *entrada;
    char nome_arq[25];
    int i=1, comp_campo;
    char campo[30];

    printf("Informe o nome do arquivo que será lido: ");
    input(nome_arq, 25);

    if ((entrada = fopen(nome_arq, "r")) == NULL) {
        fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
        return EXIT_FAILURE;
    }

    while(leia_campo(campo, 30, entrada) > 0){
        printf("Campo #%d: %s \n", i++, campo);
    }

    fclose(entrada);

    return EXIT_SUCCESS;
}