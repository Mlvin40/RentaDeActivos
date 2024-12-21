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

void ArbolAVL::insertar(const string& nombreActivo, const string& descripcion, int diasRenta)
{
    NodoAVL* nodo = new NodoAVL(nombreActivo, descripcion, diasRenta);
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
void::ArbolAVL::eliminar(string valor){
    eliminar(valor, this->raiz);
}

bool ArbolAVL::esHoja(NodoAVL* nodo)
{
 // Si el nodo no tiene hijos es una hoja
    return nodo->getIzquierdo() == nullptr && nodo->getDerecho() == nullptr;
}

void::ArbolAVL::eliminar(string valor, NodoAVL *&raiz)
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

NodoAVL* ArbolAVL::buscar(const std::string& valor) const {
    return buscar(valor, this->raiz);
}

NodoAVL* ArbolAVL::buscar(const std::string& valor, NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return nullptr; // No se encontró el valor
    }

    if (valor == nodo->getValor()) {
        return nodo; // Se encontró el nodo con el valor
    }

    if (valor < nodo->getValor()) {
        return buscar(valor, nodo->getIzquierdo()); // Buscar en el subárbol izquierdo
    }

    return buscar(valor, nodo->getDerecho()); // Buscar en el subárbol derecho
}

/*******************************************************************************************************************
 * Metodo para recorrer el arbol en preorden
 * *****************************************************************************************************************/
void ArbolAVL::recorreArbol(NodoAVL *raiz) {
    if (raiz == nullptr) {
        return;
    }

    // Verificar si el nodo actual está disponible
    if (raiz->isDisponible()) {
        raiz->mostrarDetallesActivo(); // Metodo para filtrar los activos disponibles
    }

    // Recorrer el subárbol izquierdo
    recorreArbol(raiz->getIzquierdo());

    // Recorrer el subárbol derecho
    recorreArbol(raiz->getDerecho());
}

void ArbolAVL::recorrerArbol() {
    recorreArbol(this->raiz);
}


// para todo el arbol sin parametros
void ArbolAVL::recorrerTodoElArbol() {
    recorrerTodoElArbol(this->raiz);
}

void ArbolAVL::recorrerTodoElArbol(NodoAVL *raiz) {
    if (raiz == nullptr) {
        return;
    }

    raiz->mostrarDetallesActivo(); // Metodo para filtrar los activos disponibles

    // Recorrer el subárbol izquierdo
    recorrerTodoElArbol(raiz->getIzquierdo());

    // Recorrer el subárbol derecho
    recorrerTodoElArbol(raiz->getDerecho());
}


// Recorrer todo el arbol para mostrar los activos que no estan rentados
void ArbolAVL::mostrarYaRentados() {
    mostrarYaRentados(this->raiz);
}

void ArbolAVL::mostrarYaRentados(NodoAVL *raiz) {
    if (raiz == nullptr) {
        return;
    }

    if (!raiz->isDisponible()) {
        raiz->mostrarDetallesActivo(); // Metodo para filtrar los activos rentados
    }

    // Recorrer el subárbol izquierdo
    mostrarYaRentados(raiz->getIzquierdo());

    // Recorrer el subárbol derecho
    mostrarYaRentados(raiz->getDerecho());
}

// ********************************************************************************************************************
// REPORTE DEL ARBOL AVL
void ArbolAVL::graficarArbol() {

    // Crear el archivo DOT con un nombre predeterminado para que se sobrescriba en cada llamada
    std::ofstream archivo("arbol.dot");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para crear el grafo." << std::endl;
        return;
    }

    // Iniciar el archivo DOT
    archivo << "digraph AVL {\n";
    archivo << "    node [shape=circle, style=filled];\n";

    // Generar nodos y conexiones
    if (raiz != nullptr) {
        graficarNodo(archivo, raiz);
    }

    archivo << "}\n";
    archivo.close();

    std::cout << "Archivo arbol DOT creado exitosamente: " << std::endl;
}


void ArbolAVL::graficarNodo(std::ofstream& archivo, NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Determinar el color del nodo según la propiedad isActivo
    std::string color = nodo->isDisponible() ? "lightblue" : "red";

    // Crear nodo con nombre, valor y color
    archivo << "    \"" << nodo->getValor() << "\" [label=\""
            << nodo->getNombreActivo() << "\\n" // Mostrar el nombre en una línea
            << nodo->getValor() << "\", fillcolor=" << color << "];\n"; // Mostrar el valor y aplicar el color

    // Enlazar con el hijo izquierdo
    if (nodo->getIzquierdo() != nullptr) {
        archivo << "    \"" << nodo->getValor() << "\" -> \""
                << nodo->getIzquierdo()->getValor() << "\";\n";
        graficarNodo(archivo, nodo->getIzquierdo());
    }

    // Enlazar con el hijo derecho
    if (nodo->getDerecho() != nullptr) {
        archivo << "    \"" << nodo->getValor() << "\" -> \""
                << nodo->getDerecho()->getValor() << "\";\n";
        graficarNodo(archivo, nodo->getDerecho());
    }
}

