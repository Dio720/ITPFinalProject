// Descriçãi Funções auxiliares utéis
// Created by dio on 25/11/23.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// TODO: Implementar todas as funções auxiliares

double readDouble() {
    // Lê em string e converte para Float
    char entrada[50];
    fgets(entrada, 50, stdin);
    float saida = atof(entrada);

    //Retorna a string convertida se der certo
    if(saida != 0){
        return saida;
    }
    //Erro se for do tipo incorreto e chama a função novamente.
    //Nesse caso em específico o print do erro é "tipo float ou double" porque
    //quando for lidar com os dados da tabela dá pra interpretar o float apenas como um double menos preciso.
    else{
        printf("Erro. A entrada precisa ser do tipo float ou double.\n");
        readDouble();
    }
}

// Função que lê um inteiro do usuário
int readInteger() {
    // Lê em string e converte para Int
    char entrada[50];
    fgets(entrada, 50, stdin);
    int saida = atoi(entrada);

    //Retorna a string convertida se der certo
    if(saida != 0){
        return saida;
    }

    //Erro se for do tipo incorreto e chama a função novamente.
    else{
        printf("Erro. A entrada precisa ser do tipo inteiro.\n");
        readInteger();
    }
}

void removeNewLine(char *str){
    size_t strSize = strlen(str);
    //Verifica se o último caractere da string é um newline, caso sim, transforma o newline apenas no fim da string.
    if(strSize > 0 && str[strSize - 1] == '\n'){
        str[strSize - 1] = '\0';
    }
}


//Algoritmo de levenshtein para verificar a similaridade entre duas strings
int levenshtein(const char *str1, const char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);

    int matriz[m + 1][n + 1];

    for (int i = 0; i <= m; ++i) {
        matriz[i][0] = i;
    }

    for (int j = 0; j <= n; ++j) {
        matriz[0][j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int custo = (str1[i-1] != str2[j-1]);
            matriz[i][j] = ((matriz[i-1][j] + 1) < (matriz[i][j-1] + 1)) ?
                           ((matriz[i-1][j] + 1) < (matriz[i-1][j-1] + custo) ?
                            (matriz[i-1][j] + 1) : (matriz[i-1][j-1] + custo)) :
                           ((matriz[i][j-1] + 1) < (matriz[i-1][j-1] + custo) ?
                            (matriz[i][j-1] + 1) : (matriz[i-1][j-1] + custo));
        }
    }

    return matriz[m][n];
}

// Função que sugere um nome existente com menor distância de Levenshtein

char* sugerirNome(const char *nomeErrado, const char **nomesExistentes, int numNomes) {
    /* ATENÇÃO: Precisa de algumas correções que serão feitas depois da implementação das funções de manipulação de arquivos!!

   Aqui vão algumas instruções pra melhor implementação depois:
   - Pra a função funcionar, ela precisa receber o nome inserido, o array de todos os nomes (precisa ser montado) e a quantidade de nomes (precisa ser calculada fora da função). 
   ou seja, num contexto de nome de tabelas, vai ser preciso montar um array com o nome de todas as tabelas pra servir de fonte da comparação. No mesmo momento que montar esse
   array, já calcula o tamanho dele!! Essas coisas podem ser feitas talvez até dentro da função, mas a gente ainda precisa ver quando implementar melhor. Como é qualidade de vida
   apenas, não precisa se preocupar tanto por agora.
   
   mas tipo, a função ta funcionando, eu testei já e tá tudo certo*/

    int melhorDistancia = -1;
    const char *melhorSugestao = NULL;

    for (int i = 0; i < numNomes; ++i) {
        int distancia = levenshtein(nomeErrado, nomesExistentes[i]);

        if (melhorDistancia == -1 || distancia < melhorDistancia) {
            melhorDistancia = distancia;
            melhorSugestao = nomesExistentes[i];
        }
    }

    // Retorna uma cópia da sugestão
    if (melhorSugestao != NULL) {
        char *sugestao = strdup(melhorSugestao);
        return sugestao;
    }

    // Retorna NULL se não houver sugestão
    return NULL;
}

/** Patch Notes (29/11/2023 -- schwaad):
 * - implementei as funções do utils.c, com exceção da sugerirNome. coloquei informações mais específicas no comentário dentro da função.
 */