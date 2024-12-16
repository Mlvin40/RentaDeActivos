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
        if (factEquilibrio(raiz->getIzquierdo()) > 0)
        {
            //Rotacion doble
            rotacionDerechaIzquierda(raiz);
            return;
        }
        // Rotacion Simple
        rotacionIzquierda(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1)
    {
        if (raiz->getDerecho()->getFactorEquilibrio() < 0)
        {
            //Rotacion doble
            rotacionIzquierdaDerecha(raiz);
            return;
        }
        // Rotacion Simple
        rotacionDerecha(raiz);

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


void ArbolAVL::rotacionIzquierda(NodoAVL *&nodo){
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

void ArbolAVL::rotacionDerecha(NodoAVL *&nodo){
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

void ArbolAVL::rotacionIzquierdaDerecha(NodoAVL *&nodo){
    rotacionIzquierda(nodo->getDerecho());
    rotacionDerecha(nodo);

}

void ArbolAVL::rotacionDerechaIzquierda(NodoAVL *&nodo){
    rotacionDerecha(nodo->getIzquierdo());
    rotacionIzquierda(nodo);
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
    std::cout << "Ahora puedes usar Graphviz para generar la imagen.\n"
              << "Ejemplo de comando: dot -Tpng " << nombreArchivo << " -o arbol.png\n";
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
