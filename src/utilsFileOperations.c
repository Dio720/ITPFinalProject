// Descrição: Funções auxiliares na manipulação de arquivos
// Created by dio on 27/11/23.
//

#include "database.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Table tables[MAX_TABLES];
extern int numTables;


bool convertStringToCell(const char *string, Cell *cell, DataType columnType) {
    if (string == NULL || cell == NULL) {
        fprintf(stderr, "Erro: Ponteiro nulo\n");
        return false;
    }
    memset(cell, 0, sizeof(Cell));

    switch (columnType) {
        case INT:
            cell->value.intValue = atoi(string);
            cell->type = INT;
            break;
        case FLOAT:
            cell->value.floatValue = atof(string);
            cell->type = FLOAT;
            break;
        case DOUBLE:
            cell->value.doubleValue = atof(string);
            cell->type = DOUBLE;
            break;
        case CHAR:
            cell->value.charValue = string[0];
            cell->type = CHAR;
            break;
        case STRING:
            strcpy(cell->value.stringValue, string);
            cell->value.stringValue[MAX_CELL_LENGTH - 1] = '\0';
            cell->type = STRING;
            break;
        default:
            cell->type = EMPTY;
            cell->value.emptyValue = '\0';
    }

    return true;
}

char *processRows(char *line, Table *table) {
    for (unsigned int i = 0; i < table->numRows; i++) {
        if (line == NULL) {
            fprintf(stderr, "Erro: Número de linhas menor que o esperado\n");
            return NULL;
        }

        char restOfLine[MAX_LINE_LENGTH];
        sscanf(line, "Linha %*d: %[^\n]", restOfLine);

        char *cellStart = restOfLine;
        for (unsigned int j = 0; j < table->numColumns; j++) {
            char cellValue[MAX_CELL_LENGTH] = {0};
            int charsRead;

            int result =
                    sscanf(cellStart, "\"%[^\"]\"%*[,]%n", cellValue, &charsRead);

            if (result == 1) {
                convertStringToCell(cellValue, &table->rows[i].cells[j],
                                    table->columns[j].type);
                cellStart += charsRead + 1;
            } else {
                initCellAsEmpty(&table->rows[i].cells[j]);
            }

            if (j == 0) {
                table->rows[i].id = atoi(cellValue);
            }
        }

        line = strchr(line, '\n');
        if (line != NULL)
            line++;
    }
    return line;
}

char *processTable(char *line) {
    char tableName[MAX_NAME_LENGTH];
    unsigned int numColumns, numRows;

    sscanf(line,"Tabela %*d: \"%49[^\"]\", Quantidade de colunas: %u, Quantidade de linhas: %u", tableName, &numColumns, &numRows);

    Table newTable = {0};
    strcpy(newTable.name, tableName);
    newTable.numColumns = numColumns;
    newTable.numRows = numRows;

    line = strchr(line, '\n');
    if (line != NULL)
        line++;

    for (unsigned int i = 0; i < numColumns; i++) {
        if (line == NULL)
            break;

        char columnName[MAX_NAME_LENGTH];
        unsigned int columnType;

        char *endOfLine = strchr(line, '\n');
        if (endOfLine != NULL)
            *endOfLine = '\0';

        sscanf(line, "Coluna %*d: \"%49[^\"]\", Tipo: %u", columnName, &columnType);
        strcpy(newTable.columns[i].name, columnName);
        newTable.columns[i].type = columnType;

        if (endOfLine != NULL)
            line = endOfLine + 1;
    }

    line = processRows(line, &newTable);
    tables[numTables++] = newTable;

    if (line == NULL) return NULL;
    char *startOfNextTable = strstr(line, "Tabela");

    return startOfNextTable;
}

bool isValidFileName(char* filename) {
    char invalidChars[] = "<>:\"/\\|?*"; // Caracteres inválidos para nomes de arquivos na maioria dos sistemas de arquivos
    for (int i = 0; i < strlen(filename); i++) {
        if (strchr(invalidChars, filename[i]) != NULL) {
            return false; // O nome do arquivo contém um caractere inválido
        }
    }
    return true; // O nome do arquivo é válido
}

