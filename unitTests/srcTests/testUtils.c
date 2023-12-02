// Funções para testar as utils
// Created by dio on 01/12/23.
//

#include <CUnit/CUnit.h>
#include "testUtils.h"
#include "utils.h"
#include <stdlib.h>

void testReadDouble() {
    FILE *stream = fmemopen("3.14\n", 5, "r");
    stdin = stream;
    CU_ASSERT_DOUBLE_EQUAL(readDouble(), 3.14, 0.001);
    fclose(stream);
}

void testReadInteger() {
    FILE *stream = fmemopen("42\n", 3, "r");
    stdin = stream;
    CU_ASSERT_EQUAL(readInteger(), 42);
    fclose(stream);
}

void testRemoveNewLine() {
    char string[] = "Hello, World!\n";
    removeNewLine(string);
    CU_ASSERT_STRING_EQUAL(string, "Hello, World!");
}

void testCalculateStringSimilarity() {
    CU_ASSERT_EQUAL(calculateStringSimilarity("kitten", "sitting"), 3);
}

void testSuggestName() {
    const char *existingNames[] = {"apple", "banana", "cherry"};
    char *suggestion = suggestName("aple", existingNames, 3);
    CU_ASSERT_STRING_EQUAL(suggestion, "apple");
    free(suggestion);
}

/**
 * Função: testReadDouble
 * ----------------------
 * Testa a função readDouble do arquivo utils.c.
 *
 * A função segue os seguintes passos:
 * 1. Cria um fluxo de memória com a string "3.14\n".
 * 2. Redireciona stdin para o fluxo de memória.
 * 3. Chama a função readDouble e verifica se o valor retornado é igual a 3.14.
 * 4. Fecha o fluxo de memória.
 */

/**
 * Função: testReadInteger
 * -----------------------
 * Testa a função readInteger do arquivo utils.c.
 *
 * A função segue os seguintes passos:
 * 1. Cria um fluxo de memória com a string "42\n".
 * 2. Redireciona stdin para o fluxo de memória.
 * 3. Chama a função readInteger e verifica se o valor retornado é igual a 42.
 * 4. Fecha o fluxo de memória.
 */

/**
 * Função: testRemoveNewLine
 * -------------------------
 * Testa a função removeNewLine do arquivo utils.c.
 *
 * A função segue os seguintes passos:
 * 1. Cria uma string com o valor "Hello, World!\n".
 * 2. Chama a função removeNewLine na string.
 * 3. Verifica se a string agora é igual a "Hello, World!".
 */

/**
 * Função: testCalculateStringSimilarity
 * -------------------------------------
 * Testa a função calculateStringSimilarity do arquivo utils.c.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função calculateStringSimilarity com as strings "kitten" e "sitting".
 * 2. Verifica se o valor retornado é igual a 3.
 */

/**
 * Função: testSuggestName
 * -----------------------
 * Testa a função suggestName do arquivo utils.c.
 *
 * A função segue os seguintes passos:
 * 1. Cria um array de strings com os valores "apple", "banana" e "cherry".
 * 2. Chama a função suggestName com a string "aple" e o array de strings.
 * 3. Verifica se a string retornada é igual a "apple".
 * 4. Libera a memória alocada para a string retornada.
 */

/** Patch Notes (01/12/2023 ~ Dio):
 * - Criado o arquivo junto com suas funções.
 */
