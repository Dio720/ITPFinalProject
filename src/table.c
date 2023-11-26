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

// TODO: Em algumas funções, se o usuário digitar algo inválido, a função retorna sem fazer nada, talvez seja melhor fazer um loop até que o usuário digite algo válido e uma maneira de sair desse loop

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
    int num_columns = read_integer_from_user();                          // Chama uma função do aux_functions que faz essa leitura de maneira segura
    if (num_columns == INT_MAX || num_columns < 1 || num_columns > 10) { // Como está definida cada tabela pode ter no máximo 10 colunas (INT_MAX é o caso de erro da função que acabou de chamar)
        printf("Número de colunas inválido.\n");
        return;
    }
    table.num_columns = num_columns;    // Atribui o número de colunas à tabela

    // Recebe os detalhes de cada coluna
    for (int i = 0; i < table.num_columns; i++) {
        printf("Digite o nome da coluna %d: \n", i + 1);
        fgets(table.columns[i].name, sizeof(table.columns[i].name), stdin); // fgets porque é mais seguro
        remove_newline(table.columns[i].name);                              // Remove o \n do final da string

        printf("Digite o tipo da coluna %d (0 para INT, 1 para FLOAT, 2 para DOUBLE, 3 para CHAR e 4 para STRING): \n", i + 1); // Remete ao enum criado no database.h
        int type = read_integer_from_user();                // Chama uma função do aux_functions que faz essa leitura de maneira segura
        if (type == INT_MAX || type < 0 || type > 4) {      // Verifica se o número se encaixa no enum (INT_MAX, caso de erro)
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

    tables[num_tables++] = table; // Adiciona a tabela criada ao vetor de tabelas

    save_tables_to_file(filename); // Salva as tabelas no arquivo
}

// Função para listar as tabelas do banco de dados
void list_tables(const char *filename) {
    printf("# Tabelas de %s:\n", filename);
    for (int i = 0; i < num_tables; i++)
        printf("  · Tabela %d: %s\n", i + 1, tables[i].name);   // Imprime o nome de cada tabela
}

// Função para deletar uma tabela
void delete_table(const char *filename) {
    int min_distance = INT_MAX; // Distância mínima entre o nome da tabela e o nome de uma tabela existente, INT_MAX pq é o maior valor possível para um int
    int closest_tables[3];      // Supondo um máximo de 3 tabelas próximas
    int num_closest = 0;        // Número de tabelas próximas
    int choice;            // Armazena indice da tabela escolhida pelo usuário
    char table_name[50];        // Nome da tabela a ser deletada

    // Recebe a entrada:
    printf("Digite o nome da tabela que deseja deletar: ");
    fgets(table_name, sizeof(table_name), stdin);           // fgets por segurança
    remove_newline(table_name);                             // Remove o \n do final da string

    for (int i = 0; i < num_tables; i++) {                               // Para cada tabela:
        int distance = levenshtein_distance(table_name, tables[i].name); // 1. Calcula-se a distância de Levenshtein entre o nome da tabela e o nome da tabela atual
        if (distance < min_distance) {                                   // 2. Se a distância for menor que a distância mínima:
            min_distance = distance;                                     //     * A distância mínima é atualizada
            num_closest = 0;                                             //     * O número de tabelas próximas é resetado
            closest_tables[num_closest++] = i;                           //     * A tabela atual é adicionada ao vetor de tabelas próximas
        } else if (distance == min_distance) {                           // 3. Se a distância for igual à distância mínima:
            closest_tables[num_closest++] = i;                           //     * A tabela atual é adicionada ao vetor de tabelas próximas
        }
    }

    if (num_closest == 0) { // Se não houver nenhuma tabela próxima
        printf("Tabela não encontrada.\n");
        return;
    }

    if (min_distance != 0) {    // Se a distância mínima for diferente de 0, ou seja, se não houver correspondência exata
        printf("Você não quis dizer uma dessas?\n");
        for (int i = 0; i < num_closest; i++) {                             // Para cada tabela próxima:
            printf(" · %d: %s\n", i + 1, tables[closest_tables[i]].name);   // Imprime os nomes mais parecidos com o digitado pelo usuário
        }
        printf("Digite o número da tabela que deseja deletar: ");
        choice = read_integer_from_user();
        if (choice < 1 || choice > num_closest) {       // Se a escolha do usuário for inválida
            printf("Operação cancelada.\n");
            return;
        }

        choice = closest_tables[choice - 1];    // Ajuste o índice para a escolha do usuário
    } else {
        choice = closest_tables[0];             // Caso de correspondência exata
    }

    // Removendo a tabela escolhida
    for (int i = choice; i < num_tables - 1; i++) { // A partir da tabela escolhida, move todas as tabelas uma posição para trás
        tables[i] = tables[i + 1];                  // A tabela atual recebe a próxima tabela
    }
    num_tables--;       // Diminui o número de tabelas

    save_tables_to_file(filename);     // Salva o novo estado no arquivo
}


// Última modificação 2023-11-26 -- dio