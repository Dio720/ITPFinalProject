// Funções relacionadas a manipulação de arquivos
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_FILE_OPERATIONS_H
#define PROJETO_FINAL_ITP_FILE_OPERATIONS_H

#include "database.h"

FILE* initialize_database(const char *filename);    // Inicializa o banco de dados
void save_tables_to_file(const char *filename);    // Salva as tabelas no arquivo
void load_tables_from_file(FILE *file);           // Carrega as tabelas do arquivo

#endif //PROJETO_FINAL_ITP_FILE_OPERATIONS_H

// úlitma atualização 2023-11-25