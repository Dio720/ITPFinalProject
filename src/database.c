// Descrição: Arquivo principal do projeto
// Created by dio on 24/11/23.
//

#include "database.h"
#include "utils_file_operations.h"
#include <string.h>

Table tables[MAX_TABLES] = {0}; // Ajustar de acordo com o número máximo de
// tabelas ou alocar dinâmicamente
int num_tables = 0;

void initDatabase() {
    for (int i = 0; i < MAX_TABLES; i++) {
        memset(tables[i].name, 0, sizeof(tables[i].name));
        tables[i].numColumns = 0;
        tables[i].idColumn = 0;
        tables[i].numRows = 0;
        for (int j = 0; j < MAX_COLUMNS; j++) {
            memset(tables[i].columns[j].name, 0, sizeof(tables[i].columns[j].name));
            tables[i].columns[j].type = EMPTY;
        }
        for (int j = 0; j < MAX_ROWS; j++) {
            tables[i].rows[j].id = 0;
            for (int k = 0; k < MAX_COLUMNS; k++) {
                initCellAsEmpty(&tables[i].rows[j].cells[k]);
            }
        }
    }
    num_tables = 0;
}

void initCellAsEmpty(Cell *cell) {
    if (cell == NULL) {
        fprintf(stderr, "Erro: Ponteiro nulo para initCellAsEmpty\n");
        return;
    }

    cell->type = EMPTY;
    cell->value.emptyValue = '\0';
}

/**
 * Função: initDatabase
 * ---------------------
 * Inicializa o banco de dados definindo todos os valores para 0 ou vazio.
 *
 * As tabelas são percorridas uma a uma. Para cada tabela:
 * - O nome da tabela é definido como uma string vazia.
 * - O número de colunas, a coluna do ID e o número de linhas são definidos como
 * 0.
 *
 * As colunas de cada tabela são percorridas uma a uma. Para cada coluna:
 * - O nome da coluna é definido como uma string vazia.
 * - O tipo da coluna é definido como INT.
 *
 * As linhas de cada tabela são percorridas uma a uma. Para cada linha:
 * - O ID da linha é definido como 0.
 *
 * As células de cada linha são percorridas uma a uma. Para cada célula:
 * - O tipo da célula é definido como INT.
 * - O valor da célula é definido como 0.
 *
 * Por fim, o número de tabelas no banco de dados é definido como 0.
 */

/**
 * Função: initCellAsEmpty
 * ------------------------
 * Inicializa uma célula como vazia.
 *
 * A função segue os seguintes passos:
 * 1. Verifica se a célula passada como argumento é nula. Se for, imprime uma
 * mensagem de erro e retorna.
 * 2. Define o tipo da célula como EMPTY.
 * 3. Define o valor da célula como '\0'.
 *
 * @param cell: A célula a ser inicializada como vazia.
 * @return: void
 */


/** Patch Notes (28/11/23 [~23:00] -- Dio)
 * - Reestruturação do banco para melhorar a legibilidade e a organização.
 * - Documentação das funções.
 * - InitDatabase agora é uma função que inicializa o banco de dados com todos os valores vazios.
 * - InitCellAsEmpty agora é uma função que inicializa uma célula como vazia.
 */