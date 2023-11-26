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
    char str[10];                               // String temporária
    fgets(str, sizeof str, stdin);              // fgets nosso de cada dia

    char *end;                                  // Ponteiro para o final da string
    float num = strtof(str, &end);              // Converte a string para float (strtof faz exatamente isso), o ponteiro para serve para verificar se a conversão foi bem sucedida
    if (end == str || *end != '\n') {           // Se o ponteiro for igual ao início da string ou se o próximo caractere não for \n, a conversão falhou
        printf("Erro ao ler o número.\n");
        return FLT_MAX;                         // Valor de erro
    }

    return num;                                 // Retorna o número, a mesma lógica se aplica para as outras duas envolvendo número
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
    unsigned len = strlen(str);                         // Tamanho da string, unsigned porque strlen retorna um unsigned long int, só unsigned ou unsigned long, tanto faz
    if (len > 0 && str[len-1] == '\n') {                // Se o tamanho for maior que 0 e o último caractere for \n
        str[len-1] = '\0';                              // Substitui o \n por \0
    } else {
        // Limpar o buffer de entrada
        int ch;                                         // Variável temporária para armazenar o caractere, o getchar() retorna um inteiro porque ele retorna o valor do caractere na tabela ASCII
        while ((ch = getchar()) != '\n' && ch != EOF);  // Enquanto o caractere for diferente de \n e EOF, limpa o buffer, o EOF (End Of File) é para se o cu não tiver nada a vê com as calças
    }
}

// Função que calcula a distância de Levenshtein entre duas strings
int levenshtein_distance(const char *string1, const char *string2) {
    unsigned string1_len = strlen(string1); // Tamanho da string1, unsigned porque strlen retorna um unsigned long int, só unsigned ou unsigned long, tanto faz
    unsigned string2_len = strlen(string2); // Mesma coisa aqui

    if (string1_len == 0) return (int)string2_len; // Se uma das strings for vazia, retorna o tamanho da outra string
    if (string2_len == 0) return (int)string1_len; // Mesma coisa aqui

    int *d = malloc((string1_len + 1) * (string2_len + 1) * sizeof(int));   // Aloca memória para o vetor de distâncias
    if (d == NULL) {
        printf("Erro ao alocar memória para as strings\n");
        return -1;
    }

    for (int i = 0; i <= string1_len; i++)      // 1*
        d[i * (string2_len + 1)] = i;
    for (int j = 0; j <= string2_len; j++)      // 2*
        d[j] = j;

    for (int j = 1; j <= string2_len; j++) {        //3*
        for (int i = 1; i <= string1_len; i++) {   // 4*
            int substitution_cost = (string1[i - 1] == string2[j - 1]) ? 0 : 1; // 5*

            int deletion = d[i * (string2_len + 1) + j - 1] + 1;            // 6*
            int insertion = d[(i - 1) * (string2_len + 1) + j] + 1;         // 7*
            int substitution = d[(i - 1) * (string2_len + 1) + j - 1] + substitution_cost;  // 8*

            d[i * (string2_len + 1) + j] = min(deletion, min(insertion, substitution)); //9*
        }
    }

    int result = d[string1_len * (string2_len + 1) + string2_len]; // 10*
    free(d);
    return result;
}

// Função auxiliar para encontrar o menor de dois valores
int min(int a, int b) {
    return (a < b) ? a : b;
}

/* Como funciona levenshtein_distance:
 * Apesar de ser um vetor, o d é usado como uma matriz nessa implementação
 * 1. Inicializa a primeira coluna com os valores de 0 até o tamanho da string1
 * 2. Inicializa a primeira linha com os valores de 0 até o tamanho da string2
 * 3. Percorre cada caracter da string2
 * 4. Para cada caracter da string2, percorre cada caracter da string1
 * 5. Se o caracter da string1 for igual ao caracter da string2, o custo de substituição é 0, caso contrário, é 1
 * 6. Calcula o custo de deletar o caracter da string2
 * 7. Calcula o custo de inserir o caracter da string2
 * 8. Calcula o custo de substituir o caracter da string2
 * 9. Atribui o menor valor entre os três custos à posição atual da matriz
 * */


// última atualização: 2023-11-26