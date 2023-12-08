// Funções relacionadas a manipulação de tabelas:
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_TABLE_H
#define PROJETO_FINAL_ITP_TABLE_H

#include "database.h"
#include <stdbool.h>

void createTableLogic(Table newTable);
void deleteTableLogic(char* tableName);
void createTable();
void listTables();
void listTableData(char* tableName);

#endif // PROJETO_FINAL_ITP_TABLE_H

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 * - Apaguei a versão anterior para poder recomeçar de maneira melhor
 */

/** Patch Notes (01/12/2023 ~ Dio):
 * Implementei as funções desse arquivo.
 * Troquei as chamadas previamente estabelecidas
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * Adicionei a createTableLogic
 * Adicionei a deleteTableLogic
 * Adicionei a listTableData
 */