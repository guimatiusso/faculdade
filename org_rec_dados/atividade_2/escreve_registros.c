#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void concatenar(char str_1[], char str_2[]){
    strcat(str_1, str_2);
    strcat(str_1, "|");
}

int main () {
    char nome_arq[25];
    char campo[25];
    char buffer[120];
    char *nome_campos[] = {"Nome", "Endereco", "Cidade", "UF", "CEP"};
    FILE *saida;
    short comp_reg;

    printf("Informe o nome desejado para o arquivo: ");
    input(nome_arq, 25);

    if ((saida = fopen(nome_arq, "w")) == NULL) {
        fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
        return EXIT_FAILURE;
    }

    printf("Informe um sobrenome: ");

    while ((input(campo, 25)) > 0) {
        buffer[0] = '\0';
        concatenar(buffer, campo);

        for(int i=0; i<5; i++){
            printf("%s: ", nome_campos[i]);
            input(campo, 25);
            concatenar(buffer, campo);
        }

        comp_reg = strlen(buffer);
        fwrite(&comp_reg, sizeof(short), 1, saida);
        fwrite(buffer, sizeof(char), comp_reg, saida);

        printf("Informe outro sobrenome: ");
    }

    fclose(saida);

    return EXIT_SUCCESS;
}