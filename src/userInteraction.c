//
// Created by dio on 02/12/23.
//

#include "database.h"
#include "utilsTable.h"
#include "row.h"
#include "table.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern Table tables[MAX_TABLES];
extern int numTables;

Table getNewTableData() {
    Table newTable;
    newTable.numColumns = 0;
    newTable.numRows = 0;

    while (1) {
        printf("Digite o nome da tabela (ou 'q' para sair): ");
        char* tableName = readNewTableName();
        if (tableName == NULL) {
            return newTable;
        }

        if (!isValidName(tableName)) {
            printf("Erro: O nome da tabela deve conter apenas caracteres numéricos. Digite novamente: ");
            free(tableName);
            continue;
        }

        if (findTableIndex(tableName) != -1) {
            printf("Erro: A tabela '%s' já existe. Digite novamente: ", tableName);
            free(tableName);
            continue;
        }

        strcpy(newTable.name, tableName);
        free(tableName);
        break;
    }

    while (1) {
        printf("Digite o nome da coluna de ID (ou 'q' para sair): ");
        char* idColumnName = readColumnName(&newTable);
        if (idColumnName == NULL) {
            return newTable;
        }

        if (!isValidName(idColumnName)) {
            printf("Erro: O nome da coluna deve conter apenas caracteres alfanuméricos. Digite novamente: ");
            free(idColumnName);
            continue;
        }

        strcpy(newTable.columns[newTable.numColumns].name, idColumnName);
        newTable.columns[newTable.numColumns].type = INT;
        newTable.numColumns++;
        free(idColumnName);
        break;
    }

    printf("Digite o número de colunas adicionais (ou 'q' para sair): ");
    int numAdditionalColumns = readInteger();
    while (numAdditionalColumns < 0 || numAdditionalColumns > MAX_COLUMNS - 1) {
        printf("Número de colunas deve ser entre 0 e %d. Digite novamente: ", MAX_COLUMNS - 1);
        numAdditionalColumns = readInteger();
    }

    for (int i = 0; i < numAdditionalColumns; i++) {
        while (1) {
            printf("Digite o nome da coluna %d (ou 'q' para sair): ", i + 2); // i + 2 porque a coluna de ID já foi adicionada
            char* columnName = readColumnName(&newTable);
            if (columnName == NULL) {
                // O usuário decidiu sair
                return newTable;
            }

            // Validar o nome da coluna
            if (!isValidName(columnName)) {
                printf("Erro: O nome da coluna deve conter apenas caracteres alfanuméricos. Digite novamente: ");
                free(columnName);
                continue;
            }

            DataType columnType = readColumnType();
            strcpy(newTable.columns[newTable.numColumns].name, columnName);
            newTable.columns[newTable.numColumns].type = columnType;
            newTable.numColumns++;
            free(columnName);
            break;
        }
    }

    return newTable;
}

void deleteTableUserInteraction() {
    printf("Deseja listar as tabelas antes? (s/n): ");
    char listTablesResponse[5];
    readString(listTablesResponse, 5);
    if (strcmp(listTablesResponse, "s") == 0 || strcmp(listTablesResponse, "S") == 0) {
        listTables();
    }

    printf("Digite o nome da tabela a ser deletada: ");
    char* tableName = readTableName();
    if (tableName == NULL) {
        // O usuário decidiu sair
        return;
    }

    deleteTableLogic(tableName);
    free(tableName);
}

Row getNewRowData(char* tableName) {
    Row newRow;
    newRow.id = 0;

    // Encontre o índice da tabela
    int tableIndex = findTableIndex(tableName);
    if (tableIndex == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        return newRow;
    }

    Table* table = &tables[tableIndex];

    // Solicitar ao usuário o ID da linha
    while (1) {
        printf("Digite o ID da linha (ou 'q' para sair): ");
        unsigned int rowId = readInteger();
        if (rowId == 0) {
            // O usuário decidiu sair
            return newRow;
        }

        if (rowExists(tableName, rowId)) {
            printf("Erro: O ID da linha já existe. Digite novamente: ");
            continue;
        }

        newRow.id = rowId;
        newRow.cells[0].type = INT;
        newRow.cells[0].value.intValue = rowId;
        break;
    }

    for (int i = 1; i < table->numColumns; i++) {
        while (1) {
            printf("Digite o valor da coluna %d (tipo %s) (ou 'E' para deixar vazia): ", i + 1, printColumnType(table->columns[i].type));
            Cell cell = readCell(table->columns[i].type);
            if (cell.type == EMPTY && cell.value.intValue == -1) {
                // Ocorreu um erro de conversão
                printf("Erro: A entrada precisa ser do tipo %s. Digite novamente: ", printColumnType(table->columns[i].type));
                continue;
            } else if (cell.type == EMPTY && cell.value.intValue != -1) {
                return newRow;
            } else {
                // O usuário inseriu um valor válido ou decidiu deixar a célula vazia
                newRow.cells[i] = cell;
                break;
            }
        }
    }

    return newRow;
}

