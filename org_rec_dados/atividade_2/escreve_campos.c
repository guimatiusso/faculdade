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

int main () {
    char nome_arq[25];
    char sobrenome[25];
    char nome[25];
    char endereco[30];
    char cidade[15];
    char uf[3];
    char cep[9];
    FILE *saida;

    printf("Informe o nome desejado para o arquivo: ");
    input(nome_arq, 25);

    if ((saida = fopen(nome_arq, "w")) == NULL) {
        fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
        return EXIT_FAILURE;
    }

    printf("Informe um sobrenome: ");

    while ((input(sobrenome, 25)) > 0) {
        printf("Informe o nome: ");
        input(nome, 25);

        printf("Informe o endereço: ");
        input(endereco, 30);

        printf("Informe a cidade: ");
        input(cidade, 15);

        printf("Informe a UF: ");
        input(uf, 3);

        printf("Informe o CEP: ");
        input(cep, 9);

        fprintf(saida, "%s|%s|%s|%s|%s|%s|", sobrenome, nome, endereco, cidade, uf, cep);

        printf("Informe outro sobrenome: ");
    }

    fclose(saida);
    return EXIT_SUCCESS;
}