// Funções auxiliares para leitura segura de dados do usuário
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_AUX_FUNCTIONS_H
#define PROJETO_FINAL_ITP_AUX_FUNCTIONS_H

#include <stdio.h>

int read_integer_from_user();                                       // Lê um inteiro do usuário
float read_float_from_user();                                       // Lê um float do usuário
double read_double_from_user();                                     // Lê um double do usuário
void remove_newline(char *str);                                     // Remove o \n do final de uma string
int levenshtein_distance(const char *string1, const char *string2); // Calcula a distância de Levenshtein entre duas strings
int min(int a, int b);                                              // Retorna o menor valor entre dois inteiros
// Levenshtein distance algorithm mede a quantidade mínima de operações de edições para transformar um sequência de caracteres em outra

#endif //PROJETO_FINAL_ITP_AUX_FUNCTIONS_H

// úlitma atualização 2023-11-26 -- dio