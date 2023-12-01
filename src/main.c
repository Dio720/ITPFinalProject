// Main Function
// Created by dio on 28/11/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int menu() {
    printf("-------------------------------------------\n");
    printf("                SGDB ITP\n");
    printf("-------------------------------------------\n");
    printf("1 - Criar Tabela\n2 - Deletar Tabela\n3 - Criar Linha\n4 - Listar Tabelas\n5 - Listar Dados\n6 - Deletar Linha\n7 - Procurar Linha\n0 - Sair\n");
    printf("-------------------------------------------\n");
    int input = readInteger();

    return input;
}



/* int main (){
    int input = 1;

    while(input){
        input = menu(input);
            //Quando implementar as funções, adicionar elas aqui.
            switch(input){
                case 0:
                    clearTerminal();
                    return 0;
                case 1:
                    clearTerminal();
                    break;
                case 2:
                    clearTerminal();
                    break;
                case 3:
                    clearTerminal();
                    break;
                case 4:
                    clearTerminal();
                    break;
                case 5:
                    clearTerminal();
                    break;
                case 6:
                    clearTerminal();
                    break;
                case 7:
                    clearTerminal();
                    break;
                }
        }
    return 0;
} */

/**
 * Função: clearTerminal
 * ---------------------
 * Limpa o terminal.
 *
 * A função verifica o sistema operacional em que está sendo executada e, com base nisso, executa o comando apropriado para limpar o terminal.
 * No Windows, o comando é "cls", enquanto em outros sistemas operacionais (como Linux e MacOS), o comando é "clear".
 */

/** Patch Notes (29/11/2023 -- schwaad):
 * - criei a função menu() que mostra uma interfacezinha pra executar todos os comandos. tem um comentáriozinho dentro do while
 *   que fala sobre colocar as funções em cada um dos casos depois de implementadas;
 * 
 * - criei uma funçãozinha clearTerminal que é só pra executar comandos diferentes dependendo do SO da user.
 * 
 * - o menu fica assim:
 *      -------------------------------------------
 *                      SGDB ITP
 *      -------------------------------------------
 *       1 - Criar Tabela
 *       2 - Deletar Tabela
 *       3 - Criar Linha
 *       4 - Listar Tabelas
 *       5 - Listar Dados
 *       6 - Deletar Linha
 *       7 - Procurar Linha
 *       0 - Sair
 *      -------------------------------------------   
*/

/** Hotfix (30/11/2023 ~ Dio):
 * - Troquei o nome da função limparTela para clearTerminal
 * - Coloquei a readInteger na função menu para receber o input do usuário.
 * - Troquei a chamada da função menu.
 */