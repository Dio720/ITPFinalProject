// Funções auxiliares para leitura segura de dados do usuário
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_UTILS_H
#define PROJETO_FINAL_ITP_UTILS_H

#include <stdio.h>
#include <stdbool.h>

int readInteger();
float readFloat();
double readDouble();
char readChar();
void readString(char *string, int maxLength);
void removeNewLine(char *string);
int calculateStringSimilarity(const char *string1, const char *string2); // Calcula a distância de Levenshtein entre duas strings
char* suggestName(const char *name, const char *names[], int numNames);

#endif // PROJETO_FINAL_ITP_UTILS_H

/** Patch Notes (29/11/2023 -- schwaad):
 * - implementei as funções do utils.c, com exceção da suggestName. coloquei informações mais específicas no comentário dentro da função.
 */

/** Hotfix (30/11/2023 ~ Dio):
 *  * - O uso de atof, atoi e atol é desencorajado, pois não há verificação de erros
 * Essas funções foram substituídas por strtod, strtol e strtoll, que são mais seguras.
 * - Troquei nome das funções e variáveis para inglês.
 * - Além de mudar o nome da levenshtein, re-aproveitei uma versão antiga que eu tinha desse algoritmo.
 * - Adicionei uma função para retornar o minimo entre dois inteiros.
 */

/** Hotfix (01/12/2023):
 * Correções pontuais.
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * - Adicionada a readFloat
 * - Adicionada a readChar
 * - Troca de chamda da readString
 */