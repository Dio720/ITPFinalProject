# Especifica a versão mínima do CMake necessária para compilar este projeto.
cmake_minimum_required(VERSION 3.26)

# Define o nome do projeto e a linguagem de programação usada.
project(ITPFinalProject C)

# Define o padrão da linguagem C a ser usado para compilar os arquivos de origem.
set(CMAKE_C_STANDARD 11)

# Cria uma biblioteca chamada 'mylib' com os arquivos de origem especificados.
add_library(mylib
        src/file_operations.c
        src/database.c
        src/utils_file_operations.c
        src/data.c
        src/table.c
        src/utils.c
)

# Adiciona o diretório 'include' ao caminho de inclusão para a biblioteca 'mylib'.
target_include_directories(mylib PUBLIC include)

# Cria um executável chamado 'main' com o arquivo de origem especificado.
add_executable(main src/main.c)

# Vincula a biblioteca 'mylib' ao executável 'main'.
target_link_libraries(main mylib)

# Cria um executável chamado 'tests' com o arquivo de origem especificado.
add_executable(tests src/tests.c)

# Vincula as bibliotecas 'mylib' e 'cunit' ao executável 'tests'.
target_link_libraries(tests mylib cunit)