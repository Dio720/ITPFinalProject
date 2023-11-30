// Funções à manipulação de dados dentro das tabelas
// Created by dio on 25/11/23.
// Ainda não sei o que vai precisar pra cada função, na dúvida tudo

#include "data.h"


void createRow() {
    /* Implementação de função que cria uma nova linha na tabela:
     * 1. Recebe o nome da tabela
     * 2. Recebe os valores de cada uma das colunas
     * 3. Verifica se os valores são válidos
     * 4. Verifica se a linha já existe
     * 6. Verificar a chave primária
     * * 6.1 Em uma tabela deve existir um único valor para a chave primária, se o
     * usuário tentar inserir um valor que já existe, deve retornar um erro
     */
}

void listData() {
    /* Implementação de função que lista os dados de uma tabela em formato CSV:
     * 1. Recebe o nome da tabela
     * 2. Verifica se a tabela existe
     * 3. Devem ser obtidos do arquivo que armazena (a gente ja tem um coisa que
     * inicializa e lê os dados)
     * 4. Lista os dados da tabela em formato CSV (mais bonitinho)
     */
}

void delete_data() {
    /* Implementação de função que deleta uma linha (registro, tupla, meu cu, so
     * nome feio) da tabela:
     * 1. Recebe o nome da tabela
     * 2. Recebe o valor da chave primária da linha que deve ser deletada
     */
}

void searchData() {
    /* Implementação de função que procura por uma linha na tabela:
     * 1. Recebe o nome da tabela
     * 2. Sistema deve fornecer as colunas disponíveis para busca
     * 3. Recebe o nome da coluna que deve ser buscada
     * 3. Não entendi muito bem o que ele quer aqui, mas ele pede umas informações
     * extras
     */
}

/** Patch Notes (28/11/2023 -- Dio):
 * - Troquei a formatação de snake_case para camelCase
 */