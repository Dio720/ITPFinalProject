// Funções para testar as operações de arquivo.
// Created by dio on 29/11/23.
//

#include <CUnit/CUnit.h>
#include "fileOperations.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern Table tables[MAX_TABLES];
extern int numTables;

void testReadFile() {
    const char *filename = "testFiles/testFileWithKnownContent.txt";
    char *content = readFile(filename);
    CU_ASSERT_PTR_NOT_NULL_FATAL(content)
    free(content);
}

void testProcessFileContentWithKnownContent() {
    const char *filename = "testFiles/testFileWithKnownContent.txt";
    char *content = readFile(filename);
    CU_ASSERT_PTR_NOT_NULL_FATAL(content)

    initDatabase();
    processFileContent(content);


    // Verifique se as informações foram carregadas corretamente na estrutura de banco de dados
    CU_ASSERT_EQUAL(numTables, 4)
    CU_ASSERT_STRING_EQUAL(tables[0].name, "Alunos")
    CU_ASSERT_EQUAL(tables[0].numColumns, 4)
    CU_ASSERT_EQUAL(tables[0].numRows, 3)
    CU_ASSERT_STRING_EQUAL(tables[0].columns[0].name, "ID")
    CU_ASSERT_EQUAL(tables[0].columns[0].type, INT)

    // Verificações adicionais para as células da tabela "Alunos"
    int expectedAlunosIDs[3] = {0, 1, 2};
    char *expectedAlunosNames[3] = {"João", "Maria", "Pedro"};
    int expectedAlunosAges[3] = {15, 16, 15};
    float expectedAlunosMedias[3] = {8.5, 9.0, 7.5};
    for (int i = 0; i < tables[0].numRows; i++) {
        CU_ASSERT_EQUAL(tables[0].rows[i].cells[0].value.intValue, expectedAlunosIDs[i])
        CU_ASSERT_STRING_EQUAL(tables[0].rows[i].cells[1].value.stringValue, expectedAlunosNames[i])
        CU_ASSERT_EQUAL(tables[0].rows[i].cells[2].value.intValue, expectedAlunosAges[i])
        CU_ASSERT_DOUBLE_EQUAL(tables[0].rows[i].cells[3].value.floatValue, expectedAlunosMedias[i], 0.01)
    }

    CU_ASSERT_STRING_EQUAL(tables[1].name, "Professores")
    CU_ASSERT_EQUAL(tables[1].numColumns, 4)
    CU_ASSERT_EQUAL(tables[1].numRows, 2)
    CU_ASSERT_STRING_EQUAL(tables[1].columns[0].name, "ID")
    CU_ASSERT_EQUAL(tables[1].columns[0].type, INT)

    // Verificações adicionais para as células da tabela "Professores"
    int expectedProfessoresIDs[2] = {3, 4};
    char *expectedProfessoresNames[2] = {"Carlos", "Ana"};
    int expectedProfessoresAges[2] = {35, 30};
    char *expectedProfessoresDisciplinas[2] = {"Matematica", "Portugues"};
    for (int i = 0; i < tables[1].numRows; i++) {
        CU_ASSERT_EQUAL(tables[1].rows[i].cells[0].value.intValue, expectedProfessoresIDs[i])
        CU_ASSERT_STRING_EQUAL(tables[1].rows[i].cells[1].value.stringValue, expectedProfessoresNames[i])
        CU_ASSERT_EQUAL(tables[1].rows[i].cells[2].value.intValue, expectedProfessoresAges[i])
        CU_ASSERT_STRING_EQUAL(tables[1].rows[i].cells[3].value.stringValue, expectedProfessoresDisciplinas[i])
    }

    // Verificações adicionais para a tabela "Funcionários"
    CU_ASSERT_STRING_EQUAL(tables[2].name, "Funcionários")
    CU_ASSERT_EQUAL(tables[2].numColumns, 4)
    CU_ASSERT_EQUAL(tables[2].numRows, 3)
    CU_ASSERT_STRING_EQUAL(tables[2].columns[0].name, "ID")
    CU_ASSERT_EQUAL(tables[2].columns[0].type, INT)

    int expectedFuncionariosIDs[3] = {5, 6, 7};
    char *expectedFuncionariosNames[3] = {"Lucas", "Julia", "Roberto"};
    int expectedFuncionariosAges[3] = {28, 32, 45};
    char *expectedFuncionariosCargos[3] = {"Marketeiro", "Gerente", "Diretor"};
    for (int i = 0; i < tables[2].numRows; i++) {
        CU_ASSERT_EQUAL(tables[2].rows[i].cells[0].value.intValue, expectedFuncionariosIDs[i])
        CU_ASSERT_STRING_EQUAL(tables[2].rows[i].cells[1].value.stringValue, expectedFuncionariosNames[i])
        CU_ASSERT_EQUAL(tables[2].rows[i].cells[2].value.intValue, expectedFuncionariosAges[i])
        CU_ASSERT_STRING_EQUAL(tables[2].rows[i].cells[3].value.stringValue, expectedFuncionariosCargos[i])
    }

    // Verificações adicionais para a tabela "Departamentos"
    CU_ASSERT_STRING_EQUAL(tables[3].name, "Departamentos")
    CU_ASSERT_EQUAL(tables[3].numColumns, 3)
    CU_ASSERT_EQUAL(tables[3].numRows, 2)
    CU_ASSERT_STRING_EQUAL(tables[3].columns[0].name, "ID")
    CU_ASSERT_EQUAL(tables[3].columns[0].type, INT)

    int expectedDepartamentosIDs[2] = {8, 9};
    char *expectedDepartamentosNames[2] = {"Marketing", "Gerência"};
    char *expectedDepartamentosResponsaveis[2] = {"Lucas", "Julia"};
    for (int i = 0; i < tables[3].numRows; i++) {
        CU_ASSERT_EQUAL(tables[3].rows[i].cells[0].value.intValue, expectedDepartamentosIDs[i])
        CU_ASSERT_STRING_EQUAL(tables[3].rows[i].cells[1].value.stringValue, expectedDepartamentosNames[i])
        CU_ASSERT_STRING_EQUAL(tables[3].rows[i].cells[2].value.stringValue, expectedDepartamentosResponsaveis[i])
    }

    free(content);
}

