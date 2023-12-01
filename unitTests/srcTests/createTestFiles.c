// Funções que geram arquivos de teste:
// Created by dio on 30/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/database.h"

// TODO: Refazer! TA UMA BOSTA!

char *generateRandomString(int maxLength) {
    int length = rand() % (maxLength + 1); // Gera um comprimento aleatório até maxLength
    char *string = malloc((length + 1) * sizeof(char));
    char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    if (string == NULL) {
        printf("Erro ao alocar memória para a string.\n");
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        string[i] = characters[rand() % (sizeof(characters) - 1)];
    }

    string[length] = '\0';
    return string;
}

bool generateValidTestFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return false;
    }

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    for (int i = 0; i < MAX_TABLES; i++) {
        fprintf(file, "Tabela %d: \"%s\", Quantidade de colunas: %d, Quantidade de linhas: %d\n",
                i + 1, generateRandomString(MAX_NAME_LENGTH - 1), MAX_COLUMNS, MAX_ROWS);

        for (int j = 0; j < MAX_COLUMNS; j++) {
            fprintf(file, "Coluna %d: \"%s\", Tipo: %d\n", j + 1, generateRandomString(MAX_NAME_LENGTH - 1), rand() % 6);
        }

        for (int k = 0; k < MAX_ROWS; k++) {
            fprintf(file, "Linha %d:", k + 1);
            for (int l = 0; l < MAX_COLUMNS; l++) {
                switch (rand() % 6) {
                    case INT:
                        fprintf(file, " \"%d\",", rand());
                        break;
                    case FLOAT:
                        fprintf(file, " \"%f\",", (float) rand() / (float) RAND_MAX);
                        break;
                    case DOUBLE:
                        fprintf(file, " \"%lf\",", (double) rand() / (double) RAND_MAX);
                        break;
                    case CHAR:
                        fprintf(file, " \"%c\",", 'a' + (rand() % 26));
                        break;
                    case STRING:
                        char *randomString = generateRandomString(100);
                        fprintf(file, " \"%s\",", randomString);
                        free(randomString);
                        break;
                    case EMPTY:
                        fprintf(file, " \"\",");
                        break;
                }
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    return true;
}

int main() {
    if (!generateValidTestFile("cmake-build-debug/testFiles/validTestFile.txt")) {
        printf("Erro ao gerar o arquivo de teste válido.\n");
        return 1;
    } else printf("Arquivo de teste válido gerado com sucesso.\n");

    return 0;
}

/** Patch Notes (29/11/2023 ~ Dio):
 * - Criei essa bomba aqui de arquivo
 * - Ainda não sei se vai funcionar
 * - Mas tem potencial
 */