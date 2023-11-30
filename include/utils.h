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
int levenshteinDistance(const char *string1, const char *string2); // Calcula a distância de Levenshtein entre duas strings

#endif // PROJETO_FINAL_ITP_UTILS_H

// úlitma atualização 2023-11-26 -- dio