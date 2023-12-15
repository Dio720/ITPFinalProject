// Funções à manipulação de dados dentro das tabelas
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_ROW_H
#define PROJETO_FINAL_ITP_ROW_H

#include "database.h"

Cell readCell();
int findRowIndex(Table* table, unsigned int rowId);
int rowExists(char* tableName, unsigned int rowId);
void createRowLogic(Row newRow, char* tableName);
void deleteRow(char* tableName, unsigned int rowId);
void searchValue();


#endif // PROJETO_FINAL_ITP_ROW_H

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * Adicionei a createRowLogic
 * Adicionei a deleteRow
 * Adicionei a findRowIndex
 * Adicionei a rowExists
 */