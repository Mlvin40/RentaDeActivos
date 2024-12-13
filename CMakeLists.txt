cmake_minimum_required(VERSION 3.30)
project(RentaActivosP1)

set(CMAKE_CXX_STANDARD 23)

add_executable(RentaActivosP1 main.cpp
        includes/Menu.h
        src/Menu.cpp
        includes/MatrizDispersa/NodoMatriz.h
        includes/MatrizDispersa/MatrizDispersa.h
        src/MatrizDispersa/MatrizDispersa.cpp
        src/MatrizDispersa/NodoMatriz.cpp
)
