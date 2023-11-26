// Descrição: Arquivo principal do projeto
// Created by dio on 24/11/23.
//

#include "database.h"
#include "file_operations.h"
#include "table.h"
#include "data.h"
#include "aux_functions.h"
#include <stdio.h>
#include <strings.h>
#include <limits.h>

Table tables[10];  // Ajustar de acordo com o número máximo de tabelas ou alocar dinâmicamente
int num_tables = 0;

int main() {
    const char *filename = "database.txt";  // Nome qualquer ai pra teste

    initialize_database(filename);  // Inicializa o banco de dados

    create_table(filename);  // Cria uma nova tabela

    save_tables_to_file(filename);  // Salva as tabelas no arquivo

    return 0;
}

// última atualização: 2023-11-25 -- dio
