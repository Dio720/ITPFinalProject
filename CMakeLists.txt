cmake_minimum_required(VERSION 3.26)    # Versão mínima do CMake
project(Projeto_final_ITP C)            # Define o nome do projeto

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)     # Define a versão do C

include_directories(headers_files)      # Adiciona o diretório de headers_files

add_library(Projeto_final_ITP
        src/table.c
        src/data.c
        src/file_operations.c
        src/aux_functions.c
        headers_files/aux_functions.h)          # Adiciona a biblioteca

add_executable(main src/database.c)             # Adiciona o executável
target_link_libraries(main Projeto_final_ITP)   # Adiciona a biblioteca ao executável