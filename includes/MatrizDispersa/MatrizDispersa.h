//
// Created by melvin on 12/12/24.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"


//Caso de agregar atras y adelante de un nodo

//Agregar el metodo para insertar en donde ya existen las cabeceras y valor


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
    NodoMatriz *cabeceraHorizontal(string valor);
    NodoMatriz *cabeceraVertical(string valor);

    NodoMatriz *insertarCabeceraHorizontal(string valor);
    NodoMatriz *insertarCabeceraVertical(string valor);
    void insertarValor(string valor, string cabezaHorizontal, string cabezaVertical);
    void insertarAlFinal(string valor, NodoMatriz *cabezaHorizontal, NodoMatriz *cabezaVertical);


    void insertarAlFinalVertical(string valor, NodoMatriz *nodoHorizontal);
    void insertarAlMedio(string valor, NodoMatriz *nodoVertical);

    //Metodos que llegue hasta la cabecera horizontal y vertical de cualquier nodo
    NodoMatriz *llegarCabeceraHorizontal(NodoMatriz *nodo);
    NodoMatriz *llegarCabeceraVertical(NodoMatriz *nodo);

    //Insertar un valor en cabeceras que ya existen y ya tienen un usuario
    void insertarValorCabecerasExistentes(string valor, string departamento, string institucion);

};



#endif //MATRIZDISPERSA_H