void createRowUserInteraction() {
    printf("Digite o nome da tabela: ");
    char* tableName = readTableName();
    if (tableName == NULL) {
        return;
    }

    Row newRow = getNewRowData(tableName);
    if (newRow.id == 0) {
        return;
    }

    createRowLogic(newRow, tableName);
    free(tableName);
}

void deleteRowUserInteraction() {
    printf("Digite o nome da tabela: ");
    char* tableName = readTableName();
    if (tableName == NULL) {
        return;
    }

    printf("Deseja listar os dados da tabela antes? (s/n):");
    char listData[5];
    readString(listData, 5);

    if (strcmp(listData, "s") == 0 || strcmp(listData, "S") == 0) {
        listTableData(tableName);
    }

    while (1) {
        printf("Digite o ID da linha a ser deletada (ou 'q' para sair): ");
        char rowIdString[MAX_CELL_LENGTH];
        readString(rowIdString, MAX_CELL_LENGTH);
        if (strcmp(rowIdString, "q") == 0 || strcmp(rowIdString, "Q") == 0) {
            free(tableName);
            return;
        }

        char *endptr;
        unsigned int rowId = strtol(rowIdString, &endptr, 10);
        if (*endptr != '\0') {
            printf("Erro: O ID da linha deve ser um número inteiro. Digite novamente.\n");
            continue;
        }

        deleteRow(tableName, rowId);
        break;
    }

    free(tableName);
}

void listTableDataUserInteraction() {
    printf("Digite o nome da tabela: ");
    char* tableName = readTableName();
    if (tableName == NULL) {
        return;
    }
    if (findTableIndex(tableName) == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        free(tableName);
        return;
    }

    listTableData(tableName);
    free(tableName);
}

/**
 * Função: isValidName
 * -------------------
 * Verifica se o nome fornecido é válido.
 *
 * A função segue os seguintes passos:
 * 1. Percorre cada caractere do nome.
 * 2. Verifica se o caractere é alfanumérico. Se não for, retorna 0.
 * 3. Se todos os caracteres forem alfanuméricos, retorna 1.
 *
 * @param name: O nome a ser verificado.
 * @return: 1 se o nome for válido, 0 se não for.
 */

/**
 * Função: getNewTableData
 * -----------------------
 * Solicita ao usuário os dados para a criação de uma nova tabela.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova tabela.
 * 2. Solicita ao usuário o nome da tabela.
 * 3. Verifica se o nome da tabela é válido e se a tabela já existe. Se não for válido ou já existir, solicita ao usuário que digite novamente.
 * 4. Solicita ao usuário o nome e o tipo da coluna de ID.
 * 5. Verifica se o nome da coluna de ID é válido. Se não for, solicita ao usuário que digite novamente.
 * 6. Solicita ao usuário o número de colunas adicionais.
 * 7. Para cada coluna adicional, solicita ao usuário o nome e o tipo da coluna.
 * 8. Verifica se o nome da coluna é válido e se a coluna já existe na tabela. Se não for válido ou já existir, solicita ao usuário que digite novamente.
 * 9. Retorna a nova tabela.
 *
 * @return: A nova tabela.
 */

/**
 * Função: deleteTableUserInteraction
 * ----------------------------------
 * Lida com a interação do usuário para deletar uma tabela.
 *
 * A função segue os seguintes passos:
 * 1. Solicita ao usuário o nome da tabela a ser deletada.
 * 2. Verifica se o nome da tabela é válido e se a tabela existe. Se não for válido ou não existir, solicita ao usuário que digite novamente.
 * 3. Chama a função deleteTableLogic() para deletar a tabela.
 */

/**
 * Função: getNewRowData
 * ---------------------
 * Solicita ao usuário os dados para a criação de uma nova linha em uma tabela específica.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova linha.
 * 2. Solicita ao usuário o ID da linha.
 * 3. Verifica se o ID da linha já existe. Se sim, solicita ao usuário que digite novamente.
 * 4. Solicita ao usuário os valores para cada coluna na tabela.
 * 5. Se o usuário decidir deixar uma célula como vazia, define o tipo da célula como EMPTY.
 * 6. Retorna a nova linha.
 *
 * @param tableName: O nome da tabela onde a linha será adicionada.
 * @return: A nova linha.
 */

/**
 * Função: createRowUserInteraction
 * --------------------------------
 * Lida com a interação do usuário para criar uma nova linha.
 *
 * A função segue os seguintes passos:
 * 1. Solicita ao usuário o nome da tabela onde a linha será adicionada.
 * 2. Chama a função getNewRowData() para obter os dados da nova linha do usuário.
 * 3. Chama a função createRowBusinessLogic() para adicionar a nova linha à tabela.
 */

/**
 * Função: deleteRowUserInteraction
 * --------------------------------
 * Lida com a interação do usuário para deletar uma linha.
 *
 * A função segue os seguintes passos:
 * 1. Solicita ao usuário o nome da tabela de onde a linha será deletada.
 * 2. Solicita ao usuário o ID da linha a ser deletada.
 * 3. Chama a função deleteRow() para deletar a linha da tabela.
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * Criação do arquivo e todas as susas funções
 */