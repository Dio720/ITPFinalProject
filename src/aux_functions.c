// Funções auxiliares utéis
// Created by dio on 25/11/23.
//

#include "aux_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>


// Função que lê um float do usuário
float read_float_from_user() {
    char str[10];                                   // String temporária
    fgets(str, sizeof str, stdin);                 // fgets nosso de cada dia

    char *end;                                   // Ponteiro para o final da string
    float num = strtof(str, &end);              // Converte a string para float (strtof faz exatamente isso), o ponteiro para serve para verificar se a conversão foi bem sucedida
    if (end == str || *end != '\n') {          // Se o ponteiro for igual ao início da string ou se o próximo caractere não for \n, a conversão falhou
        printf("Erro ao ler o número.\n");
        return FLT_MAX;                      // Valor de erro
    }

    return num;                            // Retorna o número, a mesma lógica se aplica para as outras duas envolvendo número
}

// Função que lê um inteiro do usuário
int read_integer_from_user() {
    char str[10];
    fgets(str, sizeof str, stdin);

    char *end;
    long num = strtol(str, &end, 10);
    if (end == str || *end != '\n' || num > INT_MAX) {
        printf("Erro ao ler o número.\n");
        return INT_MAX;
    }

    return (int)num;
}


// Função que lê um double do usuário
double read_double_from_user() {
    char str[10];
    fgets(str, sizeof str, stdin);

    char *end;
    double num = strtod(str, &end);
    if (end == str || *end != '\n') {
        printf("Erro ao ler o número.\n");
        return DBL_MAX;
    }

    return num;
}

// Função que remove o \n do final de uma string
void remove_newline(char *str) {
    int len = strlen(str);                          // Tamanho da string
    if (len > 0 && str[len-1] == '\n') {           // Se o tamanho for maior que 0 e o último caractere for \n
        str[len-1] = '\0';                         // Substitui o \n por \0
    } else {
        // Limpar o buffer de entrada
        int ch;                                          // Variável temporária para armazenar o caractere, o getchar() retorna um inteiro porque ele retorna o valor do caractere na tabela ASCII
        while ((ch = getchar()) != '\n' && ch != EOF);  // Enquanto o caractere for diferente de \n e EOF, limpa o buffer, o EOF (End Of File) é para se o cu não tiver nada a vê com as calças
    }
}

// última atualização: 2023-11-25