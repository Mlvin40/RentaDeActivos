//
// Created by melvin on 12/12/24.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"

class MatrizDispersa {
public:
    // cabecera horizontal
    NodoMatriz *nodoCabeceraHorizontal;

    // cabecera vertical
    NodoMatriz *nodoCabeceraVertical;

    MatrizDispersa();


    // metodos de la matriz

    bool estaVacia();

    //metodo para saber si existe o no una cabecera
    NodoMatriz *cabeceraHorizontal(int valor);
    NodoMatriz *cabeceraVertical(int valor);


    NodoMatriz *insertarCabeceraHorizontal(int valor);
    NodoMatriz *insertarCabeceraVertical(int valor);
    void insertarValor(int valor, int cabezaHorizontal, int cabezaVertical);
    void insertarAlFinal(int valor, NodoMatriz *cabezaHorizontal, NodoMatriz *cabezaVertical);


};



#endif //MATRIZDISPERSA_H
