<<<<<<< HEAD
# Patch Notes (30/11/2023 ~ Dio)

=======
# Patch Notes (29/11/2023 ~ schwaad)
# Mudanças gerais:
* Mudei o nome da delete_data() do data.c pra `camelCase`

# Mudanças no código:
* Implementei as funções do utils.c
* Coloquei uma interfacezinha pra executar os comandos na main.c
* Mais informações nos comentários dos arquivos!!

# Patch Notes (28/11/2023 ~ Dio)
>>>>>>> Zeivo
## Mudanças Gerais:

* Adicionado testes para o processo de carregar e salvar um banco de dados de um arquivo.
* Modularização das funções de testes em suites e arquivos diferentes.
* Adicionado o arquivo `createTestFiles.c` para gerar arquivos de teste.
* Adicionado o arquivo `testFileOperations.c / tesFileOperations.h` para testar as operações de arquivo.
* Atualizei o `CMake` e o deixei mais organizado.
* Correção de bugs e melhorias no código.

### Mudanças no código:

* #### `testFileOperations.h / testFileOperations.c`:
  * Adicionado as funções `testReadFile()`, `testProcessFileContentWithKnownContent()`, `testSaveDatabaseToFile()`.

* #### `createTestFiles.c`:
    * Adicionado a função `generateValidTestFile()` para gerar arquivos de teste válidos.
    * Adicionado a função `generateRandomString()` para gerar strings aleatórias para os testes.
    * Nenhuma das duas funciona como deveria!
  
* #### `src/fileOperations.c`:
  * Adicionado a função `saveDatabaseToFile()` para salvar o banco de dados em um arquivo.

### Mudanças no `CMake`:

* Uso de GLOB para adicionar todos os arquivos `.c` e `.h` do diretório `src` e `unitTests` automaticamente.
* Adicionados diretórios de inclusão para `include` e `unitTests/includeTests`.
* Especificados os arquivos fonte para a biblioteca `mylib` e `testlib`.

### TODOs:

* [ ] Implementar um melhor tratamento de erros nas funções relacionadas ao processamento de arquivo.
* [x] Criar novas funções para manipular arquivos, como `saveFile`, `createFile`.
* [ ] Criar as funções de manipulação de tabela.
* [ ] Criar as funções de manipulação de linha e de células.
* [ ] Levar em consideração a informação armazenada na coluna ID ao processar o arquivo.
* [ ] Estruturar uma interface na `main.c` para o usuário.


# Patch Notes (29/11/2023 ~ schwaad)
## Mudanças gerais:
* Mudei o nome da delete_data() do data.c pra `camelCase`

### Mudanças no código:
* Implementei as funções do utils.c
* Coloquei uma interfacezinha pra executar os comandos na main.c
* Mais informações nos comentários dos arquivos!!


# Patch Notes (28/11/2023 ~ Dio)

## Mudanças Gerais:

* Adicionado o sistema de patch notes.
* Mudei o nome do diretório `headers_files` para `include`.
* Mudei o nome de `aux_functions.c / aux_functions.h` para `utils.c / utils.h`.
* Criada a `utils_file_operations.c / utils_file_operations.h`.
* Troca da formatação geral do código de `snake_case` para `camelCase`.
* Reformulação do sistema de manipular arquivos e funções auxiliares a isso.
* Reformulação da documentação e comentários do código.
* Reformulação da estrutura de dados.
* Adoção do uso de bibliotecas de testes unitários `CUnit`, além de seu executável e `.c`.
* Criação de um arquivo de configuração mais organizado para o `CMake`.

### Mudanças no código:

* #### `database.c / database.h`:
    * Criação da `initDatabase`.
    * Criação da `initCellAsEmpty`.
* #### `file_operations.c / file_operations.h`:
    * Adotada uma nova abordagem para ler o arquivo e carregar no sistema.
    * Criação da `readFile`.
    * Criação da `processFileContent`.
* #### `utils_file_operations.c / utils_file_operations.h`:
    * Programa criado para auxiliar as operações de arquivos em `file_operations.c`.
    * Criação da`convertStringToCell` para processar o valor de uma célula da linha.
    * Criação da `processRows`.
    * Criação da `processColumns`.
    * Criação da `processTable`.
* #### `table.c / table.h`:
    * Descartada a versão anterior do código para estudar melhor implementação.
* #### `utils.c / utils.h`:
    * Descartada a versão anterior do código para estudar melhor implementação.

### Mudanças no `CMake`:

* Melhor organização da configuração do `CMake`.
* Criação da biblioteca `mylib`.
* Criação do executável `main`.
* Criação do executável `tests`.

### TODOs:

* [ ] Implementar um melhor tratamento de erros nas funções relacionadas ao processamento de arquivo.
* [ ] Criar novas funções para manipular arquivos, como `saveFile`, `createFile`.
* [ ] Criar as funções de manipulação de tabela.
* [ ] Criar as funções de manipulação de linha e de células.
* [ ] Levar em consideração a informação armazenada na coluna ID ao processar o arquivo.
* [ ] Estruturar uma interface na `main.c` para o usuário.

