// Funções relacionadas à manipulação de arquivos
// Created by dio on 25/11/23.
//

#include "fileOperations.h"
#include "utilsFileOperations.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Table tables[10];
extern int numTables;

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fsize == 0) {
        fprintf(stderr, "Arquivo vazio\n");
        fclose(file);
        return NULL;
    }

    char *string = malloc(fsize + 1);
    if (!string) {
        fprintf(stderr, "Falha ao alocar memória\n");
        fclose(file);
        return NULL;
    }

    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = '\0';
    return string;
}

void processFileContent(char *fileContent) {
    char *currentPosition = fileContent;
    char *nextTablePosition;

    while (currentPosition != NULL && *currentPosition != '\0') {
        nextTablePosition = processTable(currentPosition);

        if (nextTablePosition == NULL)
            return;

        while (*nextTablePosition == '\n')
            nextTablePosition++;

        currentPosition = nextTablePosition;
    }
}

bool saveDatabaseToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return false;
    }

    for (int i = 0; i < MAX_TABLES; i++) {
        Table *table = &tables[i];
        if (strlen(table->name) == 0) continue;

        fprintf(file, "Tabela %d: \"%s\", Quantidade de colunas: %d, Quantidade de linhas: %d\n", i + 1, table->name, table->numColumns, table->numRows);

        for (int j = 0; j < table->numColumns; j++) {
            fprintf(file, "Coluna %d: \"%s\", Tipo: %d\n", j + 1, table->columns[j].name, table->columns[j].type);
        }

        for (int j = 0; j < table->numRows; j++) {
            fprintf(file, "Linha %d: ", j + 1);
            for (int k = 0; k < table->numColumns; k++) {
                Cell *cell = &table->rows[j].cells[k];
                switch (cell->type) {
                    case INT:
                        fprintf(file, "\"%d\"", cell->value.intValue);
                        break;
                    case FLOAT:
                        fprintf(file, "\"%.2f\"", cell->value.floatValue);
                        break;
                    case DOUBLE:
                        fprintf(file, "\"%.2lf\"", cell->value.doubleValue);
                        break;
                    case CHAR:
                        fprintf(file, "\"%c\"", cell->value.charValue);
                        break;
                    case STRING:
                        fprintf(file, "\"%s\"", cell->value.stringValue);
                        break;
                    default:
                        fprintf(file, "\"\"");
                }
                if (k < table->numColumns - 1) fprintf(file, ", ");
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return true;
}

/**
 * Função: readFile
 * -----------------
 * Lê o conteúdo de um arquivo e retorna esse conteúdo como uma string.
 *
 * @param filename: O nome do arquivo a ser lido.
 *Arquivo de testes para file_operations.c
 * @return: Uma string contendo o conteúdo do arquivo. Se ocorrer um erro ao
 * abrir o arquivo ou alocar memória para a string, a função retorna NULL e
 * imprime uma mensagem de erro na saída de erro padrão.
 *
 * O processo de leitura do arquivo é o seguinte:
 * 1. Abre o arquivo no modo de leitura.
 * 2. Se o arquivo não puder ser aberto, imprime uma mensagem de erro e retorna
 * NULL.
 * 3. Move o ponteiro de arquivo para o final do arquivo para determinar o
 * tamanho do arquivo.
 * 4. Aloca memória para uma string que pode conter o conteúdo do arquivo.
 * 5. Se a memória não puder ser alocada, imprime uma mensagem de erro, fecha o
 * arquivo e retorna NULL.
 * 6. Move o ponteiro de arquivo de volta para o início do arquivo.
 * 7. Lê o conteúdo do arquivo para a string.
 * 8. Fecha o arquivo.
 * 9. Adiciona um caractere nulo ao final da string para garantir que ela seja
 * uma string válida em C.
 * 10. Retorna a string.
 */

/**
 * Função: processFileContent
 * ---------------------------
 * Processa o conteúdo de um arquivo que foi lido para uma string.
 *
 * A função segue os seguintes passos:
 * 1. Define a posição atual como o início da string.
 * 2. Enquanto a posição atual não for nula e não for o final da string:
 *    - Chama a função processTable com a posição atual para processar a tabela
 * atual.
 *    - Se a função processTable retornar NULL, retorna da função
 * processFileContent.
 *    - Avança a posição atual para a próxima tabela na string.
 * 3. Continua esse processo até que todas as tabelas na string tenham sido
 * processadas.
 *
 * @param fileContent: A string contendo o conteúdo do arquivo a ser processado.
 * @return: void
 */

/**
 * Função: saveDatabaseToFile
 * ---------------------------
 * Salva o banco de dados atual em um arquivo.
 *
 * @param filename: O nome do arquivo onde o banco de dados será salvo.
 * @return: Um valor booleano indicando se a operação foi bem-sucedida. Retorna
 * true se o banco de dados foi salvo com sucesso e false se ocorreu um erro ao
 * abrir o arquivo para escrita.
 *
 * A função segue os seguintes passos:
 * 1. Abre o arquivo no modo de escrita.
 * 2. Se o arquivo não puder ser aberto, imprime uma mensagem de erro e retorna
 * false.
 * 3. Para cada tabela no banco de dados:
 *    - Se o nome da tabela estiver vazio, pula a tabela.
 *    - Escreve os detalhes da tabela no arquivo, incluindo o nome da tabela, o
 * número de colunas e o número de linhas.
 *    - Para cada coluna na tabela, escreve os detalhes da coluna no arquivo,
 * incluindo o nome da coluna e o tipo de dados.
 *    - Para cada linha na tabela, escreve os valores das células no arquivo.
 * 4. Fecha o arquivo.
 * 5. Retorna true para indicar que o banco de dados foi salvo com sucesso.
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Adotei uma nova abordagem para a leitura do arquivo, agora a função readFile() retorna uma string
 * - Adicionei a função processFileContent() para processar o conteúdo da string consequentemente do Arquivo
 */

/** Patch Notes (30/11/2023 -- Dio):
 * - Adicionei a função saveDatabaseToFile() para salvar o banco de dados em um arquivo
 */