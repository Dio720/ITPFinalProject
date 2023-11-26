// Descrição: Arquivo responsável por implementar as funções de manipulação de tabelas
// Created by dio on 25/11/23.
//

#include "database.h"
#include "file_operations.h"
#include "aux_functions.h"
#include <stdio.h>
#include <strings.h>
#include <limits.h>

extern Table tables[10];
extern int num_tables;

// Função para verificar se o nome da tabela é válido
bool name_table_is_valid(const char *table_name) {
    for (int i = 0; i < num_tables; i++)
        if (strcasecmp(table_name, tables[i].name) == 0) return false; // Se o nome da tabela já existir, retorna falso,
    // strcasecmp serve para comparar duas strings ignorando o case sensitive
    return true;
}

// Função para criar uma nova tabela
void create_table(const char *filename) {
    Table table; // Tabela temporária
    
    // TODO: alguma entrada não for válida, um loop?
    // TODO: Maior interatividade dentro dela?

    // Recebe o nome da tabela
    printf("Digite o nome da tabela: \n");
    fgets(table.name, sizeof(table.name), stdin); // fgets porque é mais seguro
    remove_newline(table.name);                   // Remove o \n do final da string

    // Verifica se o nome da tabela é válido
    if (!name_table_is_valid(table.name)) {
        printf("O nome da tabela já existe. tente novamente:\n");
        return;
    } // Eu acho válido, mas podemos mudar para um loop em que o usuário digita o nome da tabela até que seja válido

    // Recebe o número de colunas
    printf("Digite o número de colunas: \n");
    int num_columns = read_integer_from_user(); // Chama uma função do aux_functions que faz essa leitura de maneira segura
    if (num_columns == INT_MAX || num_columns < 1 || num_columns > 10) { // Como está definida cada tabela pode ter no máximo 10 colunas (INT_MAX é o caso de erro da função que acabou de chamar)
        printf("Número de colunas inválido.\n");
        return;
    }
    table.num_columns = num_columns;    // Atribui o número de colunas à tabela

    // Recebe os detalhes de cada coluna
    for (int i = 0; i < table.num_columns; i++) {
        printf("Digite o nome da coluna %d: \n", i + 1);
        fgets(table.columns[i].name, sizeof(table.columns[i].name), stdin); // fgets porque é mais seguro
        remove_newline(table.columns[i].name); // Remove o \n do final da string

        printf("Digite o tipo da coluna %d (0 para INT, 1 para FLOAT, 2 para DOUBLE, 3 para CHAR e 4 para STRING): \n", i + 1); // Remete ao enum criado no database.h
        int type = read_integer_from_user();    // Chama uma função do aux_functions que faz essa leitura de maneira segura
        if (type == INT_MAX || type < 0 || type > 4) {  // Verifica se o número se encaixa no enum (INT_MAX, caso de erro)
            printf("Tipo de coluna inválido.\n");
            return;
        }
        table.columns[i].type = type;
    }

    // Recebe a chave primária
    printf("Digite o número da coluna que será a chave primária: \n");
    int table_primary_key = read_integer_from_user();
    if (table_primary_key == INT_MAX || table_primary_key < 0 || table_primary_key > table.num_columns) { // Vê se o número não é negativo ou maior que o número de colunas (INT_MAX, preciso nem dizer)
        return;
    }
    table.primary_key = (unsigned int)table_primary_key; // Atribui a chave primária à tabela o cast é necessário porque a chave primária é um unsigned int

    // Adiciona a tabela criada ao vetor de tabelas
    tables[num_tables++] = table;

    // Salva as tabelas no arquivo
    save_tables_to_file(filename);
}

void list_tables(const char *filename) {
    // Implementação da função para listar todas as tabelas
}

void delete_table() {
    // Implementação da função para deletar uma tabela
}

// Última modificação 2023-11-25 -- dio