// Main Function
// Created by dio on 28/11/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "database.h"
#include "userInteraction.h"
#include "table.h"
#include "fileOperations.h"

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseProgram() {
    printf("Pressione qualquer tecla para continuar...");
    getchar();
}

void initialMenu() {
    printf("1 - Carregar arquivo\n");
    printf("2 - Criar novo banco de dados\n");
    printf("0 - Sair\n");
}

int mainMenu() {
    printf("-------------------------------------------\n");
    printf("                SGDB ITP\n");
    printf("-------------------------------------------\n");
    printf("1 - Criar Tabela\n"
           "2 - Deletar Tabela\n"
           "3 - Criar Linha\n"
           "4 - Listar Tabelas\n"
           "5 - Listar Dados\n"
           "6 - Deletar Linha\n"
           "7 - Procurar Linha\n"
           "8 - Salvar Banco de Dados\n"
           "0 - Sair\n");
    printf("-------------------------------------------\n");
    printf("Digite um número correspondente a função desejada: ");
    int input = readInteger();

    return input;
}

int main() {

    while (1) {
        start:
        clearTerminal();
        printf("Bem-vindo ao nosso SGDB!\n");
        initialMenu();
        int choice = readInteger();

        switch (choice) {
            case 1:
                while (1) {
                    char* filename = readFileName();
                    if (filename == NULL) {
                        goto start;
                    }
                    if (loadFile(filename)) {
                        free(filename);
                        break;
                    } else {
                        free(filename);
                        printf("Deseja tentar novamente? (s/n): ");
                        char retry = readChar();
                        if (retry == 'n' || retry == 'N') {
                            return 0;
                        }
                    }
                }
                break;
            case 2:
                // Inicialize o banco de dados
                initDatabase();
                break;
            case 0:
                // Saia do programa
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        // Se chegamos aqui, o banco de dados foi inicializado ou um arquivo foi carregado
        // Podemos agora entrar no menu principal
        while (1) {
            clearTerminal();
            int input = mainMenu();
            switch (input) {
                case 1:
                    createTable();
                    pauseProgram();
                    break;
                case 2:
                    deleteTableUserInteraction();
                    pauseProgram();
                    break;
                case 3:
                   createRowUserInteraction();
                   pauseProgram();
                    break;
                case 4:
                    listTables();
                    pauseProgram();
                    break;
                case 5:
                    listTableDataUserInteraction();
                    pauseProgram();
                    break;
                case 6:
                    deleteRowUserInteraction();
                    pauseProgram();
                    break;
                case 7:
                    searchValue();
                    break;
                case 8: {
                    char* filename = readFileName();
                    if (filename == NULL) {
                        // O usuário decidiu sair
                        break;
                    }
                    saveDatabaseToFile(filename);
                    free(filename);
                    pauseProgram();
                    break;
                }
                case 0:
                    // Saia do programa
                    return 0;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        }
    }
}

/**
 * Função: clearTerminal
 * ---------------------
 * Limpa o terminal.
 *
 * A função verifica o sistema operacional em que está sendo executada e, com base nisso, executa o comando apropriado para limpar o terminal.
 * No Windows, o comando é "cls", enquanto em outros sistemas operacionais (como Linux e MacOS), o comando é "clear".
 */

/**
 * Função: pauseProgram
 * --------------------
 * Pausa a execução do programa até que o usuário pressione Enter.
 *
 * A função imprime uma mensagem solicitando ao usuário que pressione Enter para continuar e, em seguida, lê um caractere do input do usuário.
 */

/**
 * Função: initialMenu
 * -------------------
 * Exibe o menu inicial do programa.
 *
 * A função imprime as opções do menu inicial, que permitem ao usuário carregar um arquivo, criar um novo banco de dados ou sair do programa.
 */

/**
 * Função: mainMenu
 * ----------------
 * Solicita ao usuário que escolha uma opção do menu principal.
 *
 * A função imprime as opções do menu principal, que permitem ao usuário realizar várias operações no banco de dados, como criar uma tabela, deletar uma tabela, criar uma linha, listar tabelas, listar dados, deletar uma linha, procurar uma linha, salvar o banco de dados ou sair do programa.
 * Em seguida, lê um número inteiro do input do usuário e retorna esse número.
 *
 * @return: O número da opção escolhida pelo usuário.
 */

/**
 * Função: main
 * ------------
 * A função principal do programa.
 *
 * A função entra em um loop infinito onde exibe o menu inicial e solicita ao usuário que escolha uma opção. Dependendo da opção escolhida, a função realiza várias operações, como carregar um arquivo, criar um novo banco de dados ou sair do programa.
 * Se o usuário escolher carregar um arquivo ou criar um novo banco de dados, a função entra em um segundo loop infinito onde exibe o menu principal e solicita ao usuário que escolha uma opção. Dependendo da opção escolhida, a função realiza várias operações no banco de dados, como criar uma tabela, deletar uma tabela, criar uma linha, listar tabelas, listar dados, deletar uma linha, procurar uma linha ou salvar o banco de dados.
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

/** Patch Notes (03/12/2023 ~ Dio):
 *
 */