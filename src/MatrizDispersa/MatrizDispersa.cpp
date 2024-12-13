//
// Created by melvin on 12/12/24.
//

#include "../../includes/MatrizDispersa/MatrizDispersa.h"

//Siguiente anterior es de cabeceras horizontales
//Arriba abajo es de cabeceras verticales
//Adelante atras es de nodos de la matriz que representa a los usuarios
//Cada nodo de la matriz tiene un valor y 6 apuntadores


// Constructor de la matriz dispersa que inicializa las cabeceras horizontales y verticales en null
MatrizDispersa::MatrizDispersa() {
    this->nodoCabeceraHorizontal = nullptr;
    this->nodoCabeceraVertical = nullptr;
}

bool MatrizDispersa::estaVacia() {
    if (this->nodoCabeceraHorizontal == nullptr && this->nodoCabeceraVertical == nullptr) {
        return true;
    }
    return false;
}

NodoMatriz *MatrizDispersa::cabeceraHorizontal(int valor) {
    if (estaVacia())
    {
        return nullptr;
    }

    //Recorrer la lista de cabeceras horizontales
    NodoMatriz *auxiliar = nodoCabeceraHorizontal;
    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }
    return nullptr;

}

NodoMatriz *MatrizDispersa::cabeceraVertical(int valor) {
    if (estaVacia())
    {
        return nullptr;
    }
    NodoMatriz *auxiliar = nodoCabeceraVertical;
    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->abajo;
    }
    return nullptr;
}

// Metodo para insertar una cabecera vertical en la matriz dispersa
NodoMatriz *MatrizDispersa::insertarCabeceraHorizontal(int valor) {

    NodoMatriz *nuevaCabecera = new NodoMatriz(valor);

    // si la matriz esta vacia se inserta la cabecera horizontal en la matriz dispersa
    if (nodoCabeceraHorizontal == nullptr)
    {
        nodoCabeceraHorizontal = nuevaCabecera;
        return nuevaCabecera;
    }

    NodoMatriz *auxiliar = nodoCabeceraHorizontal;

    while (auxiliar->siguiente != nullptr){
        auxiliar = auxiliar->siguiente;
    }

    auxiliar->siguiente = nuevaCabecera;
    nuevaCabecera->anterior = auxiliar;

    return nuevaCabecera;

}

NodoMatriz *MatrizDispersa::insertarCabeceraVertical(int valor) {
    NodoMatriz *nuevaCabecera = new NodoMatriz(valor);

    if (nodoCabeceraVertical == nullptr)
    {
        nodoCabeceraVertical = nuevaCabecera;
        return nuevaCabecera;
    }

    NodoMatriz *auxiliar = nodoCabeceraVertical;

    while (auxiliar->abajo != nullptr){
        auxiliar = auxiliar->abajo;
    }

    auxiliar->abajo = nuevaCabecera;
    nuevaCabecera->arriba = auxiliar;

    return nuevaCabecera;
}


// Metodo para insertar un valor en la matriz dispersa
void MatrizDispersa::insertarValor(int valor, int cabezaHorizontal, int cabezaVertical) {

    //Cuando la matriz esta vacia se inserta el primer nodo entre las cabeceras
    if (estaVacia())
    {
        NodoMatriz *nodoCabeceraHorizontal = insertarCabeceraHorizontal(cabezaHorizontal);
        NodoMatriz *nodoCabeceraVertical = insertarCabeceraVertical(cabezaVertical);
        insertarAlFinal(valor, nodoCabeceraHorizontal, nodoCabeceraVertical);
    }
}


// Metodo para insertar un valor al final de la matriz dispersa
void MatrizDispersa::insertarAlFinal(int valor, NodoMatriz* cabezaHorizontal, NodoMatriz* cabezaVertical){
    NodoMatriz *usuarioNuevo = new NodoMatriz(valor);

    NodoMatriz *auxiliarHorizontal = cabezaHorizontal;
    NodoMatriz *auxiliarVertical = cabezaVertical;

    while (auxiliarHorizontal->abajo != nullptr){
        auxiliarHorizontal = auxiliarHorizontal->abajo;
    }

    // con esto se llega al ultimo nodo de la cabecera horizontal
    auxiliarHorizontal-> abajo = usuarioNuevo;
    usuarioNuevo->arriba = auxiliarHorizontal;

    while (auxiliarVertical->siguiente != nullptr){
        auxiliarVertical = auxiliarVertical->siguiente;
    }

    auxiliarVertical->siguiente = usuarioNuevo;
    usuarioNuevo->anterior = auxiliarVertical;

}


