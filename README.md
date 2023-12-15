
# Sistema de Gerenciamento de Dados Relacional Simplificado
***
# Descrição do projeto

Como parte da ementa do curso Introdução as técnicas de programação (ITP) na Universidade Federal do Rio Grande Do Norte (UFRN), este projeto é um Sistema de Gerenciamento de Banco de Dados Relacional (SGBD) simplificado, implementado na linguagem de programação C. O objetivo do projeto é fornecer uma maneira simplificada de criar, manipular e gerenciar tabelas em um banco de dados relacional.

## Características

* O SGBD suporta a criação de várias tabelas, cada uma com um número definido de colunas e linhas.
* Cada tabela pode ter colunas de diferentes tipos de dados, incluindo inteiros, floats, doubles, caracteres e strings.
* As operações suportadas incluem a criação de novas tabelas, adição de linhas a uma tabela, exclusão de tabelas e linhas, e listagem de todas as tabelas no banco de dados.
* O SGBD também suporta a leitura e gravação de bancos de dados a partir de e para arquivos, permitindo a persistência de dados entre as sessões.
* O projeto utiliza uma abordagem modular, com diferentes componentes do SGBD implementados em arquivos separados. Isso facilita a manutenção e a expansão do código.

## Limitações

* Não há suporte para a atualização de linhas em uma tabela.
* Não há suporte para a exclusão de colunas de uma tabela.
* O tamanho máximo do banco de dados é estático com no máximo 10 tabelas, 20 linhas e 10 colunas por tabela.
* As informações armazenadas na tabela também tem um tamanho máximo.
* O banco de dados é apenas local, não há suporte para conexão remota.

## Pré-requisitos
Antes de instalar e executar o SGBD, certifique-se de que seu sistema atende aos seguintes pré-requisitos:

* Sistema Operacional: Windows, Linux ou MacOS.
* Compilador C: GCC para Linux, Clang para MacOS ou MinGW/Clang/Visual Studio para Windows.
* CMake: Ferramenta para controle de compilação do software.

Para instalar o CMake e o compilador apropriado:

* Windows:
    * CMake: Baixe do site oficial do CMake.
    * Compilador: Instale MinGW, Clang ou Visual Studio.

* Linux:
   * CMake: Execute sudo apt-get install cmake.
   * Compilador GCC: Normalmente já vem instalado ou pode ser instalado via gerenciador de pacotes.
  
* MacOS:
  * CMake: Instale via Homebrew com brew install cmake.
  * Clang: Normalmente já vem instalado no MacOS.

***
# Compilando e Rodando pelo terminal

Primeiro de tudo, instale o CMake para seu S.O. e baixe ou clone o repo do projeto.

* **Windows:**
    1. Pré-configuração:
        * Instale o CMake e adicione-o ao PATH do sistema (no instalador há essa opção).
        * Instale o compilador apropriado (MinGW, Clang ou Visual Studio).
    2. Criar e Navegar para o diretório de construção do projeto:
         * Abra o terminal e navegue até a pasta do projeto.
         * Crie um diretório para a construção do projeto: `mkdir build && cd build`
    3. Configure o projeto com CMake:
        * Visual Studio:
          ```
          cmake .. -G "<versao_do_VS>"
          cmake --build . --config Release
          ```
        * MinGW:
          ```
          cmake .. -G "MinGW Makefiles" 
          cmake --build .
          ```
        * Clang:
          ```
          set CC=clang
          cmake .. -G
          ```
  4. Execute o programa (estando na pasta build): `./main.exe`

* **Linux & MacOS (bem mais fácil):**
    1. Instale o CMake :
       Ubuntu ou Debian:
       ```
       sudo apt-get install cmake
       ```
       MacOS:
       ```
       brew install cmake
       ```
    2. Configure, compile e execute:
        * Navegue até a pasta do projeto e execute os comandos:
       ```
       mkdir build && cd build
       cmake ..
       make
       ./main
       ```
    