void testSaveDatabaseToFile() {
    // Inicialize o banco de dados com os dados conhecidos do arquivo testFileWithKnownContent.txt
    const char *inputFilename = "testFiles/testFileWithKnownContent.txt";
    char *inputContent = readFile(inputFilename);
    CU_ASSERT_PTR_NOT_NULL_FATAL(inputContent)

    initDatabase();
    processFileContent(inputContent);

    // Salve o banco de dados em um novo arquivo usando saveDatabaseToFile
    const char *outputFilename = "testFiles/testSaveDatabaseToFileOutput.txt";
    bool saveResult = saveDatabaseToFile(outputFilename);
    CU_ASSERT_TRUE_FATAL(saveResult)

    // Leia o conteúdo do novo arquivo
    char *outputContent = readFile(outputFilename);
    CU_ASSERT_PTR_NOT_NULL_FATAL(outputContent)

    // Compare o conteúdo do novo arquivo com o conteúdo do arquivo original
    char *expectedContent = readFile(inputFilename);
    CU_ASSERT_STRING_EQUAL(expectedContent, outputContent)

    free(inputContent);
    free(outputContent);
}

/**
 * Função: testReadFile
 * --------------------
 * Testa a função readFile.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função readFile com um nome de arquivo de teste conhecido.
 * 2. Usa a função CU_ASSERT_PTR_NOT_NULL_FATAL do CUnit para verificar se a função readFile retornou um ponteiro não nulo.
 * 3. Libera a memória alocada para o conteúdo do arquivo.
 */

/**
 * Função: testProcessFileContentWithKnownContent
 * ----------------------------------------------
 * Testa a função processFileContent com conteúdo de arquivo conhecido.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função readFile com um nome de arquivo de teste conhecido e armazena o conteúdo do arquivo.
 * 2. Usa a função CU_ASSERT_PTR_NOT_NULL_FATAL do CUnit para verificar se a função readFile retornou um ponteiro não nulo.
 * 3. Chama a função initDatabase para inicializar o banco de dados.
 * 4. Chama a função processFileContent com o conteúdo do arquivo para preencher o banco de dados.
 * 5. Verifica se os dados no banco de dados correspondem aos dados esperados.
 * 6. Libera a memória alocada para o conteúdo do arquivo.
 */

/**
 * Função: testSaveDatabaseToFile
 * ------------------------------
 * Testa a função saveDatabaseToFile.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função readFile com um nome de arquivo de teste conhecido e armazena o conteúdo do arquivo.
 * 2. Usa a função CU_ASSERT_PTR_NOT_NULL_FATAL do CUnit para verificar se a função readFile retornou um ponteiro não nulo.
 * 3. Chama a função initDatabase para inicializar o banco de dados.
 * 4. Chama a função processFileContent com o conteúdo do arquivo para preencher o banco de dados.
 * 5. Chama a função saveDatabaseToFile para salvar o banco de dados em um novo arquivo.
 * 6. Usa a função CU_ASSERT_TRUE_FATAL do CUnit para verificar se a função saveDatabaseToFile retornou true.
 * 7. Chama a função readFile para ler o conteúdo do novo arquivo.
 * 8. Usa a função CU_ASSERT_PTR_NOT_NULL_FATAL do CUnit para verificar se a função readFile retornou um ponteiro não nulo.
 * 9. Compara o conteúdo do novo arquivo com o conteúdo do arquivo original.
 * 10. Libera a memória alocada para o conteúdo dos arquivos.
 */

/** Patch Notes (29/11/23 -- Dio):
 * - Adicionado testes para o processo de carregar e salvar um banco de dados de um arquivo
 */