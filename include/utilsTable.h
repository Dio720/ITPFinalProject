//
// Created by dio on 02/12/23.
//

#ifndef ITPFINALPROJECT_UTILSTABLE_H
#define ITPFINALPROJECT_UTILSTABLE_H

#include "database.h"

int isValidName(char* name);
char* readNewTableName();
char* readTableName();
char* readColumnName(Table* table);
DataType readColumnType();
const char* printColumnType(DataType columnType);
int findTableIndex(char* tableName);
int findColumnIndex(Table* table, char* columnName);

#endif //ITPFINALPROJECT_UTILSTABLE_H


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