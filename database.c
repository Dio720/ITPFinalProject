//
// Created by dio on 24/11/23.
//

#include "database.h"
#include <stdio.h>

Table tables[10];
int num_tables = 0;

void create_table() {
    // Função para criar uma nova tabela
    Table table;

    printf("Digite o nome da tabela: ");
    scanf("%s", table.name);

    printf("Digite o número de colunas: ");
    scanf("%d", &table.num_columns);

    // Ler os dados de cada coluna
    for (int i = 0; i < table.num_columns; i++) {
        printf("Digite o nome da coluna %d: ", i + 1);
        scanf("%s", table.columns[i].name);
        printf("Digite o tipo da coluna %d: ", i + 1);
        scanf("%d", &table.columns[i].type);
    }

    // Ler a chave primária
    printf("Digite o número da coluna que será a chave primária: ");
    scanf("%u", &table.primary_key);

    // Adicionar a tabela ao vetor de tabelas
    tables[num_tables] = table;
    num_tables++;

    // Abrir o arquivo para escrita
    FILE *file = fopen("database.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escrever os dados da tabela no arquivo
    fprintf(file, "Tabela: %s\n", table.name);
    fprintf(file, "Número de colunas: %d\n", table.num_columns);
    for (int i = 0; i < table.num_columns; i++) {
        fprintf(file, "Coluna %d: %s, Tipo: %d\n", i + 1, table.columns[i].name, table.columns[i].type);
    }
    fprintf(file, "Chave primária: %u\n", table.primary_key);

    // Fechar o arquivo
    fclose(file);
}

void list_tables() {
    // Implementação da função para listar todas as tabelas
}

void create_row() {
    // Implementação da função para criar uma nova linha em uma tabela
}

void list_data() {
    // Implementação da função para listar todos os dados de uma tabela
}

void search_value() {
    // Implementação da função para pesquisar um valor em uma tabela
}

void delete_row() {
    // Implementação da função para apagar uma tupla de uma tabela
}

void delete_table() {
    // Implementação da função para apagar uma tabela
}

// A main está construída apenas para testar as funções no momento
int main() {
    // Chamar a função para criar uma tabela
    create_table();

    // Chamar a função para listar as tabelas
    list_tables();

    // Adicionar mais chamadas de função conforme necessário

    return 0;
}