//
// Created by melvin on 15/12/24.
//

#include "../../includes/Arbol/NodoAVL.h"

NodoAVL::NodoAVL(string nombreActivo, string descripcion){
    this->nombreActivo = nombreActivo;
    this->descripcionActivo = descripcion;
    this->valor = generarID();
    this->factorEquilibrio = 0;
    this->izquierdo = nullptr;
    this->derecho = nullptr;

}

string NodoAVL::getValor()
{
    return this->valor;
}

void NodoAVL::setValor(string valor)
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

string NodoAVL::generarID(){

    // Semilla basada en el tiempo actual
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Generador de números aleatorios
    std::mt19937 generator(seed);

    // Distribución uniforme [0, 9]
    std::uniform_int_distribution<int> distribucion(0, 9);

    std::string id;
    for (int i = 0; i < 15; i++) {
        id += std::to_string(distribucion(generator)); // Genera un dígito y lo agrega al ID
    }
    return id;
}

string NodoAVL::getNombreActivo()
{
    return this->nombreActivo;
}

void NodoAVL::setNombreActivo(string nombreActivo)
{
    this->nombreActivo = nombreActivo;
}

string NodoAVL::getDescripcionActivo()
{
    return this->descripcionActivo;
}

void NodoAVL::setDescripcionActivo(string descripcionActivo)
{
    this->descripcionActivo = descripcionActivo;
}

bool NodoAVL::isDisponible()
{
    return this->disponible;
}

void NodoAVL::setDisponible(bool disponible)
{
    this->disponible = disponible;
}

void NodoAVL::mostrarDetallesActivo()
{
    cout << "ID: " << this->valor << ";" << "Nombre: " << this->nombreActivo << ";" << "Descripcion: " << this->descripcionActivo << endl;
}

// Created by melvin on 15/12/24.





