// Sources of tests.
// Created by dio on 27/11/23.
//

#include "testFileOperations.h"
#include "database.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

extern Table tables[MAX_TABLES];
extern int numTables;

void testFileOperations() {
    testReadFile();
    testProcessFileContentWithKnownContent();
    testSaveDatabaseToFile();
}

// Testes para operações de banco de dados
/* void testDatabaseOperations() {
    testInitDatabase();
    testInitCellAsEmpty();
}*/

// Testes para operações auxiliares de arquivo
/* void testUtilsFileOperations() {
    testProcessTable();
    testConvertStringToCell();
    testProcessRows();
} */

int main() {
    CU_initialize_registry();

    CU_pSuite fileOpsSuite = CU_add_suite("File Operations Tests", NULL, NULL);
    CU_add_test(fileOpsSuite, "testFileOperations", testFileOperations);

    // CU_pSuite dbOpsSuite = CU_add_suite("Database Operations Tests", NULL, NULL);
    // CU_add_test(dbOpsSuite, "testDatabaseOperations", testDatabaseOperations);

    // CU_pSuite utilsFileOpsSuite = CU_add_suite("Utils File Operations Tests", NULL, NULL);
    // CU_add_test(utilsFileOpsSuite, "testUtilsFileOperations", testUtilsFileOperations);

    // Execute todos os testes
    CU_basic_run_tests();

    // Limpe o registro do CUnit
    CU_cleanup_registry();

    return 0;
}

/**
 * Função: testFileOperations
 * ---------------------------
 * Testa as operações de arquivo.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função testReadFile para testar a leitura de um arquivo.
 * 2. Chama a função testProcessFileContentWithKnownContent para testar o processamento do conteúdo de um arquivo com conteúdo conhecido.
 * 3. Chama a função testSaveDatabaseToFile para testar a gravação do banco de dados em um arquivo.
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Adicionado testes para o processo de carregar um banco de dados de um arquivo
 * - Pretende-se criar mais arquivos de testes ou adicionar mais testes neste arquivo
 */

/** Patch Notes (29/11/2023 ~ Dio):
 * - Modularização das funções de testes em suites e arquivos diferentes
 * - Adicionado testes para o processo de salvar um banco de dados em um arquivo
 */