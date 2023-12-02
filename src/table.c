// Descrição: Arquivo responsável por implementar as funções de manipulação de tabelas
// Created by dio on 25/11/23.
//

#include "database.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Table tables[10];
extern int numTables;

void createTable() {
    if (numTables >= MAX_TABLES) {
        printf("Número máximo de tabelas atingido.\n");
        return;
    }

    printf("Digite o nome da tabela: ");
    char tableName[MAX_NAME_LENGTH];
    fgets(tableName, MAX_NAME_LENGTH, stdin);
    removeNewLine(tableName);

    if (strcmp(tableName, "q") == 0 || strcmp(tableName, "Q") == 0) {
        return;
    }

    while (strlen(tableName) == 0 || strlen(tableName) > MAX_NAME_LENGTH) {
        printf("Nome para tabela deve ter no máximo %d caracteres. Digite novamente: ", MAX_NAME_LENGTH - 1);
        fgets(tableName, MAX_NAME_LENGTH, stdin);
        removeNewLine(tableName);
    }

    Table newTable;
    strcpy(newTable.name, tableName);
    newTable.numColumns = 0;
    newTable.numRows = 0;

    printf("Digite o nome da coluna ID: ");
    char idColumnName[MAX_NAME_LENGTH];
    fgets(idColumnName, MAX_NAME_LENGTH, stdin);
    removeNewLine(idColumnName);

    if (strcmp(idColumnName, "q") == 0 || strcmp(idColumnName, "Q") == 0) {
        return;
    }

    while (strlen(idColumnName) == 0 || strlen(idColumnName) > MAX_NAME_LENGTH) {
        printf("Nome para coluna ID deve ter no máximo %d caracteres. Digite novamente: ", MAX_NAME_LENGTH - 1);
        fgets(idColumnName, MAX_NAME_LENGTH, stdin);
        removeNewLine(idColumnName);
    }

    strcpy(newTable.columns[0].name, idColumnName);
    newTable.columns[0].type = INT;
    newTable.numColumns++;

    printf("Digite o número de colunas adicionais: ");
    int numColumns = readInteger();

    while (numColumns < 0 || numColumns > MAX_COLUMNS) {
        printf("Número de colunas deve ser menor que %d. Digite novamente: ", MAX_COLUMNS);
        numColumns = readInteger();
    }

    for (int i = 0; i < numColumns; i++) {
        printf("Digite o nome da coluna %d: ", i + 2);
        char columnName[MAX_NAME_LENGTH];
        fgets(columnName, MAX_NAME_LENGTH, stdin);
        removeNewLine(columnName);

        while (strlen(columnName) == 0 || strlen(columnName) > MAX_NAME_LENGTH) {
            printf("Nome para coluna %d deve ter no máximo %d caracteres. Digite novamente: ", i + 2, MAX_NAME_LENGTH - 1);
            fgets(columnName, MAX_NAME_LENGTH, stdin);
            removeNewLine(columnName);
        }

        printf("Digite o tipo da coluna %d (1 para INT, 2 para FLOAT, 3 para DOUBLE, 4 para CHAR, 5 para STRING): ", i + 2);
        int columnType = readInteger();

        while (columnType < 1 || columnType > 5) {
            printf("Tipo de coluna deve ser menor que 6. Digite novamente: ");
            columnType = readInteger();
        }

        strcpy(newTable.columns[i+1].name, columnName);
        newTable.columns[i+1].type = columnType;
        newTable.numColumns++;
    }

    newTable.idColumn = 0;
    tables[numTables] = newTable;
    numTables++;
}

void listTables() {
    for (int i = 0; i < numTables; i++) {
        printf("Tabela %d: %s\n", i + 1, tables[i].name);
    }
}

void deleteTable() {
    printf("Digite o nome da tabela a ser deletada: ");
    char tableName[MAX_NAME_LENGTH];
    if (!fgets(tableName, MAX_NAME_LENGTH, stdin)) {
        fprintf(stderr, "Erro ao ler o nome da tabela.\n");
        return;
    }
    removeNewLine(tableName);

    int tableIndex = -1;
    for (int i = 0; i < numTables; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            tableIndex = i;
            break;
        }
    }

    if (tableIndex == -1) {
        printf("Tabela '%s' não encontrada.\n", tableName);
        const char *tableNames[MAX_TABLES];
        for (int i = 0; i < numTables; i++) {
            tableNames[i] = tables[i].name;
        }
        char *suggestedName = suggestName(tableName, tableNames, numTables);
        if (suggestedName != NULL) {
            printf("Você quis dizer %s? (s/n)\n", suggestedName);
            char response[3];
            if (!fgets(response, 3, stdin)) {
                fprintf(stderr, "Erro ao ler a resposta.\n");
                free(suggestedName);
                return;
            }
            removeNewLine(response);
            while (strcmp(response, "s") != 0 && strcmp(response, "S") != 0 && strcmp(response, "n") != 0 && strcmp(response, "N") != 0 && strcmp(response, "q") != 0 && strcmp(response, "Q") != 0) {
                printf("Entrada inválida. Digite 's' para sim, 'n' para não ou 'q' para sair: ");
                if (!fgets(response, 3, stdin)) {
                    fprintf(stderr, "Erro ao ler a resposta.\n");
                    free(suggestedName);
                    return;
                }
                removeNewLine(response);
            }
            if (strcmp(response, "q") == 0 || strcmp(response, "Q") == 0) {
                free(suggestedName);
                return;
            }
            if (strcmp(response, "s") == 0 || strcmp(response, "S") == 0) {
                for (int i = 0; i < numTables; i++) {
                    if (strcmp(tables[i].name, suggestedName) == 0) {
                        tableIndex = i;
                        break;
                    }
                }
            }
            free(suggestedName);
        }
        if (tableIndex == -1) {
            return;
        }
    }

    for (int i = tableIndex; i < numTables - 1; i++) {
        tables[i] = tables[i + 1];
    }

    numTables--;

    // Verificar se a tabela foi removida com sucesso
    for (int i = 0; i < numTables; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            fprintf(stderr, "Erro: Falha ao remover a tabela '%s'.\n", tableName);
            return;
        }
    }

    printf("A tabela '%s' foi removida com sucesso.\n", tableName);
}

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 * - Apaguei a versão anterior para poder recomeçar de maneira melhor
 */
