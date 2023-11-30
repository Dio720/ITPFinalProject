// Funções relacionadas à manipulação de arquivos
// Created by dio on 25/11/23.
//

#include "file_operations.h"
#include "utils_file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Table tables[10];
extern int num_tables;

// TODO: Escrever Funções para salvar o arquivo
// TODO: Escrever Funções para criar o arquivo

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

/**
 * Função: readFile
 * -----------------
 * Lê o conteúdo de um arquivo e retorna esse conteúdo como uma string.
 *
 * @param filename: O nome do arquivo a ser lido.
 *
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

/** Patch Notes (28/11/2023 -- Dio):
 * - Adotei uma nova abordagem para a leitura do arquivo, agora a função readFile() retorna uma string
 * - Adicionei a função processFileContent() para processar o conteúdo da string consequentemente do Arquivo
 */