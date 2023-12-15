// Funções relacionadas à manipulação de linhas
// Created by dio on 25/11/23.
//

#include "database.h"
#include "utilsTable.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern Table tables[MAX_TABLES];
extern int numTables;

Cell readCell(DataType columnType) {
    Cell cell;
    cell.type = columnType;

    char input[MAX_CELL_LENGTH];
    readString(input, MAX_CELL_LENGTH);

    if (strcmp(input, "E") == 0 || strcmp(input, "e") == 0) {
        cell.type = EMPTY;
        return cell;
    }

    char *endptr;
    switch (columnType) {
        case INT: {
            cell.value.intValue = strtol(input, &endptr, 10);
            if (*endptr != '\0') {
                cell.type = EMPTY;
                cell.value.intValue = -1;
            }
            break;
        }
        case FLOAT: {
            cell.value.floatValue = strtof(input, &endptr);
            if (*endptr != '\0') {
                cell.type = EMPTY;
                cell.value.intValue = -1;
            }
            break;
        }
        case DOUBLE: {
            cell.value.doubleValue = strtod(input, &endptr);
            if (*endptr != '\0') {
                cell.type = EMPTY;
                cell.value.intValue = -1;
            }
            break;
        }
        case CHAR: {
            cell.value.charValue = input[0];
            break;
        }
        case STRING: {
            strcpy(cell.value.stringValue, input);
            break;
        }
        case EMPTY:
            break;
    }

    return cell;
}

int findRowIndex(Table* table, unsigned int rowId) {
    for (int i = 0; i < table->numRows; i++) {
        if (table->rows[i].id == rowId) {
            return i;
        }
    }
    return -1;
}

int rowExists(char* tableName, unsigned int rowId) {
    int tableIndex = findTableIndex(tableName);
    if (tableIndex == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        return 0;
    }

    Table* table = &tables[tableIndex];
    for (int i = 0; i < table->numRows; i++) {
        if (table->rows[i].id == rowId) {
            return 1;
        }
    }

    return 0;
}

void createRowLogic(Row newRow, char* tableName) {
    int tableIndex = findTableIndex(tableName);
    if (tableIndex == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        return;
    }

    Table* table = &tables[tableIndex];
    if (table->numRows >= MAX_ROWS) {
        printf("Erro: O número máximo de linhas foi atingido.\n");
        return;
    }

    table->rows[table->numRows] = newRow;
    table->numRows++;
    printf("A linha de ID %u foi criada com sucesso na tabela '%s'.\n", newRow.id, tableName);

}

void deleteRow(char* tableName, unsigned int rowId) {
    int tableIndex = findTableIndex(tableName);
    if (tableIndex == -1) {
        printf("Erro: A tabela '%s' não foi encontrada.\n", tableName);
        return;
    }

    Table* table = &tables[tableIndex];
    int rowIndex = findRowIndex(table, rowId);
    if (rowIndex == -1) {
        printf("Erro: A linha com ID %u não foi encontrada na tabela '%s'.\n", rowId, tableName);
        return;
    }


    for (int i = rowIndex; i < table->numRows - 1; i++) {
        table->rows[i] = table->rows[i + 1];
    }

    table->numRows--;
    printf("A linha com ID %u foi deletada com sucesso da tabela '%s'.\n", rowId, tableName);
}

