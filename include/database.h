// Arquivo de cabeçalho para a estrutura de dados do projeto
// Created by dio on 24/11/23.
//

#ifndef PROJETO_FINAL_ITP_DATABASE_H
#define PROJETO_FINAL_ITP_DATABASE_H

#define MAX_TABLES 10
#define MAX_ROWS 20
#define MAX_NAME_LENGTH 50
#define MAX_COLUMNS 10
#define MAX_CELL_LENGTH 100
#define MAX_LINE_LENGTH 1009

typedef enum {
    EMPTY,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
} DataType;

typedef struct {
    union {
        char emptyValue;
        int intValue;
        float floatValue;
        double doubleValue;
        char charValue;
        char stringValue[MAX_CELL_LENGTH];
    } value;
    DataType type;
} Cell;

typedef struct {
    char name[MAX_NAME_LENGTH];
    DataType type;
} Column;

typedef struct {
    unsigned int id;
    Cell cells[10];
} Row;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Column columns[MAX_COLUMNS];
    unsigned int numColumns;
    unsigned int idColumn;
    unsigned int numRows;
    Row rows[MAX_ROWS];
} Table;

void initDatabase();
void initCellAsEmpty(Cell *cell);

#endif // PROJETO_FINAL_ITP_DATABASE_H

/** Patch Notes (28/11/23 -- Dio)
 * - Reestruturação do banco para melhorar a legibilidade e a organização.
 * - Documentação das funções.
 * - InitDatabase agora é uma função que inicializa o banco de dados com todos os valores vazios.
 * - InitCellAsEmpty agora é uma função que inicializa uma célula como vazia.
 */

/** Hotfix (01/12/23):
 * - Aumentei o tamanho máximo de uma linha para 1009 caracteres, porque é o tamanho máximo em tese que poderia ter.
 */