# ITPFinalProject
***

# Compilando e Rodando pelo terminal

Primeiro de tudo, instale o CMake para seu S.O. e baixe ou clone o repo do projeto.

* **Windows:**
    1. Baixe-o pelo site oficial do CMake: https://cmake.org/download/
       * Instale o CMake e adicione-o ao PATH do Windows.
    2. Precisa de um desses compiladores MinGW, Clang ou Visual Studio instalados e configurados no computador.
    3. Na pasta do projeto, crie um diretório para a construção do projeto: `mkdir build && cd build`
    4. Navegue até onde o CMakeLists.txt está e execute o CMake para configurar o projeto:
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
    5. Execute o programa (estando na pasta do executavel): `main` ou `.\main.exe`

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
       ```
       mkdir build && cd build
       cmake ..
       make
       ./main
       ```
    
