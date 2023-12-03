// Funções auxiliares para leitura segura de dados do usuário
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_UTILS_H
#define PROJETO_FINAL_ITP_UTILS_H

#include <stdio.h>

int readInteger();                                                 // Lê um inteiro do usuário
float readFloat();                                                 // Lê um float do usuário
double readDouble();                                               // Lê um double do usuário
void removeNewline(char *str);                                     // Remove o \n do final de uma string
char* sugerirNome(const char *nomeErrado, const char **nomesExistentes, int numNomes); // Calcula a distância de Levenshtein entre duas strings e sugere um nome

#endif // PROJETO_FINAL_ITP_UTILS_H

// úlitma atualização 2023-11-30 -- schwaad
/*
*  - só fiz mudar a "levenshteinDistance" pra "sugerirNome" que foram as alterações feitas no utils.c
*/