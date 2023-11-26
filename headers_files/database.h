// Arquivo de cabeçalho para a estrutura de dados do projeto
// Created by dio on 24/11/23.
//

#ifndef PROJETO_FINAL_ITP_DATABASE_H
#define PROJETO_FINAL_ITP_DATABASE_H

#include <stdio.h>

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} DataType; // Tipos de dados suportados de cada coluna

typedef struct {
    char name[50];
    DataType type;
} Column;   // Colunas de uma tabela

typedef struct {
    char name[50];               // Nome da tabela
    Column columns[10];         // Colunas da tabela
    int num_columns;           // Número de colunas da tabela
    unsigned int primary_key; // Chave primária da tabela, é o índice da coluna que é a chave primária e ela servira para questões de segurança no futuro
} Table;

#endif //PROJETO_FINAL_ITP_DATABASE_H

// Última atualização 2023-11-25 -- dio