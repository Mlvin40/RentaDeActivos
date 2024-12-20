//
// Created by melvin on 15/12/24.
//

#ifndef NODOAVL_H
#define NODOAVL_H

#include <iostream>
#include <random>
#include <string>
#include <chrono>

using namespace std;

class NodoAVL {
private:
    int factorEquilibrio;
    NodoAVL *izquierdo;
    NodoAVL *derecho;


    //Para la logica del proyecto un nodo representa un activo fijo
    string valor; // ID del activo fijo
    string nombreActivo;
    string descripcionActivo;
    bool disponible = true;
    string generarID();

    //getter y setter
public:
    NodoAVL(string nombreActivo, string descripcion); // Constructor


    //Getters y Setters
    string getValor();
    void setValor(string valor);
    string getNombreActivo();
    void setNombreActivo(string nombreActivo);
    string getDescripcionActivo();
    void setDescripcionActivo(string descripcionActivo);
    bool isDisponible();
    void setDisponible(bool disponible);


    int getFactorEquilibrio();
    void setFactorEquilibrio(int factorEquilibrio);
    NodoAVL *&getIzquierdo();
    void setIzquierdo(NodoAVL *izquierdo);
    NodoAVL *&getDerecho();
    void setDerecho(NodoAVL *derecho);

    void mostrarDetallesActivo();


};


#endif //NODOAVL_H
