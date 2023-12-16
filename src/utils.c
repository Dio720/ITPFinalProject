// Descrição Funções auxiliares utéis
// Created by dio on 25/11/23.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Implementar todas as funções auxiliares

double readDouble() {
    char string[50];
    char *endptr;

    fgets(string, 50, stdin);

    double output = strtod(string, &endptr);

    if (endptr != string && *endptr == '\n')
        return output;
    else {
        fprintf(stderr,"Erro: A string precisa ser do tipo double.\n");
        return readDouble();
    }
}

float readFloat() {
    char string[50];
    char *endptr;

    fgets(string, 50, stdin);

    float output = strtof(string, &endptr);

    if (endptr != string && *endptr == '\n')
        return output;
    else {
        fprintf(stderr,"Erro: A string precisa ser do tipo float.\n");
        return readFloat();
    }

}

int readInteger() {
    char input[50];
    char *endptr;

    fgets(input, 50, stdin);

    long output = strtol(input, &endptr, 10);

    if (endptr != input && (*endptr == '\n' || *endptr == '\0')) {
        return (int)output;
    } else {
        fprintf(stderr,"Erro: A entrada precisa ser do tipo inteiro.\n");
        return readInteger();
    }
}

void removeNewLine(char *string) {
    if (string == NULL)
        return;

    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}


char readChar() {
    char input[50];

    fgets(input, 50, stdin);

    if (strlen(input) == 2 && input[1] == '\n') {
        return input[0];
    } else {
        fprintf(stderr,"Erro: A entrada precisa ser do tipo char.\n");
        return readChar();
    }
}

void readString(char *string, int maxLength) {
    fgets(string, maxLength, stdin);
    removeNewLine(string);
}

int minimumOfTwo(int x, int y) {
    return (x < y) ? x : y;
}

int calculateStringSimilarity(const char *string1, const char *string2) {
    int string1Len = strlen(string1);
    int string2Len = strlen(string2);

    if (string1Len == 0) return string2Len;
    if (string2Len == 0) return string1Len;

    int *distanceMatrix = malloc((string1Len + 1) * (string2Len + 1) * sizeof(int));
    if (distanceMatrix == NULL) {
        fprintf(stderr,"Erro: Falha ao alocar memória.\n");
        return -1;
    }

    for (int i = 0; i <= string1Len; i++) {
        distanceMatrix[i * (string2Len + 1)] = i;
    }
    for (int j = 0; j <= string2Len; j++) {
        distanceMatrix[j] = j;
    }

    for (int j = 1; j <= string2Len; j++) {
        for (int i = 1; i <= string1Len; i++) {
            int substitutionCost;
            if (string1[i - 1] == string2[j - 1])
                substitutionCost = 0;
            else
                substitutionCost = 1;

            int deletion = distanceMatrix[i * (string2Len + 1) + j - 1] + 1;
            int insertion = distanceMatrix[(i - 1) * (string2Len + 1) + j] + 1;
            int substitution = distanceMatrix[(i - 1) * (string2Len + 1) + j - 1] + substitutionCost;

            distanceMatrix[i * (string2Len + 1) + j] = minimumOfTwo(minimumOfTwo(deletion, insertion), substitution);
        }
    }

    int result = distanceMatrix[string1Len * (string2Len + 1) + string2Len];
    free(distanceMatrix);
    return result;
}

char* suggestName(const char *incorrectName, const char **existingNames, int numNames) {
    int bestDistance = -1;
    const char *bestSuggestion = NULL;
    int threshold = 3;

    for (int i = 0; i < numNames; ++i) {
        int distance = calculateStringSimilarity(incorrectName, existingNames[i]);

        if (bestDistance == -1 || distance < bestDistance) {
            bestDistance = distance;
            bestSuggestion = existingNames[i];
        }

        if (distance < threshold) break;
    }

    if (bestSuggestion != NULL) {
        char *suggestion = strdup(bestSuggestion);
        return suggestion;
    }

    return NULL;
}

/**
 * Função: readDouble
 * ------------------
 * Lê um valor double do usuário.
 *
 * A função segue os seguintes passos:
 * 1. Lê uma string do usuário.
 * 2. Converte a string para um valor double.
 * 3. Verifica se a conversão foi bem-sucedida. Se não foi, imprime uma mensagem de erro e chama a si mesma recursivamente.
 * 4. Retorna o valor double convertido.
 *
 * @return: O valor double lido do usuário.
 */

/**
 * Função: readFloat
 * ------------------
 * Lê um valor float do usuário.
 *
 * A função segue os seguintes passos:
 * 1. Lê uma string do usuário.
 * 2. Converte a string para um valor float.
 * 3. Verifica se a conversão foi bem-sucedida. Se não foi, imprime uma mensagem de erro e chama a si mesma recursivamente.
 * 4. Retorna o valor float convertido.
 *
 * @return: O valor float lido do usuário.
 */

