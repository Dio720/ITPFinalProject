//
// Created by dio on 02/12/23.
//

#include "utilsTable.h"
#include "database.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

extern Table tables[MAX_TABLES];
extern int numTables;

int isValidName(char* name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!isalnum((unsigned char)name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int findColumnIndex(Table* table, char* columnName) {
    for (int i = 0; i < table->numColumns; i++) {
        if (strcmp(table->columns[i].name, columnName) == 0) {
            return i;
        }
    }
    return -1;
}

char* readNewTableName() {
    char* tableName = malloc(MAX_NAME_LENGTH * sizeof(char));

    while (1) {
        readString(tableName, MAX_NAME_LENGTH);

        if (strcmp(tableName, "q") == 0 || strcmp(tableName, "Q") == 0) {
            free(tableName);
            return NULL;
        }

        if (strlen(tableName) == 0 || strlen(tableName) > MAX_NAME_LENGTH) {
            printf("Erro: O nome da tabela deve ter no máximo %d caracteres. Digite novamente: ", MAX_NAME_LENGTH - 1);
            continue;
        }

        if (findTableIndex(tableName) != -1) {
            printf("Erro: A tabela '%s' já existe. Digite novamente: ", tableName);
            continue;
        }

        break;
    }

    return tableName;
}

char* readTableName() {
    char* tableName = malloc(MAX_NAME_LENGTH * sizeof(char));
    char* suggestedTableName;

    while (1) {
        readString(tableName, MAX_NAME_LENGTH);

        if (strcmp(tableName, "q") == 0 || strcmp(tableName, "Q") == 0) {
            free(tableName);
            return NULL;
        }

        if (strlen(tableName) == 0 || strlen(tableName) > MAX_NAME_LENGTH) {
            printf("Erro: O nome da tabela deve ter no máximo %d caracteres. Digite novamente: ", MAX_NAME_LENGTH - 1);
            continue;
        }

        int tableIndex = findTableIndex(tableName);
        if (tableIndex == -1) {
            char* existingTableNames[MAX_TABLES];
            for (int i = 0; i < numTables; i++) {
                existingTableNames[i] = tables[i].name;
            }
            suggestedTableName = suggestName(tableName, (const char **)existingTableNames, numTables);
            if (suggestedTableName != NULL) {
                printf("A tabela '%s' não existe. Você quis dizer '%s'? (s/n): ", tableName, suggestedTableName);
                char response = readChar();
                if (response == 's' || response == 'S') {
                    free(tableName);
                    tableName = suggestedTableName;
                } else {
                    printf("Deseja tentar novamente ou voltar ao menu? (t/m): ");
                    char retry = readChar();
                    if (retry == 'm' || retry == 'M') {
                        free(suggestedTableName);
                        free(tableName);
                        return NULL;
                    }
                    free(suggestedTableName);
                    continue;
                }
            }
        }

        break;
    }

    return tableName;
}

char* readColumnName(Table* table) {
    char* columnName = malloc(MAX_NAME_LENGTH * sizeof(char));

    while (1) {
        readString(columnName, MAX_NAME_LENGTH);

        if (strcmp(columnName, "q") == 0 || strcmp(columnName, "Q") == 0) {
            free(columnName);
            return NULL;
        }

        if (strlen(columnName) == 0 || strlen(columnName) > MAX_NAME_LENGTH) {
            printf("Erro: O nome da coluna deve ter no máximo %d caracteres. Digite novamente: ", MAX_NAME_LENGTH - 1);
            continue;
        }

        if (findColumnIndex(table, columnName) != -1) {
            printf("Erro: A coluna '%s' já existe na tabela. Digite novamente: ", columnName);
            continue;
        }

        break;
    }

    return columnName;
}

DataType readColumnType() {
    printf("Digite o tipo da coluna:\n");
    printf("1 - Inteiro\n");
    printf("2 - Float\n");
    printf("3 - Double\n");
    printf("4 - Char\n");
    printf("5 - String\n");
    printf("Digite o número correspondente ao tipo: ");
    int type = readInteger();

    while (type < 1 || type > 5) {
        printf("Tipo inválido. Digite novamente: ");
        type = readInteger();
    }

    switch (type) {
        case 1:
            return INT;
        case 2:
            return FLOAT;
        case 3:
            return DOUBLE;
        case 4:
            return CHAR;
        case 5:
            return STRING;
        default:
            return EMPTY;
    }
}

const char* printColumnType(DataType columnType) {
    switch (columnType) {
        case INT:
            return "Inteiro";
        case FLOAT:
            return "Float";
        case DOUBLE:
            return "Double";
        case CHAR:
            return "Char";
        case STRING:
            return "String";
        default:
            return "Desconhecido";
    }
}

int findTableIndex(char* tableName) {
    int i;
    for (i = 0; i < numTables; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            return i;
        }
    }

    return -1;
}

int valueExistsInColumn(Table table, Column column, Cell cells[], int numRows, void* value, int* foundRow) {
    for (int i = 0; i < numRows; i++) {
        for(int j = 0; j < MAX_COLUMNS;j++)
        switch (column.type) {
            case INT:
                if (table.rows[i].cells[j].value.intValue == *((int*)value)) {
                    return 1; 
                    *foundRow = i;
                }
                break;
            case FLOAT:
                if (table.rows[i].cells[j].value.floatValue == *((float*)value)) {
                    return 1;
                    *foundRow = i;
                }
                break;
            case DOUBLE:
                if (table.rows[i].cells[j].value.doubleValue == *((double*)value)) {
                    return 1; 
                    *foundRow = i;
                }
                break;
            case CHAR:
                if (table.rows[i].cells[j].value.charValue == *((char*)value)) {
                    return 1;
                    *foundRow = i;
                }
                break;
            case STRING:
                if (strcmp(table.rows[i].cells[j].value.stringValue, (char*)value) == 0) {
                    return 1; 
                    *foundRow = i;
                }
                break;
            default:
                break;
        }
    }
    return 0; 
}

void valueNotFound(void *value, Table table, Column column) {
    int counterGreaterThan = 0;
    int counterLessThan = 0;
    int columnIndex = findColumnIndex(tables, column.name);
    char **nameArray[table.numRows];

    if (column.type == INT || column.type == FLOAT || column.type == DOUBLE) {
        for (int i = 0; i < table.numRows; i++) {
            switch (column.type) {
                case INT:
                    if (table.rows[i].cells[columnIndex].value.intValue > *((int*)value)) {
                        counterGreaterThan++;
                    } else if (table.rows[i].cells[columnIndex].value.intValue < *((int*)value)) {
                        counterLessThan++;
                    }
                    break;
                case FLOAT:
                    if (table.rows[i].cells[columnIndex].value.floatValue > *((float*)value)) {
                        counterGreaterThan++;
                    } else if (table.rows[i].cells[columnIndex].value.floatValue < *((float*)value)) {
                        counterLessThan++;
                    }
                    break;
                case DOUBLE:
                    if (table.rows[i].cells[columnIndex].value.doubleValue > *((double*)value)) {
                        counterGreaterThan++;
                    } else if (table.rows[i].cells[columnIndex].value.doubleValue < *((double*)value)) {
                        counterLessThan++;
                    }
                    break;
            }
        }

        printf("Valor não encontrado. Existem %d valores maiores e %d valores menores que o solicitado. Gostaria de saber quais?\n", counterGreaterThan, counterLessThan);
        printf("Para valores maiores, digite G.\nPara valores menores, digite L.\n");

        char entrada;
        scanf(" %c", &entrada);
        entrada = toupper(entrada);

        if (entrada == 'G') {
            for (int i = 0; i < table.numRows; i++) {
                switch (column.type) {
                    case INT:
                        if (table.rows[i].cells[columnIndex].value.intValue > *((int*)value)) {
                            printf("%d ", table.rows[i].cells[columnIndex].value.intValue);
                        }
                        break;
                    case FLOAT:
                        if (table.rows[i].cells[columnIndex].value.floatValue > *((float*)value)) {
                            printf("%.2f ", table.rows[i].cells[columnIndex].value.floatValue);
                        }
                        break;
                    case DOUBLE:
                        if (table.rows[i].cells[columnIndex].value.doubleValue > *((double*)value)) {
                            printf("%.2lf ", table.rows[i].cells[columnIndex].value.doubleValue);
                        }
                        break;
                }
            }
        } else if (entrada == 'L') {
            for (int i = 0; i < table.numRows; i++) {
                switch (column.type) {
                    case INT:
                        if (table.rows[i].cells[columnIndex].value.intValue < *((int*)value)) {
                            printf("%d ", table.rows[i].cells[columnIndex].value.intValue);
                        }
                        break;
                    case FLOAT:
                        if (table.rows[i].cells[columnIndex].value.floatValue < *((float*)value)) {
                            printf("%.2f ", table.rows[i].cells[columnIndex].value.floatValue);
                        }
                        break;
                    case DOUBLE:
                        if (table.rows[i].cells[columnIndex].value.doubleValue < *((double*)value)) {
                            printf("%.2lf ", table.rows[i].cells[columnIndex].value.doubleValue);
                        }
                        break;
                }   
            }
        }
    }
    else if(column.type == STRING){
        char *nameArray[table.numRows];
        for(int i = 0; i < table.numRows; i++){
            nameArray[i] = strdup(table.rows[i].cells[columnIndex].value.stringValue);
        }

        char *suggestion = suggestName(value, (const char **)nameArray, table.numRows);
        printf("Valor não encontrado.\nVocê quis dizer: %s? [S|N]\n", suggestion);


        char entrada;
        scanf("%c", &entrada);
        entrada = toupper(entrada);
        if(entrada == 'S'){
            printf("Valor encontrado na coluna %s.", column.name);
        }
        else if(entrada == 'N'){
            printf("Valor não encontrado.");
        }


        for(int i = 0; i < table.numRows; i++){
            free(nameArray[i]);
        }
}

}


/**
 * Função: isValidName
 * -------------------
 * Verifica se o nome fornecido é válido.
 *
 * A função segue os seguintes passos:
 * 1. Percorre cada caractere do nome.
 * 2. Verifica se o caractere é alfanumérico ou um espaço. Se não for, retorna 0.
 * 3. Se todos os caracteres forem alfanuméricos ou espaços, retorna 1.
 *
 * @param name: O nome a ser verificado.
 * @return: 1 se o nome for válido, 0 se não for.
 */

/**
 * Função: findColumnIndex
 * ----------------------
 * Encontra o índice de uma coluna em uma tabela.
 *
 * A função segue os seguintes passos:
 * 1. Percorre cada coluna na tabela.
 * 2. Compara o nome de cada coluna com o nome da coluna fornecido.
 * 3. Se encontrar uma coluna com o mesmo nome, retorna o índice da coluna.
 * 4. Se não encontrar uma coluna com o mesmo nome, retorna -1.
 *
 * @param table: Um ponteiro para a tabela onde a coluna será procurada.
 * @param columnName: O nome da coluna a ser procurada.
 * @return: O índice da coluna, ou -1 se a coluna não for encontrada.
 */

/**
 * Função: readNewTableName
 * ------------------------
 * Solicita ao usuário o nome da nova tabela.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova string para armazenar o nome da tabela.
 * 2. Entra em um loop onde solicita ao usuário que digite o nome da tabela.
 * 3. Verifica se o usuário quer sair. Se sim, libera a memória alocada para o nome da tabela e retorna NULL.
 * 4. Verifica se o nome da tabela é válido e se a tabela já existe. Se não for válido ou já existir, solicita ao usuário que digite novamente.
 * 5. Se o nome da tabela for válido e a tabela não existir, quebra o loop e retorna o nome da tabela.
 *
 * @return: O nome da nova tabela, ou NULL se o usuário decidir sair.
 */

/**
 * Função: readTableName
 * ---------------------
 * Solicita ao usuário o nome da tabela.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova string para armazenar o nome da tabela.
 * 2. Entra em um loop onde solicita ao usuário que digite o nome da tabela.
 * 3. Verifica se o usuário quer sair. Se sim, libera a memória alocada para o nome da tabela e retorna NULL.
 * 4. Verifica se o nome da tabela é válido. Se não for, solicita ao usuário que digite novamente.
 * 5. Verifica se a tabela já existe. Se não existir, sugere um nome de tabela e pergunta ao usuário se ele gostaria de usar a sugestão.
 * 6. Se o usuário aceitar a sugestão, usa a sugestão como o nome da tabela.
 * 7. Se a tabela existir, quebra o loop e retorna o nome da tabela.
 *
 * @return: O nome da tabela, ou NULL se o usuário decidir sair.
 */

/**
 * Função: readColumnName
 * ----------------------
 * Solicita ao usuário o nome da coluna.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa uma nova string para armazenar o nome da coluna.
 * 2. Entra em um loop onde solicita ao usuário que digite o nome da coluna.
 * 3. Verifica se o usuário quer sair. Se sim, libera a memória alocada para o nome da coluna e retorna NULL.
 * 4. Verifica se o nome da coluna é válido. Se não for, solicita ao usuário que digite novamente.
 * 5. Verifica se a coluna já existe na tabela. Se sim, solicita ao usuário que digite novamente.
 * 6. Se o nome da coluna for válido e a coluna não existir, quebra o loop e retorna o nome da coluna.
 *
 * @param table: Um ponteiro para a tabela onde a coluna será adicionada.
 * @return: O nome da coluna, ou NULL se o usuário decidir sair.
 */

/**
 * Função: readColumnType
 * ----------------------
 * Solicita ao usuário o tipo de dados da coluna.
 *
 * A função segue os seguintes passos:
 * 1. Imprime as opções de tipos de dados.
 * 2. Solicita ao usuário que digite o número correspondente ao tipo de dados.
 * 3. Verifica se o tipo de dados é válido. Se não for, solicita ao usuário que digite novamente.
 * 4. Retorna o tipo de dados correspondente ao número digitado pelo usuário.
 *
 * @return: O tipo de dados da coluna.
 */

/**
 * Função: printColumnType
 * -----------------------
 * Retorna uma string representando o tipo de dados de uma coluna.
 *
 * A função segue os seguintes passos:
 * 1. Verifica o tipo de dados da coluna.
 * 2. Retorna uma string que representa o tipo de dados.
 *
 * @param columnType: O tipo de dados da coluna.
 * @return: Uma string representando o tipo de dados.
 */

/**
 * Função: findTableIndex
 * ----------------------
 * Encontra o índice de uma tabela no array de tabelas.
 *
 * A função segue os seguintes passos:
 * 1. Percorre o array de tabelas.
 * 2. Compara o nome de cada tabela com o nome da tabela fornecido.
 * 3. Se encontrar uma tabela com o mesmo nome, retorna o índice da tabela.
 * 4. Se não encontrar uma tabela com o mesmo nome, retorna -1.
 *
 * @param tableName: O nome da tabela.
 * @return: O índice da tabela, ou -1 se a tabela não for encontrada.
 */

/**
 * Função: valueExistsInColumn
 * ---------------------------
 * Verifica se um valor existe em uma coluna.
 * 
 * A função segue os seguintes passos:
 * 1. Percorre todas as células de uma coluna;
 * 2. Verifica se o valor recebido está dentro de alguma das células, levando em conta seu tipo;
 * 3. Retorna 1 se o valor foi encontrado;
 * 4. Armazena no ponteiro foundRow o número da linha que contém o valor;
 * 5. Retorna 0 se o valor não for encontrado.
*/

/**
 * Função: valueNotFound
 * ---------------------
 * Sugere valores quando o valor procurado não foi encontrado.
 * 
 * A função segue os seguintes passos:
 * 1. Verifica o tipo da coluna;
 * 2. Se a coluna for de tipo numérico, conta quantos valores são maiores e quantos são menores que o valor solicitado;
 * 3. Printa essa quantidade e solicita ao usuário se ele quer ver os valores menores ou os valores maiores;
 * 4. Printa o que o usuário escolher.
 * 5. Se a coluna for de tipo string, cria um array com as strings de cada célula;
 * 6. Chama a função suggestName e printa uma sugestão de nome;
 * 7. Por fim, solicita feedback do usuário quanto a sugestão e finaliza.
*/

/** Patch Notes (03/12/2023 ~ Dio):
 * Criado o arquivo com todas as suas funções:
 * - Adicionada a função isValidName para verificar se o nome da tabela é válido
 * - Adicionada a função findColumnIndex para encontrar o índice de uma coluna em uma tabela
 * - Adicionada a função readNewTableName para solicitar ao usuário o nome da nova tabela
 * - Adicionada a função readTableName para solicitar ao usuário o nome da tabela
 * - Adicionada a função readColumnName para solicitar ao usuário o nome da coluna
 * - Adicionada a função readColumnType para solicitar ao usuário o tipo de dados da coluna
 * - Adicionada a função printColumnType para retornar uma string representando o tipo de dados de uma coluna
 */