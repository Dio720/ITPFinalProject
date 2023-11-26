// Funções relacionadas à manipulação de arquivos
// Created by dio on 25/11/23.
//

#include "file_operations.h"
#include "database.h"
#include <stdio.h>
#include <string.h>

extern Table tables[10];  // Talvez a gente tenha que mudar isso para alocar dinâmicamente
extern int num_tables;    // Número de tabelas no banco de dados

// Função que inicializa o banco de dados
FILE* initialize_database(const char *filename) {   // Eu acho uma doidera o tipo FILE, descobri que assim dava certo depois de muita dor de cabeça
    FILE *file = fopen(filename, "r+");  // Tenta abrir o arquivo para leitura e escrita

    if (file != NULL)
        load_tables_from_file(file);    // Carrega as tabelas do arquivo, se ele existir
    else {
        file = fopen(filename, "w+"); // Se o arquivo não existir, cria um novo
        if (file == NULL)
            printf("Erro ao criar o arquivo.\n"); // Se der problema
    }
    return file;
}

// Função que carrega as tabelas do arquivo
void load_tables_from_file(FILE *file) {
    num_tables = 0;   // Zera o número de tabelas
    Table table;     // Tabela temporária
    char line[256]; // Buffer para ler uma linha do arquivo

    // Lê o arquivo linha por linha
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%49[^,],%d,%u", table.name, &table.num_columns, &table.primary_key) == 3) { // Lê o nome da tabela, o número de colunas e a chave primária (sscanf serve para ler uma string formatada)
            for (int i = 0; i < table.num_columns; i++)
                if (fgets(line, sizeof(line), file) == NULL || sscanf(line, "%49[^,],%d", table.columns[i].name, (int *)&table.columns[i].type) != 2) break; // Erro de leitura ou formatação inválida

            tables[num_tables++] = table;                            // Armazena os dados na memória RAM
            if (num_tables >= sizeof(tables) / sizeof(tables[0])) { // Verifica se o número máximo de tabelas foi atingido
                printf("Valor máximo de tabelas atingido nesse banco de dados.\n");
                break;
            }
        }
    }
    rewind(file); // Aponta o ponteiro do arquivo para o início
}


void save_tables_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");  // Tenta abrir o arquivo para escrita
    if (file == NULL) {                // Se der problema
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve as tabelas no arquivo
    for (int i = 0; i < num_tables; i++) {                                                           // O for aqui é só pra percorrer as tabelas
        fprintf(file, "%s,%d,%u\n", tables[i].name, tables[i].num_columns, tables[i].primary_key);  // Escreve o nome da tabela, o número de colunas e a chave primária
        for (int j = 0; j < tables[i].num_columns; j++)                                            // O for aqui é só pra percorrer as colunas
            fprintf(file, "%s,%d\n", tables[i].columns[j].name, tables[i].columns[j].type);       // Escreve os detalhes de cada coluna
    }

    fclose(file);
}

// última modificação: 2023-11-25 -- dio
