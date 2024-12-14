//
// Created by melvin on 12/12/24.
//

#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include <iostream>
using namespace std;

class NodoMatriz {
public:
    // LO QUE CONTIENE EL NODO
    string valor = "";
    //Diferentes apuntadores para las 3 dimensiones
    NodoMatriz *siguiente;
    NodoMatriz *anterior;

    NodoMatriz *arriba;
    NodoMatriz *abajo;

    NodoMatriz *adelante;
    NodoMatriz *atras;

    // se inicializa el nodo con los apuntadores en null
    NodoMatriz(string valor);

};



#endif //NODOMATRIZ_H
