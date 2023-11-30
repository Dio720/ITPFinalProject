// Descrição: Arquivo principal do projeto
// Created by dio on 24/11/23.
//

#include "database.h"
#include "file_operations.h"
#include "table.h"

Table tables[10];  // Ajustar de acordo com o número máximo de tabelas ou alocar dinâmicamente
int num_tables = 0;

int main() {
    const char *filename = "database.txt";  // Nome qualquer ai pra teste

    initialize_database(filename);  // Inicializa o banco de dados

    list_tables(filename);            // Lista as tabelas do banco de dados

    create_table(filename);  // Cria uma nova tabela

    create_row(tables[10], filename);

    delete_table(filename);  // Deleta uma tabela

    save_tables_to_file(filename);  // Salva as tabelas no arquivo

    return 0;
}

// última atualização: 2023-11-26 -- dio
