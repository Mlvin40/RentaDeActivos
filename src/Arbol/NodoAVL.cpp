//
// Created by melvin on 15/12/24.
//

#include "../../includes/Arbol/NodoAVL.h"

NodoAVL::NodoAVL(string nombreActivo, string descripcion, int diasRenta){
    this->nombreActivo = nombreActivo;
    this->descripcionActivo = descripcion;
    this->diasRenta = diasRenta;
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
    // Semilla basada en el tiempo actual (solo se usa una vez)
    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    // Distribución uniforme [0, 9]
    std::uniform_int_distribution<int> distribucion(0, 9);

    // Generar un ID de 15 dígitos
    std::string id;
    for (int i = 0; i < 15; i++) {
        id += std::to_string(distribucion(generator)); // Genera un dígito y lo agrega al ID
    }

    // Eliminar cualquier espacio en blanco
    id.erase(std::remove_if(id.begin(), id.end(), [](unsigned char c) { return std::isspace(c); }), id.end());


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

int NodoAVL::getDiasRenta()
{
    return this->diasRenta;
}

void NodoAVL::mostrarDetallesActivo()
{
    cout << "ID: " << this->valor << ";" << " Nombre: " << this->nombreActivo << ";" << " Descripcion: " << this->descripcionActivo << ";" <<" Tiempo de Renta: " << this->diasRenta << endl;
}

// Created by melvin on 15/12/24.