/**
 * Função: readChar
 * ----------------
 * Lê um caractere do usuário.
 *
 * A função segue os seguintes passos:
 * 1. Lê uma string do usuário.
 * 2. Verifica se a string contém exatamente um caractere. Se não, imprime uma mensagem de erro e chama a si mesma recursivamente.
 * 3. Retorna o caractere lido.
 *
 * @return: O caractere lido do usuário.
 */

/**
 * Função: readString
 * ------------------
 * Lê uma string do usuário.
 *
 * A função segue os seguintes passos:
 * 1. Lê uma string do usuário.
 * 2. Remove o caractere de nova linha do final da string, se houver.
 * 3. Retorna a string lida.
 *
 * @param string: O ponteiro para a string onde a entrada do usuário será armazenada.
 * @param maxLength: O número máximo de caracteres a serem lidos.
 */

/**
 * Função: readInteger
 * -------------------
 * Lê um valor inteiro do usuário.
 *
 * A função segue os seguintes passos:
 * 1. Lê uma string do usuário.
 * 2. Converte a string para um valor inteiro.
 * 3. Verifica se a conversão foi bem-sucedida. Se não foi, imprime uma mensagem de erro e chama a si mesma recursivamente.
 * 4. Retorna o valor inteiro convertido.
 *
 * @return: O valor inteiro lido do usuário.
 */

/**
 * Função: removeNewLine
 * ---------------------
 * Remove o caractere de nova linha do final de uma string.
 *
 * A função segue os seguintes passos:
 * 1. Verifica se a string é nula. Se for, retorna sem fazer nada.
 * 2. Obtém o comprimento da string.
 * 3. Verifica se o último caractere da string é um caractere de nova linha. Se for, substitui-o por um caractere nulo.
 *
 * @param string: A string da qual o caractere de nova linha será removido.
 */

/**
 * Função: minimumOfTwo
 * --------------------
 * Retorna o menor de dois números.
 *
 * @param x: O primeiro número.
 * @param y: O segundo número.
 * @return: O menor dos dois números.
 */

/**
 * Função: calculateStringSimilarity
 * ---------------------------------
 * Calcula a distância de Levenshtein entre duas strings.
 *
 * A função segue os seguintes passos:
 * 1. Obtém o comprimento das duas strings.
 * 2. Se uma das strings for vazia, retorna o comprimento da outra string.
 * 3. Aloca memória para uma matriz de distâncias.
 * 4. Inicializa a primeira linha e a primeira coluna da matriz.
 * 5. Preenche o restante da matriz com as distâncias de Levenshtein calculadas.
 * 6. Retorna a distância de Levenshtein entre as duas strings, que é o valor na célula inferior direita da matriz.
 *
 * @param string1: A primeira string.
 * @param string2: A segunda string.
 * @return: A distância de Levenshtein entre as duas strings.
 */

/**
 * Função: suggestName
 * -------------------
 * Sugere um nome com base em uma lista de nomes existentes.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa a melhor distância como -1 e a melhor sugestão como NULL.
 * 2. Percorre cada nome na lista de nomes existentes. Para cada nome:
 *    - Calcula a distância de Levenshtein entre o nome incorreto e o nome existente.
 *    - Se a distância for menor que a melhor distância, atualiza a melhor distância e a melhor sugestão.
 *    - Se a distância for menor que um limite, interrompe o loop.
 * 3. Se a melhor sugestão não for NULL, retorna uma cópia da melhor sugestão.
 * 4. Se a melhor sugestão for NULL, retorna NULL.
 *
 * @param incorrectName: O nome incorreto.
 * @param existingNames: A lista de nomes existentes.
 * @param numNames: O número de nomes na lista.
 * @return: Uma sugestão de nome.
 */


/** Patch Notes (29/11/2023 -- schwaad):
 * - implementei as funções do utils.c, com exceção da suggestName. coloquei informações mais específicas no comentário dentro da função.
 */

/** Hotfix (30/11/2023 ~ Dio):
 * - O uso de atof, atoi e atol é desencorajado, pois não há verificação de erros
 * Essas funções foram substituídas por strtod, strtol e strtoll, que são mais seguras.
 * - Troquei nome das funções e variáveis para inglês.
 * - Além de mudar o nome da levenshtein, re-aproveitei uma versão antiga que eu tinha desse algoritmo.
 * - Adicionei uma função para retornar o minimo entre dois inteiros.
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * - Adicionada a readFloat
 * - Adicionada a readChar
 * - Troca de chamda da readString
 */