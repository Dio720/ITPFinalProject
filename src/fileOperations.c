// Funções relacionadas à manipulação de arquivos
// Created by dio on 25/11/23.
//

#include "fileOperations.h"
#include "utilsFileOperations.h"
#include "database.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Table tables[MAX_TABLES];
extern int numTables;

char* readFileName() {
    char* filename = (char*) malloc(MAX_NAME_LENGTH * sizeof(char));
    if (filename == NULL) {
        printf("Erro ao alocar memória para o nome do arquivo.\n");
        return NULL;
    }

    while (1) {
        printf("Digite o nome do arquivo (ou 'q' para voltar): ");
        readString(filename, MAX_NAME_LENGTH);

        if (strcmp(filename, "q") == 0 || strcmp(filename, "Q") == 0) {
            free(filename);
            return NULL;
        }

        if (isValidFileName(filename)) {
            break;
        } else {
            printf("Nome de arquivo inválido. Tente novamente.\n");
        }
    }

    return filename;
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

    for (int i = 0; i < numTables; i++) {
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

bool loadFile(char* filename) {
    initDatabase();

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro: O arquivo %s não pôde ser aberto. Verifique se o arquivo existe e se você tem permissão para lê-lo.\n", filename);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    if (fsize == 0) {
        printf("Erro: O arquivo %s está vazio.\n", filename);
        fclose(file);
        return false;
    }
    fseek(file, 0, SEEK_SET);

    char *fileContent = malloc(fsize + 1);
    if (fileContent == NULL) {
        printf("Erro: Não foi possível alocar memória para ler o arquivo %s.\n", filename);
        fclose(file);
        return false;
    }

    fread(fileContent, 1, fsize, file);
    fclose(file);

    fileContent[fsize] = '\0';

    processFileContent(fileContent);
    free(fileContent);
    printf("Arquivo %s carregado com sucesso.\n", filename);
    return true;
}


/**
 * Função: readFileName
 * --------------------
 * Solicita ao usuário o nome do arquivo.
 *
 * A função segue os seguintes passos:
 * 1. Aloca memória para armazenar o nome do arquivo.
 * 2. Entra em um loop onde solicita ao usuário que digite o nome do arquivo.
 * 3. Verifica se o usuário quer sair. Se sim, libera a memória alocada para o nome do arquivo e retorna NULL.
 * 4. Verifica se o nome do arquivo é válido. Se for, quebra o loop.
 * 5. Se o nome do arquivo não for válido, imprime uma mensagem de erro e continua o loop.
 *
 * @return: O nome do arquivo, ou NULL se o usuário decidir sair.
 */

/**
 * Função: processFileContent
 * --------------------------
 * Processa o conteúdo de um arquivo.
 *
 * A função segue os seguintes passos:
 * 1. Define a posição atual como o início do conteúdo do arquivo.
 * 2. Entra em um loop onde processa cada tabela no conteúdo do arquivo.
 * 3. Chama a função processTable para processar a tabela atual.
 * 4. Avança a posição atual para a próxima tabela.
 * 5. Continua o loop até que todas as tabelas tenham sido processadas.
 *
 * @param fileContent: O conteúdo do arquivo a ser processado.
 */

/**
 * Função: saveDatabaseToFile
 * --------------------------
 * Salva o banco de dados em um arquivo.
 *
 * A função segue os seguintes passos:
 * 1. Abre o arquivo para escrita.
 * 2. Verifica se o arquivo foi aberto com sucesso. Se não, imprime uma mensagem de erro e retorna false.
 * 3. Percorre cada tabela no banco de dados.
 * 4. Para cada tabela, imprime os detalhes da tabela e os dados de cada coluna e linha no arquivo.
 * 5. Fecha o arquivo.
 * 6. Retorna true para indicar que o banco de dados foi salvo com sucesso.
 *
 * @param filename: O nome do arquivo onde o banco de dados será salvo.
 * @return: Um valor booleano indicando se o banco de dados foi salvo com sucesso.
 */

/**
 * Função: loadFile
 * ----------------
 * Carrega um arquivo para o banco de dados.
 *
 * A função segue os seguintes passos:
 * 1. Inicializa o banco de dados.
 * 2. Abre o arquivo para leitura.
 * 3. Verifica se o arquivo foi aberto com sucesso. Se não, imprime uma mensagem de erro e retorna false.
 * 4. Verifica se o arquivo está vazio. Se sim, imprime uma mensagem de erro e retorna false.
 * 5. Aloca memória para armazenar o conteúdo do arquivo.
 * 6. Lê o conteúdo do arquivo para a memória.
 * 7. Fecha o arquivo.
 * 8. Chama a função processFileContent para processar o conteúdo do arquivo.
 * 9. Libera a memória alocada para o conteúdo do arquivo.
 * 10. Imprime uma mensagem informando que o arquivo foi carregado com sucesso.
 * 11. Retorna true para indicar que o arquivo foi carregado com sucesso.
 *
 * @param filename: O nome do arquivo a ser carregado.
 * @return: Um valor booleano indicando se o arquivo foi carregado com sucesso.
 */

/** Patch Notes (28/11/2023 -- Dio):
 * - Adotei uma nova abordagem para a leitura do arquivo, agora a função readFile() retorna uma string
 * - Adicionei a função processFileContent() para processar o conteúdo da string consequentemente do Arquivo
 */

/** Patch Notes (30/11/2023 -- Dio):
 * - Adicionei a função saveDatabaseToFile() para salvar o banco de dados em um arquivo
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * - Deleção da readFile
 * - Criação da loadFile
 */