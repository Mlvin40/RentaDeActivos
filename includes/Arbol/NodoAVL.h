//
// Created by melvin on 15/12/24.
//

#ifndef NODOAVL_H
#define NODOAVL_H



class NodoAVL {
private:
    int valor;
    int factorEquilibrio;
    NodoAVL *izquierdo;
    NodoAVL *derecho;

    //getter y setter
public:
    NodoAVL(int valor); // Constructor


    //Getters y Setters
    int getValor();
    void setValor(int valor);
    int getFactorEquilibrio();
    void setFactorEquilibrio(int factorEquilibrio);
    NodoAVL *&getIzquierdo();
    void setIzquierdo(NodoAVL *izquierdo);
    NodoAVL *&getDerecho();
    void setDerecho(NodoAVL *derecho);

};


#endif //NODOAVL_H
