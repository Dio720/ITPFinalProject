// Descrição: Arquivo responsável por implementar as funções de manipulação de tabelas
// Created by dio on 25/11/23.
//

#include "database.h"
#include "utilsTable.h"
#include "userInteraction.h"
#include <stdio.h>



extern Table tables[MAX_TABLES];
extern int numTables;

void createTableLogic(Table newTable) {
    int previousNumTables = numTables;
    if (numTables == MAX_TABLES) {
        printf("Erro: O número máximo de tabelas foi atingido.\n");
        return;
    }
    tables[numTables] = newTable;
    numTables++;
    if (previousNumTables < numTables) {
        printf("A tabela '%s' foi criada com sucesso.\n", newTable.name);
    } else {
        printf("A tabela '%s' não foi criada.\n", newTable.name);
    }
}

void createTable() {
    Table newTable = getNewTableData();
    if (newTable.numColumns == 0) {
        return; // O usuário decidiu sair
    }
    createTableLogic(newTable);
}

void deleteTableLogic(char* tableName) {
    int tableIndex = findTableIndex(tableName);
    if (tableIndex == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        return;
    }

    for (int i = tableIndex; i < numTables - 1; i++) {
        tables[i] = tables[i + 1];
    }

    numTables--;

    printf("A tabela '%s' foi deletada com sucesso.\n", tableName);
}

void listTables() {
    if (numTables == 0) {
        printf("Não há tabelas no banco de dados.\n");
        return;
    }
    for (int i = 0; i < numTables; i++) {
        printf("Tabela %d: %s\n", i + 1, tables[i].name);
    }
}

void listTableData(char* tableName) {
    int tableIndex = findTableIndex(tableName);

    Table* table = &tables[tableIndex];

    // Calculate maximum width for each column
    int columnWidths[MAX_COLUMNS];
    for (int i = 0; i < table->numColumns; i++) {
        columnWidths[i] = strlen(table->columns[i].name);
        for (int j = 0; j < table->numRows; j++) {
            int cellWidth;
            Cell cell = table->rows[j].cells[i];
            switch (cell.type) {
                case INT:
                    cellWidth = snprintf(NULL, 0, "%d", cell.value.intValue);
                    break;
                case FLOAT:
                    cellWidth = snprintf(NULL, 0, "%.2f", cell.value.floatValue);
                    break;
                case DOUBLE:
                    cellWidth = snprintf(NULL, 0, "%.2lf", cell.value.doubleValue);
                    break;
                case CHAR:
                    cellWidth = snprintf(NULL, 0, "%c", cell.value.charValue);
                    break;
                case STRING:
                    cellWidth = strlen(cell.value.stringValue);
                    break;
                case EMPTY:
                    cellWidth = 1;
                    break;
            }
            if (cellWidth > columnWidths[i]) {
                columnWidths[i] = cellWidth;
            }
        }
        columnWidths[i] += 2; // Add extra spaces for readability
    }

    // Calculate total width
    int totalWidth = 0;
    for (int i = 0; i < table->numColumns; i++) {
        totalWidth += columnWidths[i] + 3; // for data, "| ", and " "
    }
    totalWidth += 1; // for the last "|"

    // Print line above column headers
    for (int i = 0; i < totalWidth; i++) {
        printf("-");
    }
    printf("\n");

    // Print column headers
    for (int i = 0; i < table->numColumns; i++) {
        printf("| %-*s ", columnWidths[i], table->columns[i].name);
    }
    printf("|\n");

    // Print line below column headers
    for (int i = 0; i < totalWidth; i++) {
        printf("-");
    }
    printf("\n");

    // Print each row
    for (int i = 0; i < table->numRows; i++) {
        for (int j = 0; j < table->numColumns; j++) {
            Cell cell = table->rows[i].cells[j];
            printf("| ");
            switch (cell.type) {
                case INT:
                    printf("%-*d ", columnWidths[j], cell.value.intValue);
                    break;
                case FLOAT:
                    printf("%-*.*f ", columnWidths[j], 2, cell.value.floatValue);
                    break;
                case DOUBLE:
                    printf("%-*.*lf ", columnWidths[j], 2, cell.value.doubleValue);
                    break;
                case CHAR:
                    printf("%-*c ", columnWidths[j], cell.value.charValue);
                    break;
                case STRING:
                    printf("%-*s ", columnWidths[j], cell.value.stringValue);
                    break;
                case EMPTY:
                    printf("%-*s ", columnWidths[j], " ");
                    break;
            }
        }
        printf("|\n");
    }

    // Print line at the end of the table
    for (int i = 0; i < totalWidth; i++) {
        printf("-");
    }
    printf("\n");
}

/**
 * Função: createTableLogic
 * ------------------------
 * Cria uma nova tabela no banco de dados.
 *
 * A função segue os seguintes passos:
 * 1. Verifica se o número máximo de tabelas foi atingido. Se sim, imprime uma mensagem de erro e retorna.
 * 2. Adiciona a nova tabela ao array de tabelas.
 * 3. Imprime uma mensagem informando que a tabela foi criada com sucesso.
 *
 * @param newTable: A nova tabela a ser adicionada.
 */

/**
 * Função: createTable
 * -------------------
 * Solicita ao usuário os dados para a criação de uma nova tabela e a cria.
 *
 * A função segue os seguintes passos:
 * 1. Chama a função getNewTableData() para obter os dados da nova tabela do usuário.
 * 2. Se o usuário decidir sair, retorna.
 * 3. Chama a função createTableLogic() para criar a tabela.
 */

/**
 * Função: deleteTableLogic
 * ------------------------
 * Deleta uma tabela do banco de dados.
 *
 * A função segue os seguintes passos:
 * 1. Encontra o índice da tabela.
 * 2. Se a tabela não for encontrada, imprime uma mensagem de erro e retorna.
 * 3. Remove a tabela do array de tabelas.
 * 4. Decrementa o número de tabelas.
 * 5. Imprime uma mensagem informando que a tabela foi deletada com sucesso.
 *
 * @param tableName: O nome da tabela a ser deletada.
 */

/**
 * Função: listTables
 * ------------------
 * Lista todas as tabelas no banco de dados.
 *
 * A função segue os seguintes passos:
 * 1. Verifica se há tabelas no banco de dados. Se não houver, imprime uma mensagem e retorna.
 * 2. Percorre todas as tabelas no banco de dados.
 * 3. Imprime o nome de cada tabela.
 */

/**
 * Função: listTableData
 * ---------------------
 * Lista todos os dados em uma tabela específica.
 *
 * A função segue os seguintes passos:
 * 1. Encontra o índice da tabela.
 * 2. Imprime os nomes das colunas da tabela.
 * 3. Percorre todas as linhas da tabela.
 * 4. Para cada linha, percorre todas as células.
 * 5. Imprime o valor de cada célula.
 *
 * @param tableName: O nome da tabela cujos dados serão listados.
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 * - Apaguei a versão anterior para poder recomeçar de maneira melhor
 */

/** Patch Notes (01/12/2023 ~ Dio):
 * - Criada as funções de manipular tabelas
 *   · createTable()
 *   · listTables()
 *   · deleteTable()
 */

/** Patch Notes (03/12/2023 ~ Dio):
 *  · Refeita as funções de manipular tabelas
 *  · Adicionada a função createTableLogic()
 *  · Adicionada a função deleteTableLogic()
 *  · Adicionada a função listTableData()
 */