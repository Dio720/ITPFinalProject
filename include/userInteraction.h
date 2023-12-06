// Interação com o usuário
// Created by dio on 02/12/23.
//

#ifndef ITPFINALPROJECT_USERINTERACTION_H
#define ITPFINALPROJECT_USERINTERACTION_H

#include "database.h"

Table getNewTableData();
void deleteTableUserInteraction();
void createRowUserInteraction();
Row getNewRowData(char* tableName);
void deleteRowUserInteraction();
void listTableDataUserInteraction();

#endif //ITPFINALPROJECT_USERINTERACTION_H

/** Patch Notes (03/12/2023 ~ Dio):
 * Criação do arquivo e todas as susas funções
 */