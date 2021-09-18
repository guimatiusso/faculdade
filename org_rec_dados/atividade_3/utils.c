#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COMP_REG 64
#define DELIM_STR "|"

char *prompt[] = {
    "    Sobrenome: ",
    "Primeiro nome: ",
    "     Endereco: ",
    "       Cidade: ",
    "       Estado: ",
    "          CEP: ",
    "" // string vazia para encerrar o loop
};

/* função que lê uma linha do stdin para a string str */
int input(char str[], int size) {
    int i = 0;
    char c = getchar();
    while (c != '\n') {
        if (i < size-1) {
            str[i] = c;
            i++;
        }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

/* função que lê e retorna um número inteiro do stdin */
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

/* Converte o char si para UPPERCASE e retorna em so */
char ucase(char si){
    char so = (si >= 'a' && si <= 'z') ? si & 0x5f : si;
    return so;
}

/* função que lê e retorna um char do stdin */
char input_char() {
    char str[2];
    input(str, 2);
    return str[0];
}

/* função local para perguntar ao usuario pela próx. operação
   retorna um valor numérico */
int menu() {
    int opcao;
    char str[5];
    
    printf("\n\nPROGRAMA PARA CRIACAO E ALTERACAO DE ARQUIVO\n");
    printf("\n\nSuas opcoes sao:\n\n");
    printf("\t1. Adicionar um registro ao final do arquivo\n");
    printf("\t2. Recuperar um registro por RRN para alteracoes \n");
    printf("\t3. Terminar o programa\n\n");
    printf("Digite o numero da sua escolha: ");
    opcao = input_int();
    return opcao;

}

/* função para a entrada dos campos do registro,
   escrevendo-os no buffer passado por parâmetro */
void pedir_campos(char buffer[]) {
    int i;
    char campo[50];

    // limpa o buffer (inicializa como uma string vazia)
    buffer[0] = '\0';

    // obtem os campos
    for (i = 0; prompt[i] != ""; i++) {
        printf("%s", prompt[i]);
        input(campo, 50);
        concatena_campo(buffer, campo);
    }

    /* Atenção! Esta função não é segura, pois deixa que o usuário
       informe campos que, juntos, ultrapassem a capacidade do registro.
       Você pode arrumar isso se desejar...
    */
    
}

/* função para a entrada do RRN do registro a ser buscado/alterado */
int pedir_rrn() {
    int rrn;

    printf("\n\nDigite o RRN do registro: ");
    rrn = input_int();
    return rrn;
}

/* função que lê e mostra um registro, sem seek.
   a leitura começa na posição atual do arquivo */
void ler_e_mostrar(FILE *arq) {
    char buffer[COMP_REG+1];
    char *campo;

    fread(buffer, COMP_REG, 1, arq);

    printf("\n\n\n\nConteudo do registro\n");
    campo = strtok(buffer, "|");
    while (campo != NULL) {
        printf("\t%s\n",campo);
        campo = strtok(NULL, "|");
    }
}

/* função para perguntar ao usuário se ele quer modificar o registro ou nao
   Retorna 1 para SIM e 0 para NAO */
int alterar() {
    char resposta;

    printf("\n\nVoce quer modificar este registro?\n");
    printf("    Responda S ou N, seguido de <ENTER>: ");
    resposta = ucase(input_char());
    return ((resposta == 'S'));
}