// Funções relacionadas a manipulação de tabelas:
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_TABLE_H
#define PROJETO_FINAL_ITP_TABLE_H

#include "database.h"
#include <stdbool.h>

Table createTable(const char *filename); // Cria uma nova tabela
void listTables(const char *filename);   // Lista as tabelas do banco de dados
void deleteTable(const char *filename);  // Deleta uma tabela do banco de dados

#endif // PROJETO_FINAL_ITP_TABLE_H

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 * - Apaguei a versão anterior para poder recomeçar de maneira melhor
 */
