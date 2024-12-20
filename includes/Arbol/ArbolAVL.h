//
// Created by melvin on 15/12/24.
//

#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "NodoAVL.h"
#include <fstream>
#include <string>
#include <iostream>

class ArbolAVL {
private:
    NodoAVL *raiz;
    void insertar(NodoAVL *valor, NodoAVL *&raiz);
    int alturaMax(NodoAVL *nodo);
    int factEquilibrio(NodoAVL *nodo); // formula = al derecho - al izquierdo: Valores permitidos [-1,0,1]

    //Métodos para las rotaciones del árbol
    void rotacionIzquierda(NodoAVL *&nodo);  // Rotación simple
    void rotacionDerecha(NodoAVL *&nodo);  // Rotación simple

    // Rotaciones dobles
    void rotacionIzquierdaDerecha(NodoAVL *&nodo);
    void rotacionDerechaIzquierda(NodoAVL *&nodo);

    void eliminar(string valor, NodoAVL *&raiz);
    bool esHoja(NodoAVL *nodo);
    NodoAVL *masDerecha(NodoAVL *nodo);


    void recorreArbol(NodoAVL *raiz);


public:
    ArbolAVL(); //Constructor
    ~ArbolAVL(); //Destructor


    //Getters y Setters
    NodoAVL *getRaiz();
    void setRaiz(NodoAVL *raiz);

    //Métodos
    void insertar(const string& nombreActivo, const string& descripcion);  //el que se utiliza en el controlador

    void eliminar(string valor);


    void graficarArbol();
    void graficarNodo(std::ofstream& archivo, NodoAVL* nodo);
    NodoAVL* buscar(const std::string& valor) const;
    NodoAVL* buscar(const std::string& valor, NodoAVL* nodo) const;

    void recorrerArbol();


};



#endif //ARBOLAVL_H
