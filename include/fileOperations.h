// Funções relacionadas a manipulação de arquivos
// Created by dio on 25/11/23.
//

#ifndef PROJETO_FINAL_ITP_FILE_OPERATIONS_H
#define PROJETO_FINAL_ITP_FILE_OPERATIONS_H

#include <stdbool.h>
#include "database.h"

char* readFileName();
void processFileContent(char *fileContent);     // Função para processar o conteúdo da string
bool saveDatabaseToFile(const char *filename);
bool loadFile(char *filename);


#endif // PROJETO_FINAL_ITP_FILE_OPERATIONS_H

/** Patch Notes (28/11/2023 -- Dio):
 * - Adotei uma nova abordagem para a leitura do arquivo, agora a função readFile() retorna uma string
 * - Adicionei a função processFileContent() para processar o conteúdo da string consequentemente do Arquivo
 */

/** Patch Notes (29/11/2023 -- Dio):
 * - Adicionei a função saveDatabaseToFile() para salvar o banco de dados em um arquivo
 */

/** Patch Notes (03/12/2023 ~ Dio):
 * - Deleção da readFile
 * - Criação da loadFile
 */