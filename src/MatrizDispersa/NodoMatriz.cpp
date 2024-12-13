//
// Created by melvin on 12/12/24.
//

#include "../../includes/MatrizDispersa/NodoMatriz.h"

NodoMatriz::NodoMatriz(int valor) {
    this->valor = valor;
    this->siguiente = nullptr;
    this->anterior = nullptr;
    this->arriba = nullptr;
    this->abajo = nullptr;
    this->adelante = nullptr;
    this->atras = nullptr;
}