// Main Function
// Created by dio on 28/11/23.
//
#include <stdio.h>
#include <stdlib.h>

//Diferentes comandos para limpar o terminal em diferentes SOs
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int menu(int entrada){
    printf("-------------------------------------------\n");
    printf("                SGDB ITP\n");
    printf("-------------------------------------------\n");
    printf("1 - Criar Tabela\n2 - Deletar Tabela\n3 - Criar Linha\n4 - Listar Tabelas\n5 - Listar Dados\n6 - Deletar Linha\n7 - Procurar Linha\n0 - Sair\n");
    printf("-------------------------------------------\n");
    scanf("%d", &entrada);
    return entrada;
}



int main (){
    int entrada = 1;

    while(entrada){
        entrada = menu(entrada);
            //Quando implementar as funções, adicionar elas aqui.
            switch(entrada){
                case 0:
                    limparTela();
                    return 0;
                case 1:
                    limparTela();
                    break;
                case 2:
                    limparTela();
                    break;
                case 3:
                    limparTela();
                    break;
                case 4:
                    limparTela();
                    break;
                case 5:
                    limparTela();
                    break;
                case 6:
                    limparTela();
                    break;
                case 7:
                    limparTela();
                    break;
                }
        }
    return 0;
}
/** Patch Notes (29/11/2023 -- schwaad):
 * - criei a função menu() que mostra uma interfacezinha pra executar todos os comandos. tem um comentáriozinho dentro do while
 *   que fala sobre colocar as funções em cada um dos casos depois de implementadas;
 * 
 * - criei uma funçãozinha limparTela que é só pra executar comandos diferentes dependendo do SO da user.
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