void searchValue() {
    char tableName[MAX_NAME_LENGTH];
    char columnName[MAX_NAME_LENGTH];
    int found = 0;
    int foundRow = 0;
    int c;
    
    Column tempColumn;
    printf("Digite o nome da tabela: ");
    fgets(tableName, MAX_NAME_LENGTH, stdin);
    removeNewLine(tableName);
    int index = findTableIndex(tableName);
    

    if (index == -1) {
        printf("Tabela não encontrada.\n");
        searchValue();
        return;
    }
    Table tempTable = tables[index];

    printf("Escolha uma coluna para procurar o valor:\n");
    for (int i = 0; i < tempTable.numColumns; i++) {
        printf("%s\n", tempTable.columns[i].name);
    }
    fgets(columnName, MAX_NAME_LENGTH, stdin);
    removeNewLine(columnName);
    for (int i = 0; i < tempTable.numColumns; i++) {
        if (strcmp(tempTable.columns[i].name, columnName) == 0) {
            tempColumn = tempTable.columns[i];
            found = 1;
            break;
        }
    }

    if (found == 1) {
        printf("Digite o valor que está procurando: ");

        switch (tempColumn.type) {
            case INT: {
                int value;
                scanf("%d", &value);
                while ((c = getchar()) != '\n' && c != EOF);
                if (valueExistsInColumn(tempTable, tempColumn, tempTable.rows[0].cells, tempTable.numRows, &value, &foundRow)) {
                    printf("Valor encontrado na coluna %s. Linha: %d.\n", tempColumn.name, foundRow + 1);
                    break;
                } else {
                    valueNotFound(&value, tempTable, tempColumn);
                    break;
                }
            }
            case FLOAT: {
                float value;
                scanf("%f", &value);
                while ((c = getchar()) != '\n' && c != EOF);
                if (valueExistsInColumn(tempTable, tempColumn, tempTable.rows[0].cells, tempTable.numRows, &value, &foundRow)) {
                    printf("Valor encontrado na coluna %s. Linha: %d.\n", tempColumn.name, foundRow + 1);
                    break;
                } else {
                    valueNotFound(&value, tempTable, tempColumn);
                    break;
                }
            }
            case DOUBLE: {
                double value;
                scanf("%lf", &value);
                while ((c = getchar()) != '\n' && c != EOF);
                if (valueExistsInColumn(tempTable, tempColumn, tempTable.rows[0].cells, tempTable.numRows, &value, &foundRow)) {
                    printf("Valor encontrado na coluna %s. Linha: %d.\n", tempColumn.name, foundRow + 1);
                    break;
                } else {
                    valueNotFound(&value, tempTable, tempColumn);
                    break;
                }
            }
            case STRING: {
                char value[MAX_CELL_LENGTH];
                fgets(value, MAX_CELL_LENGTH, stdin);
                removeNewLine(value);
                if (valueExistsInColumn(tempTable, tempColumn, tempTable.rows[0].cells, tempTable.numRows, value, &foundRow)) {
                    printf("Valor encontrado na coluna %s. Linha: %d.\n", tempColumn.name, foundRow + 1);
                    break;
                } else {
                    valueNotFound(value, tempTable, tempColumn);
                    break;
                }
            }
            case CHAR: {
                char value;
                scanf(" %c", &value);
                while ((c = getchar()) != '\n' && c != EOF);
                if (valueExistsInColumn(tempTable, tempColumn, tempTable.rows[0].cells, tempTable.numRows, &value, &foundRow)) {
                    printf("Valor encontrado na coluna %s. Linha: %d.\n", tempColumn.name, foundRow + 1);
                    break;
                } else {
                    printf("Valor não encontrado. Valores da coluna %s:\n", tempColumn.name);
                    for(int i = 0; i < tempTable.numRows; i++){
                        printf("%c\n", tempTable.rows[i].cells[findColumnIndex(tables, tempColumn.name)].value.charValue);
                    }
                    break;

                }
                
            }
            default:
                break;
        }
    } else {
        printf("Coluna não encontrada.\n");
        searchValue();
    }
}

/**
 * Função: readCell
 * ----------------
 * Solicita ao usuário o tipo de dados e o valor da célula.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova célula com o tipo EMPTY.
 * 2. Solicita ao usuário o tipo de dados da célula.
 * 3. Verifica se o usuário quer deixar a célula como vazia. Se sim, retorna a célula.
 * 4. Verifica se o tipo de dados é válido. Se não for, solicita ao usuário que digite novamente.
 * 5. Solicita ao usuário o valor da célula.
 * 6. Retorna a célula.
 *
 * @return: A célula.
 */

