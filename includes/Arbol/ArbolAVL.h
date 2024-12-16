//
// Created by melvin on 15/12/24.
//

#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "NodoAVL.h"

class ArbolAVL {
private:
    NodoAVL *raiz;
    void insertar(NodoAVL *valor, NodoAVL *&raiz);
    int alturaMax(NodoAVL *nodo);
    int factEquilibrio(NodoAVL *nodo); // formula = al derecho - al izquierdo: Valores permitidos [-1,0,1]



public:
    ArbolAVL(); //Constructor
    ~ArbolAVL(); //Destructor


    //Getters y Setters
    NodoAVL *getRaiz();
    void setRaiz(NodoAVL *raiz);

    //Métodos
    void insertar(int valor);
    void eliminar(int valor);
    bool esHoja(NodoAVL *nodo);







};



#endif //ARBOLAVL_H
