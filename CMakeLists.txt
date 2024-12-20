cmake_minimum_required(VERSION 3.30)
project(RentaActivosP1)

set(CMAKE_CXX_STANDARD 23)

add_executable(RentaActivosP1 main.cpp
        includes/MatrizDispersa/NodoMatriz.h
        includes/MatrizDispersa/MatrizDispersa.h
        src/MatrizDispersa/MatrizDispersa.cpp
        src/MatrizDispersa/NodoMatriz.cpp
        includes/ListaDoble/NodoDoble.h
        includes/ListaDoble/ListaDobleEnlazada.h
        includes/Arbol/NodoAVL.h
        src/Arbol/NodoAVL.cpp
        includes/Arbol/ArbolAVL.h
        src/Arbol/ArbolAVL.cpp
        includes/Transacciones/RentaActivo.h
        includes/Usuario/Usuario.h
        src/Usuario/Usuario.cpp
        includes/Controlador.h
        src/Controlador.cpp
        src/Transacciones/RentaActivo.cpp
        includes/Util.h
        src/Util.cpp
)