/**
 * Função: convertStringToCell
 * ----------------------------
 * Converte uma string para uma célula.
 *
 * A função segue os seguintes passos:
 * 1. Verifica se a string ou a célula passadas como argumentos são nulas. Se
 * forem, imprime uma mensagem de erro e retorna false.
 * 2. Limpa a memória da célula para garantir que ela esteja vazia.
 * 3. Usa um switch para verificar o tipo da coluna. Dependendo do tipo da
 * coluna, a função converte a string para o tipo correspondente e armazena o
 * valor na célula.  Apesar de nunca ser, se o tipo da coluna for EMPTY, a função define o tipo da
 * célula como EMPTY e o valor como '\0'.
 * 4. Retorna true para indicar que a conversão foi bem-sucedida.
 *
 * @param string: A string a ser convertida.
 * @param cell: A célula onde o valor convertido será armazenado.
 * @param columnType: O tipo da coluna, que determina como a string será
 * convertida.
 * @return: Um valor booleano indicando se a conversão foi bem-sucedida.
 */

/**
 * Função: processRows
 * --------------------
 * Processa uma linha de entrada que representa uma linha de uma tabela.
 *
 * A função segue os seguintes passos:
 * 1. Percorre cada linha da tabela. Se a linha for nula, imprime uma mensagem
 * de erro e retorna NULL.
 * 2. Lê a linha de entrada e extrai o restante da linha após "Linha X:".
 * 3. Percorre cada célula da linha. Para cada célula:
 *    - Lê o valor da célula da linha de entrada.
 *    - Se a leitura for bem-sucedida, converte a string para uma célula usando
 * a função convertStringToCell.
 *    - Se a leitura falhar, inicializa a célula como vazia usando a função
 * initCellAsEmpty.
 * 4. Avança para a próxima linha.
 * 5. Retorna a posição da próxima linha após processar todas as linhas.
 *
 * @param line: A linha de entrada a ser processada.
 * @param table: A tabela onde as linhas processadas serão armazenadas.
 * @return: A posição da próxima linha após processar todas as linhas.
 */

/**
 * Função: processTable
 * ---------------------
 * Processa uma linha de entrada que representa uma tabela.
 *
 * A função segue os seguintes passos:
 * 1. Lê a linha de entrada e extrai o nome da tabela, o número de colunas e o
 * número de linhas.
 * 2. Inicializa uma nova tabela com o nome, número de colunas e número de
 * linhas extraídos.
 * 3. Avança para a próxima linha.
 * 4. Percorre cada coluna da tabela. Para cada coluna, lê a linha de entrada e
 * extrai o nome e o tipo da coluna. Armazena o nome e o tipo na coluna
 * correspondente da nova tabela.
 * 5. Chama a função processRows para processar as linhas da tabela. A função
 * processRows retorna a posição da próxima linha após processar todas as
 * linhas.
 * 6. Verifica se a função processRows retornou NULL. Se sim, imprime uma
 * mensagem de erro e retorna NULL.
 * 7. Encontra a posição do início da próxima tabela na linha de entrada.
 * 8. Adiciona a nova tabela ao banco de dados.
 * 9. Retorna a posição do início da próxima tabela.
 *
 * @param line: A linha de entrada a ser processada.
 * @return: A posição do início da próxima tabela.
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Funções criadas para auxiliar na manipulação de arquivos
 * - Adicionada a função convertStringToCell para processar o valor de uma célula da linha
 * - Adicionada a função processRows para processar as linhas de uma tabela
 * - Adicionada a função processTable para processar uma tabela
 */

/** Patch Notes (03/12/203 ~ Dio):
 * - Agora a chave primária das linhas são armazenadas corretamente
 * - Adicionada a isValidFileName
 */