// Sources of tests.
// Created by dio on 27/11/23.
//

#include "file_operations.h"
#include "utils_file_operations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

extern Table tables[MAX_TABLES];
extern int num_tables;

void testLoadDatabaseWithSomeTypes() {
    char input[] =
            "Tabela 1: \"nome1\", Quantidade de colunas: 2, Quantidade de Linhas: 2\n"
            "Coluna 1: \"nome1\", Tipo: 1\n"
            "Coluna 2: \"nome2\", Tipo: 2\n"
            "Linha 1: \"1\", \"2.2\"\n"
            "Linha 2: \"3\", \"4.4\"\n";

    initDatabase();
    processFileContent(input);

    CU_ASSERT_EQUAL(num_tables, 1);
    CU_ASSERT_STRING_EQUAL(tables[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].numColumns, 2);
    CU_ASSERT_EQUAL(tables[0].numRows, 2);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].columns[0].type, INT);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[1].name, "nome2");
    CU_ASSERT_EQUAL(tables[0].columns[1].type, FLOAT);
    CU_ASSERT_EQUAL(tables[0].rows[0].cells[0].value.intValue, 1);
    CU_ASSERT_DOUBLE_EQUAL(tables[0].rows[0].cells[1].value.floatValue, 2.2,
                           0.001);
    CU_ASSERT_EQUAL(tables[0].rows[1].cells[0].value.intValue, 3);
    CU_ASSERT_DOUBLE_EQUAL(tables[0].rows[1].cells[1].value.floatValue, 4.4,
                           0.001);
}

void testLoadDatabaseWithEmptyCells() {
    char input[] =
            "Tabela 1: \"nome1\", Quantidade de colunas: 2, Quantidade de Linhas: 2\n"
            "Coluna 1: \"nome1\", Tipo: 0\n"
            "Coluna 2: \"nome2\", Tipo: 0\n"
            "Linha 1: \"\", \"\"\n"
            "Linha 2: \"\", \"\"\n";

    initDatabase();
    processFileContent(input);

    CU_ASSERT_EQUAL(num_tables, 1);
    CU_ASSERT_STRING_EQUAL(tables[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].numColumns, 2);
    CU_ASSERT_EQUAL(tables[0].numRows, 2);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].columns[0].type, EMPTY);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[1].name, "nome2");
    CU_ASSERT_EQUAL(tables[0].columns[1].type, EMPTY);
    CU_ASSERT_EQUAL(tables[0].rows[0].cells[0].type, EMPTY);
    CU_ASSERT_EQUAL(tables[0].rows[0].cells[1].type, EMPTY);
    CU_ASSERT_EQUAL(tables[0].rows[1].cells[0].type, EMPTY);
    CU_ASSERT_EQUAL(tables[0].rows[1].cells[1].type, EMPTY);
}

void testLoadDatabaseWithMultipleTables() {
    char input[] =
            "Tabela 1: \"nome1\", Quantidade de colunas: 2, Quantidade de Linhas: 2\n"
            "Coluna 1: \"nome1\", Tipo: 1\n"
            "Coluna 2: \"nome2\", Tipo: 2\n"
            "Linha 1: \"1\", \"2.2\"\n"
            "Linha 2: \"3\", \"4.4\"\n"
            "Tabela 2: \"nome3\", Quantidade de colunas: 3, Quantidade de Linhas: 3\n"
            "Coluna 1: \"nome4\", Tipo: 1\n"
            "Coluna 2: \"nome5\", Tipo: 3\n"
            "Coluna 3: \"nome6\", Tipo: 5\n"
            "Linha 1: \"5\", \"6.6\", \"string1\"\n"
            "Linha 2: \"7\", \"8.8\", \"string2\"\n"
            "Linha 3: \"9\", \"10.10\", \"string3\"\n";

    initDatabase();
    processFileContent(input);

    CU_ASSERT_EQUAL(num_tables, 2);
    // Verificações para a primeira tabela
    CU_ASSERT_STRING_EQUAL(tables[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].numColumns, 2);
    CU_ASSERT_EQUAL(tables[0].numRows, 2);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[0].name, "nome1");
    CU_ASSERT_EQUAL(tables[0].columns[0].type, INT);
    CU_ASSERT_STRING_EQUAL(tables[0].columns[1].name, "nome2");
    CU_ASSERT_EQUAL(tables[0].columns[1].type, FLOAT);
    CU_ASSERT_EQUAL(tables[0].rows[0].cells[0].value.intValue, 1);
    CU_ASSERT_DOUBLE_EQUAL(tables[0].rows[0].cells[1].value.floatValue, 2.2,
                           0.001);
    CU_ASSERT_EQUAL(tables[0].rows[1].cells[0].value.intValue, 3);
    CU_ASSERT_DOUBLE_EQUAL(tables[0].rows[1].cells[1].value.floatValue, 4.4,
                           0.001);
    // Verificações para a segunda tabela
    CU_ASSERT_STRING_EQUAL(tables[1].name, "nome3");
    CU_ASSERT_EQUAL(tables[1].numColumns, 3);
    CU_ASSERT_EQUAL(tables[1].numRows, 3);
    CU_ASSERT_STRING_EQUAL(tables[1].columns[0].name, "nome4");
    CU_ASSERT_EQUAL(tables[1].columns[0].type, INT);
    CU_ASSERT_STRING_EQUAL(tables[1].columns[1].name, "nome5");
    CU_ASSERT_EQUAL(tables[1].columns[1].type, DOUBLE);
    CU_ASSERT_STRING_EQUAL(tables[1].columns[2].name, "nome6");
    CU_ASSERT_EQUAL(tables[1].columns[2].type, STRING);
    CU_ASSERT_EQUAL(tables[1].rows[0].cells[0].value.intValue, 5);
    CU_ASSERT_DOUBLE_EQUAL(tables[1].rows[0].cells[1].value.doubleValue, 6.6,
                           0.001);
    CU_ASSERT_STRING_EQUAL(tables[1].rows[0].cells[2].value.stringValue,
                           "string1");
    CU_ASSERT_EQUAL(tables[1].rows[1].cells[0].value.intValue, 7);
    CU_ASSERT_DOUBLE_EQUAL(tables[1].rows[1].cells[1].value.doubleValue, 8.8,
                           0.001);
    CU_ASSERT_STRING_EQUAL(tables[1].rows[1].cells[2].value.stringValue,
                           "string2");
    CU_ASSERT_EQUAL(tables[1].rows[2].cells[0].value.intValue, 9);
    CU_ASSERT_DOUBLE_EQUAL(tables[1].rows[2].cells[1].value.doubleValue, 10.10,
                           0.001);
    CU_ASSERT_STRING_EQUAL(tables[1].rows[2].cells[2].value.stringValue,
                           "string3");
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("loadDatabase_test_suite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testLoadDatabaseWithSomeTypes",
                             testLoadDatabaseWithSomeTypes)) ||
        (NULL == CU_add_test(pSuite, "testLoadDatabaseWithEmptyCells",
                             testLoadDatabaseWithEmptyCells)) ||
        (NULL == CU_add_test(pSuite, "testLoadDatabaseWithMultipleTables",
                             testLoadDatabaseWithMultipleTables))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

