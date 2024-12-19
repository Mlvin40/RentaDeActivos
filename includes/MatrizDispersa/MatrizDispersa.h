//
// Created by melvin on 12/12/24.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"
#include <iostream>
using namespace std;


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
    void insertarAlFinal(NodoMatriz *usuarioNuevo, NodoMatriz *cabezaHorizontal, NodoMatriz *cabezaVertical);

    void insertarAlFinalVertical(NodoMatriz *usuarioNuevo, NodoMatriz *nodoVertical);
    void insertarAlMedioVertical(NodoMatriz *usuarioNuevo, NodoMatriz *vertical);
    void insertarAlMedioHorizontal(NodoMatriz *usuarioNuevo, NodoMatriz *horizontal);
    void insertarAlFinalHorizontal(NodoMatriz *usuarioNuevo, NodoMatriz *nodoHorizontal);


    //Metodos que llegue hasta la cabecera horizontal y vertical de cualquier nodo
    NodoMatriz *llegarCabeceraHorizontal(NodoMatriz *nodo);
    NodoMatriz *llegarCabeceraVertical(NodoMatriz *nodo);


    bool masAbajo(NodoMatriz *cabeceraV, string valor);
    bool masDerecha(NodoMatriz *cabeceraH, string valor);

    //Insertar un valor en cabeceras que ya existen y ya tienen un usuario
    void insertarValorCabecerasExistentes(string valor, string departamento, string institucion);


    //Ultimos metodos
    void graficarMatriz(const string& nombreArchivo);
    NodoMatriz* buscarNodo(string departamento, string empresa);

    void insertarAdelante(NodoMatriz *usuarioExistente, string nuevoUsuario);
    void insertarAtras(NodoMatriz *nodo, string nuevoUsuario);


};


#endif //MATRIZDISPERSA_H
