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

void strtolower (char str_1[], char str_2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        s2[i] = tolower(s1[i]);
        i++;
    }
    s2[i] = '\0';
}

short leia_reg(char buffer[], int tam, FILE *entrada){
    short comp_reg;

    if ((fread(&comp_reg ,sizeof(short), 1, entrada)) > 0 && comp_reg < tam) {
        fread(buffer, sizeof(char), comp_reg, entrada);
        buffer[comp_reg] = '\0';
        return comp_reg;
    }
}

int escreve_registros (char nome_arq[], FILE *saida) {
    char campo[25];
    char buffer[120];
    char *nome_campos[] = {"Nome", "Endereco", "Cidade", "UF", "CEP"};
    short comp_reg;

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

int le_registros(char nome_arq[], FILE *entrada){
    char *campo;
    char buffer[TAM_BUFFER];
    short comp_reg;
    int i, j;

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