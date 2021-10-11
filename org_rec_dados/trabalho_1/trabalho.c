#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

/* função que lê e retorna um char do stdin */
char input_char() {
    char str[2];
    input(str, 2);
    return str[0];
}

int input_int() {
    char str[25];
    if (input(str, 25) > 0)
        return atoi(str);
    return 0;
}

/* função para concatenar um campo campo ao buffer e 
   adicionar o delimitador de campo em seguida */
void concatena_campo(char *buffer, char *campo) {
    strcat(buffer, campo);
    strcat(buffer, DELIM_STR);
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

int ler_e_mostrar(FILE *arq, int qtde_reg, char *chave_busca) {
    char buffer[COMP_REG+1], reg[COMP_REG+1];
    char *chave, *campo;
    int rrn = 0, byte_offset;

    while (rrn <= qtde_reg) {
        byte_offset = rrn * COMP_REG + sizeof(int);
        fseek(arq, (long) byte_offset, SEEK_SET);
        fread(buffer, COMP_REG, 1, arq);
        strcpy(reg, buffer);
        chave = strtok(buffer, "|");
        if (strcasecmp(chave,chave_busca) == 0){
            campo = strtok(reg, "|");

            while (campo != NULL) {
                printf("%s|", campo);
                campo = strtok(NULL, "|");
            }
            printf("\tRRN - %d - byteoffset %d\n", rrn, byte_offset);
            return 1;
        }
        rrn++;
    }

    return 0;
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
    FILE *arq;
    char chave_busca[20];
    bool achou = false;

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {

        importacao(argv[2]);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);

        if ((arq = fopen(argv[2], "r+b")) == NULL) {
            printf("Ocorreu um erro ao abrir o arquivo");
        }

        fread(&cab, sizeof(cab), 1, arq);

        printf("Informe a chave para busca no arquivo: ");
        input(chave_busca, 25);

        achou = ler_e_mostrar(arq, cab.cont_reg, chave_busca);

        if (!achou) {
            printf("Erro: registro não encontrado");
        }

        fclose(arq);

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