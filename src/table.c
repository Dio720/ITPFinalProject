// Descrição: Arquivo responsável por implementar as funções de manipulação de tabelas
// Created by dio on 25/11/23.
//

#include "database.h"

extern Table tables[10];
extern int numTables;

// TODO: createTable() e listTables() são funções que devem ser implementadas

Table createTable(const char *filename) {
    // Assim ou void?
}

void listTables(const char *filename) {
    // Função para listar tabelas direto do arquivo? ou carregar o arquivo primeiro?
}

void deleteTable(const char *filename) {
    // Função para deletar uma tabela do arquivo? ou carregar ele primeiro?
}

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 * - Apaguei a versão anterior para poder recomeçar de maneira melhor
 */
