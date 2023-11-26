// Funções relacionadas a manipulação de tabelas:
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_TABLE_H
#define PROJETO_FINAL_ITP_TABLE_H
#include "database.h"

bool name_table_is_valid(const char *table_name);   // Verifica se o nome da tabela é válido
void create_table(const char *filename);           // Cria uma nova tabela
void list_tables(const char *filename);           // Lista as tabelas do banco de dados
void delete_table();                             // Deleta uma tabela do banco de dados

#endif //PROJETO_FINAL_ITP_TABLE_H

// última atualização: 2023-11-25 -- dio
