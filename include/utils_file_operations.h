// Funções para auxiliar na manipulação de arquivos:
// Created by dio on 27/11/23.
//

#ifndef PROJETO_FINAL_ITP_UTILS_FILE_OPERATIONS_H
#define PROJETO_FINAL_ITP_UTILS_FILE_OPERATIONS_H

#include "database.h"
#include <stdbool.h>
#include <stdio.h>

char *processTable(char *line);                                                // Processa uma linha de entrada que representa uma tabela
bool convertStringToCell(const char *string, Cell *cell, DataType columnType); // Converte uma string para uma célula
char *processRows(char *line, Table *table);                                   // Processa uma linha de entrada que representa uma linha

#endif // PROJETO_FINAL_ITP_UTILS_FILE_OPERATIONS_H

/** Patch Notes (28/11/2023 -- Dio):
 * - Funções criadas para auxiliar na manipulação de arquivos
 * - Adicionada a função convertStringToCell para processar o valor de uma célula da linha
 * - Adicionada a função processRows para processar as linhas de uma tabela
 * - Adicionada a função processTable para processar uma tabela
 */