/**
 * Função: findRowIndex
 * --------------------
 * Encontra o índice de uma linha específica em uma tabela, com base no ID da linha.
 *
 * A função segue os seguintes passos:
 * 1. Percorre todas as linhas da tabela.
 * 2. Compara o ID de cada linha com o ID fornecido.
 * 3. Se encontrar uma linha com o mesmo ID, retorna o índice da linha.
 * 4. Se não encontrar uma linha com o mesmo ID, retorna -1.
 *
 * @param table: Um ponteiro para a tabela.
 * @param rowId: O ID da linha.
 * @return: O índice da linha, ou -1 se a linha não for encontrada.
 */

/**
 * Função: rowExists
 * -----------------
 * Verifica se uma linha com um determinado ID já existe em uma tabela específica.
 *
 * A função segue os seguintes passos:
 * 1. Encontra o índice da tabela.
 * 2. Se a tabela não for encontrada, imprime uma mensagem de erro e retorna 0.
 * 3. Percorre todas as linhas da tabela.
 * 4. Compara o ID de cada linha com o ID fornecido.
 * 5. Se encontrar uma linha com o mesmo ID, retorna 1.
 * 6. Se não encontrar uma linha com o mesmo ID, retorna 0.
 *
 * @param tableName: O nome da tabela.
 * @param rowId: O ID da linha.
 * @return: 1 se a linha existir, 0 se não existir.
 */

/**
 * Função: createRowBusinessLogic
 * ------------------------------
 * Adiciona uma nova linha a uma tabela específica.
 *
 * A função segue os seguintes passos:
 * 1. Encontra o índice da tabela.
 * 2. Se a tabela não for encontrada, imprime uma mensagem de erro e retorna.
 * 3. Verifica se o número máximo de linhas foi atingido. Se sim, imprime uma mensagem de erro e retorna.
 * 4. Adiciona a nova linha à tabela.
 * 5. Incrementa o número de linhas na tabela.
 * 6. Imprime uma mensagem informando que a linha foi criada com sucesso.
 *
 * @param newRow: A nova linha.
 * @param tableName: O nome da tabela.
 */


/**
 * Função: deleteRow
 * -----------------
 * Deleta uma linha de uma tabela específica.
 *
 * A função segue os seguintes passos:
 * 1. Encontra o índice da tabela.
 * 2. Se a tabela não for encontrada, imprime uma mensagem de erro e retorna.
 * 3. Encontra o índice da linha.
 * 4. Se a linha não for encontrada, imprime uma mensagem de erro e retorna.
 * 5. Remove a linha da tabela.
 * 6. Decrementa o número de linhas na tabela.
 * 7. Imprime uma mensagem informando que a linha foi deletada com sucesso.
 *
 * @param tableName: O nome da tabela.
 * @param rowId: O ID da linha.
 */

/**
 * Função: searchValue
 * -----------------
 * Procura um valor em uma determinada tabela.
 * 
 * A função segue os seguintes passos:
 * 1. Solicita o nome de uma tabela;
 * 2. Percorre o vetor de tabelas procurando pela tabela solicitada;
 * 3. Se não encontrar, printa um erro e chama a função searchValue novamente;
 * 4. Se encontrar, armazena a tabela solicitada numa variável temporária;
 * 5. Lista todas as colunas da tabela e pergunta em qual o usuário deseja procurar;
 * 6. Se não encontrar, printa um erro e chama a função searchValue novamente;
 * 7. Se encontrar, armazena a coluna solicitada numa variável temporária;
 * 8. Recebe um valor de qualquer tipo para procurar na coluna;
 * 9. Retorna se o valor foi encontrado e se sim, em qual linha;
 * 10. Se o valor não for encontrado, chama a função valueNotFound().
*/