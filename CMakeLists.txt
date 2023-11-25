cmake_minimum_required(VERSION 3.26)
project(Projeto_final_ITP C)

set(CMAKE_C_STANDARD 23)

add_library(Projeto_final_ITP
        database.c
        database.h)
