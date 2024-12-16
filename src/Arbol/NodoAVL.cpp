//
// Created by melvin on 15/12/24.
//

#include "../../includes/Arbol/NodoAVL.h"

NodoAVL::NodoAVL(int valor)
{
    this->valor = valor;
    this->factorEquilibrio = 0;
    this->izquierdo = nullptr;
    this->derecho = nullptr;

}

int NodoAVL::getValor()
{
    return this->valor;
}

void NodoAVL::setValor(int valor)
{
    this->valor = valor;
}

int NodoAVL::getFactorEquilibrio()
{
    return this->factorEquilibrio;
}

void NodoAVL::setFactorEquilibrio(int factorEquilibrio)
{
    this->factorEquilibrio = factorEquilibrio;
}

NodoAVL *&NodoAVL::getIzquierdo()
{
    return this->izquierdo;
}

void NodoAVL::setIzquierdo(NodoAVL *izquierdo)
{
    this->izquierdo = izquierdo;
}

NodoAVL *&NodoAVL::getDerecho()
{
    return this->derecho;
}

void NodoAVL::setDerecho(NodoAVL *derecho)
{
    this->derecho = derecho;
}

// Created by melvin on 15/12/24.