/**
 * Função: testLoadDatabaseWithSomeTypes
 * -------------------------------------
 * Testa o processo de carregar um banco de dados com todos os tipos de dados.
 *
 * A função segue os seguintes passos:
 * 1. Define uma string que representa o conteúdo de um arquivo. Esta string
 * contém uma única tabela com duas colunas de diferentes tipos (INT e FLOAT) e
 * duas linhas.
 * 2. Chama a função initDatabase para inicializar o banco de dados.
 * 3. Chama a função processFileContent com a string para carregar os dados no
 * banco de dados.
 * 4. Usa as funções de assert do CUnit para verificar se os dados foram
 * carregados corretamente no banco de dados. Ela verifica o número de tabelas
 * no banco de dados, o nome, número de colunas e número de linhas da tabela, o
 * nome e tipo de cada coluna, e o valor e tipo de cada célula.
 *
 * @return: void
 */

/**
 * Função: testLoadDatabaseWithEmptyCells
 * ---------------------------------------
 * Testa o processo de carregar um banco de dados com células vazias.
 *
 * A função segue os seguintes passos:
 * 1. Define uma string que representa o conteúdo de um arquivo. Esta string
 * contém uma única tabela com duas colunas de tipo EMPTY e duas linhas com
 * células vazias.
 * 2. Chama a função initDatabase para inicializar o banco de dados.
 * 3. Chama a função processFileContent com a string para carregar os dados no
 * banco de dados.
 * 4. Usa as funções de assert do CUnit para verificar se os dados foram
 * carregados corretamente no banco de dados. Ela verifica o número de tabelas
 * no banco de dados, o nome, número de colunas e número de linhas da tabela, o
 * nome e tipo de cada coluna, e o tipo de cada célula (que deve ser EMPTY).
 *
 * @return: void
 */

/**
 * Função: testLoadDatabaseWithMultipleTables
 * -------------------------------------------
 * Testa o processo de carregar um banco de dados com múltiplas tabelas.
 *
 * A função segue os seguintes passos:
 * 1. Define uma string que representa o conteúdo de um arquivo. Esta string
 * contém duas tabelas, cada uma com várias colunas de diferentes tipos e várias
 * linhas.
 * 2. Chama a função initDatabase para inicializar o banco de dados.
 * 3. Chama a função processFileContent com a string para carregar os dados no
 * banco de dados.
 * 4. Usa as funções de assert do CUnit para verificar se os dados foram
 * carregados corretamente no banco de dados. Ela verifica o número de tabelas
 * no banco de dados, o nome, número de colunas e número de linhas de cada
 * tabela, o nome e tipo de cada coluna, e o valor e tipo de cada célula.
 *
 * @return: void
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Adicionado testes para o processo de carregar um banco de dados de um arquivo
 * - Pretende-se criar mais arquivos de testes ou adicionar mais testes neste arquivo
 */