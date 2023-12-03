cmake_minimum_required(VERSION 3.26)

project(ITPFinalProject C)

set(CMAKE_C_STANDARD 11)

# Incluindo os diretórios de cabeçalho
include_directories(include)
include_directories(unitTests/includeTests)

# Especificando os arquivos fonte para mylib
file(GLOB_RECURSE MYLIB_SOURCES "src/*.c" "include/*.h")
add_library(mylib ${MYLIB_SOURCES})

# Especificando os arquivos fonte para testlib
file(GLOB_RECURSE TESTLIB_SOURCES "unitTests/srcTests/*.c" "unitTests/includeTests/*.h")
add_library(testlib ${TESTLIB_SOURCES})

# Criando o executável principal
add_executable(main src/main.c)
target_link_libraries(main mylib)

# Criando o executável de testes
add_executable(tests unitTests/tests.c)

target_link_libraries(tests testlib mylib cunit)
