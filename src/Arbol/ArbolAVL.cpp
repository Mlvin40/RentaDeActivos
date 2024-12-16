//
// Created by melvin on 15/12/24.
//

#include  "../../includes/Arbol/ArbolAVL.h"

#include <iostream>
#include <string>

ArbolAVL::ArbolAVL()
{
    this->raiz = nullptr;
}

void ArbolAVL::insertar(int valor)
{
    NodoAVL* nodo = new NodoAVL(valor);
    insertar(nodo, this->raiz);
}

void ArbolAVL::insertar(NodoAVL* valor, NodoAVL *&raiz){
    if (raiz == nullptr){
        raiz = valor;
        std::cout<< "El Fe de " + std::to_string(raiz->getValor()) + " es: " + std::to_string(factEquilibrio(raiz)) << std::endl;
        return;
    }

    if (valor->getValor() < raiz->getValor()){
        insertar(valor, raiz->getIzquierdo());
    }
    else{
        insertar(valor, raiz->getDerecho());
    }

    std::cout<< "El Fe de " + std::to_string(raiz->getValor()) + " es: " + std::to_string(factEquilibrio(raiz)) << std::endl;


}

int ArbolAVL::alturaMax(NodoAVL* nodo){
    if (nodo == nullptr){
        return 0;
    }
    int hijoIzquierdo = alturaMax(nodo->getIzquierdo());
    int hijoDerecho = alturaMax(nodo->getDerecho());

    return hijoIzquierdo > hijoDerecho ? hijoIzquierdo + 1 : hijoDerecho + 1;

}

int ArbolAVL::factEquilibrio(NodoAVL* nodo){
    if (nodo == nullptr){
        return 0;
    }
    return alturaMax(nodo->getDerecho()) - alturaMax(nodo->getIzquierdo());
}