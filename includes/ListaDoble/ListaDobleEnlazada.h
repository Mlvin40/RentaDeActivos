#ifndef LISTADOBLEENLAZADA_H
#define LISTADOBLEENLAZADA_H

#include <iostream>
#include <stdexcept>
#include "../../includes/ListaDoble/NodoDoble.h"

template <typename T>
class ListaDobleEnlazada {
private:
    NodoDoble<T>* inicio;
    NodoDoble<T>* fin;
    int tamano;

    // Métodos auxiliares
    NodoDoble<T>* obtenerNodoAvanzando(int index) const;
    NodoDoble<T>* obtenerNodoRetrocediendo(int index) const;

public:
    // Constructor
    ListaDobleEnlazada();

    // Métodos públicos
    bool estaVacia() const;
    void agregarElemento(T* valor);
    void eliminarUltimo();
    T* obtenerContenido(int index) const;
};

#include "../../src/ListaDoble/ListaDobleEnlazada.tpp"

#endif // LISTADOBLEENLAZADA_H
