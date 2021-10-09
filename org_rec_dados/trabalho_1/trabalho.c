#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMP_REG 64
#define DELIM_STR "|"

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

/* função para concatenar um campo campo ao buffer e 
   adicionar o delimitador de campo em seguida */
void concatena_campo(char *buffer, char *campo) {
    strcat(buffer, campo);
    strcat(buffer, DELIM_STR);
}


int leia_campo(char str[], int tam, FILE *entrada){
    int i = 0, j;
    char c = fgetc(entrada);
    j = 0;
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

struct {
    int cont_reg;
} cab; //cabeçalho do arquivo - 4 bytes

int importacao (char str[]) {
    FILE *entrada, *saida;
    char nome_arq[25];
    int i=1, j=1;
    int byte_offset;
    char campo[30];
    char buffer[COMP_REG+1];

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", str);

        if ((entrada = fopen(str, "r")) == NULL) {
            fprintf(stderr, "O arquivo %s não está disponível", nome_arq);
            return EXIT_FAILURE;
        }

        if ((saida = fopen("dados.dat", "w+b")) == NULL) {
            fprintf(stderr, "O arquivo dados.dat não está disponível");
            return EXIT_FAILURE;
        }

        cab.cont_reg = 0;
        fwrite(&cab, sizeof(cab), 1, saida);

        while(leia_campo(campo, 30, entrada) > 0){
            if (i == 1) {
                // limpa o buffer (inicializa como uma string vazia)
                buffer[0] = '\0';
            }

            concatena_campo(buffer, campo);
            i++;

            if (i == 5) {

                byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
                fseek(saida, (long) byte_offset, SEEK_SET);
                fwrite(buffer, COMP_REG, 1, saida);
                cab.cont_reg++;
                i = 1;
            }
        }

        rewind(saida);
        fwrite(&cab, sizeof(cab), 1, saida);

        fclose(entrada);
        fclose(saida);
}

int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {

        importacao(argv[2]);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        // executa_operacoes(argv[2]);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {

        printf("Modo de impressao da PED ativado ...\n");
        // imprime_ped();

    } else {

        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    return 0;
}