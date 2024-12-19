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


// Metodo para insertar un nodo en el arbol AVL
void ArbolAVL::insertar(NodoAVL* valor, NodoAVL *&raiz){
    if (raiz == nullptr){
        raiz = valor;
        raiz->setFactorEquilibrio(factEquilibrio(raiz));
        return;
    }

    if (valor->getValor() < raiz->getValor()){
        insertar(valor, raiz->getIzquierdo());
    }
    else{
        insertar(valor, raiz->getDerecho());
    }

    raiz->setFactorEquilibrio(factEquilibrio(raiz));

    if (raiz->getFactorEquilibrio() < -1){
        if (raiz->getIzquierdo()->getFactorEquilibrio() > 0)
        {
            //Rotacion doble
            rotacionIzquierdaDerecha(raiz);
            return;
        }
        // Rotacion Simple
        rotacionDerecha(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1)
    {
        if (raiz->getDerecho()->getFactorEquilibrio() < 0)
        {
            //Rotacion doble
            rotacionDerechaIzquierda(raiz);
            return;
        }
        // Rotacion Simple
        rotacionIzquierda(raiz);

    }
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


void ArbolAVL::rotacionDerecha(NodoAVL *&nodo){
    NodoAVL *aux = nodo->getIzquierdo();

    nodo-> getIzquierdo() = aux->getDerecho();
    aux->getDerecho() = nodo;
    nodo = aux;

    //Actualizar los factores de equilibrio
    nodo->setFactorEquilibrio(factEquilibrio(nodo));
    nodo->getDerecho()->setFactorEquilibrio(factEquilibrio(nodo->getDerecho()));

    if (nodo->getIzquierdo() == nullptr) return ; // Si no tiene hijo izquierdo
    nodo->getIzquierdo()->setFactorEquilibrio(factEquilibrio(nodo->getIzquierdo()));
}

void ArbolAVL::rotacionIzquierda(NodoAVL *&nodo){
    NodoAVL *aux = nodo->getDerecho();

    nodo-> getDerecho() = aux->getIzquierdo();
    aux->getIzquierdo() = nodo;
    nodo = aux;

    //Actualizar los factores de equilibrio
    nodo->setFactorEquilibrio(factEquilibrio(nodo));
    nodo->getIzquierdo()->setFactorEquilibrio(factEquilibrio(nodo->getIzquierdo()));

    if (nodo->getDerecho() == nullptr) return ; // Si no tiene hijo derecho
    nodo->getDerecho()->setFactorEquilibrio(factEquilibrio(nodo->getDerecho()));

}

void ArbolAVL::rotacionDerechaIzquierda(NodoAVL *&nodo){
    rotacionDerecha(nodo->getDerecho());
    rotacionIzquierda(nodo);

}

void ArbolAVL::rotacionIzquierdaDerecha(NodoAVL *&nodo){
    rotacionIzquierda(nodo->getIzquierdo());
    rotacionDerecha(nodo);
}

NodoAVL *ArbolAVL::masDerecha(NodoAVL *nodo){
    if (nodo->getDerecho() == nullptr){
        return nodo;
    }
    return masDerecha(nodo->getDerecho());
}

// este metodo utiliza el metodo privado que se encarga de eliminar un nodo del arbol
void::ArbolAVL::eliminar(int valor){
    eliminar(valor, this->raiz);
}

bool ArbolAVL::esHoja(NodoAVL* nodo)
{
 // Si el nodo no tiene hijos es una hoja
    return nodo->getIzquierdo() == nullptr && nodo->getDerecho() == nullptr;
}

void::ArbolAVL::eliminar(int valor, NodoAVL *&raiz)
{
    if (raiz == nullptr){ // esto significa que el valor no existe dentro del arbol
        std::cout << "El valor no existe en el arbol" << std::endl;
        return;
    }

    // Al eliminar cualquier nodo se debe recalcular los factores de equilibrio
    if (valor == raiz->getValor()){  // si el valor es menor que el valor de la raiz para saber si se va a la izquierda o derecha

        if (esHoja(raiz)){ // Si la raiz es una hoja
            raiz = nullptr;
            return;
        }

        //Si no es una hoja
        if (raiz->getIzquierdo() == nullptr)
        {
            raiz = raiz->getDerecho();
            return;
        }

        if (raiz->getDerecho() == nullptr)
        {
            raiz = raiz->getIzquierdo();
            return;
        }

        //si ninguno de los dos hijos es nulo se debe buscar el nodo mas a la derecha del subarbol izquierdo
        NodoAVL *aux = masDerecha(raiz->getIzquierdo());
        raiz->setValor(aux->getValor()); // Simplemete se cambia el valor del nodo a eliminar por el valor del nodo mas a la derecha


        eliminar(aux->getValor(), raiz->getIzquierdo()); // se elimina el nodo mas a la derecha
        valor = raiz->getValor(); // se cambia el valor a eliminar por el valor del nodo mas a la derecha
        //********************//

    }
    if (valor < raiz->getValor()){
        eliminar(valor, raiz->getIzquierdo());
    }

    else{
        eliminar(valor, raiz->getDerecho());
    }

    raiz->setFactorEquilibrio(factEquilibrio(raiz));

    if (raiz->getFactorEquilibrio() < -1){
        if (raiz->getIzquierdo()->getFactorEquilibrio() > 0)
        {
            //Rotacion doble
            rotacionIzquierdaDerecha(raiz);
            return;
        }
        // Rotacion Simple
        rotacionDerecha(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1) // Significa que esta desequilibrado a la derecha
    {
        if (raiz->getDerecho()->getFactorEquilibrio() < 0)
        {
            //Rotacion doble
            rotacionDerechaIzquierda(raiz);
            return;
        }
        // Rotacion Simple
        rotacionIzquierda(raiz);
        return;
    }

}

// ********************************************************************************************************************
// REPORTE DEL ARBOL AVL
void ArbolAVL::graficarArbol(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para crear el grafo." << std::endl;
        return;
    }

    // Iniciar el archivo DOT
    archivo << "digraph AVL {\n";
    archivo << "    node [shape=circle, style=filled, color=lightblue];\n";

    // Generar nodos y conexiones
    if (raiz != nullptr) {
        graficarNodo(archivo, raiz);
    }

    archivo << "}\n";
    archivo.close();

    std::cout << "Archivo DOT creado exitosamente: " << nombreArchivo << std::endl;
}

void ArbolAVL::graficarNodo(std::ofstream& archivo, NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Crear nodo
    archivo << "    \"" << nodo->getValor() << "\" [label=\""
            << nodo->getValor() << "\"];\n";

    // Enlazar con el hijo izquierdo
    if (nodo->getIzquierdo() != nullptr) {
        archivo << "    \"" << nodo->getValor() << "\" -> \"" << nodo->getIzquierdo()->getValor() << "\";\n";
        graficarNodo(archivo, nodo->getIzquierdo());
    }

    // Enlazar con el hijo derecho
    if (nodo->getDerecho() != nullptr) {
        archivo << "    \"" << nodo->getValor() << "\" -> \"" << nodo->getDerecho()->getValor() << "\";\n";
        graficarNodo(archivo, nodo->getDerecho());
    }
}
