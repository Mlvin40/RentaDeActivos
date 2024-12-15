//
// Created by melvin on 15/12/24.
//

#ifndef NODODOBLE_H
#define NODODOBLE_H

template <typename T>
class NodoDoble {
private:
    T valor;
    NodoDoble* siguiente;
    NodoDoble* anterior;

public:
    // Constructor
    NodoDoble(T valor);

    // Métodos getter y setter
    T getValor() const;
    void setValor(T valor);

    NodoDoble* getSiguiente() const;
    void setSiguiente(NodoDoble* siguiente);

    NodoDoble* getAnterior() const;
    void setAnterior(NodoDoble* anterior);
};

#include "../../src/ListaDoble/NodoDoble.tpp"


#endif //NODODOBLE_H
