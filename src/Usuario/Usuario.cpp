//
// Created by melvin on 19/12/24.
//

#include "../../includes/Usuario/Usuario.h"

Usuario::Usuario(string username, string nombre, string contrasena, string departamento, string empresa) {
    this->username = username;
    this->nombre = nombre;
    this->contrasena = contrasena;
    this->departamento = departamento;
    this->empresa = empresa;
    this->arbol = new ArbolAVL();
}


string Usuario::getNombre() {
    return this->nombre;
}

string Usuario::getDepartamento() {
    return this->departamento;
}

string Usuario::getEmpresa() {
    return this->empresa;
}

ArbolAVL *Usuario::getArbol() {
    return this->arbol;
}

string Usuario::getContrasena() {
    return this->contrasena;
}

string Usuario::getUsername() {
    return this->username;
}

// Implementar metodos de la clase



