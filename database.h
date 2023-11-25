//
// Created by dio on 24/11/23.
//

#ifndef PROJETO_FINAL_ITP_DATABASE_H
#define PROJETO_FINAL_ITP_DATABASE_H

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} DataType;

typedef struct {
    char name[50];
    DataType type;
} Column;

typedef struct {
    char name[50];
    Column columns[10];
    int num_columns;
    unsigned int primary_key;
} Table;

void create_table();
void list_tables();
void create_row();
void list_data();
void search_value();
void delete_row();
void delete_table();

#endif //PROJETO_FINAL_ITP_DATABASE_H