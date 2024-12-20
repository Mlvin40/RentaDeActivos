//
// Created by melvin on 19/12/24.
//

#ifndef USUARIO_H
#define USUARIO_H

#include "../Arbol/ArbolAVL.h"

#include <iostream>
using namespace std;

class Usuario {

private:
    string nombre;
    string username;
    string contrasena;
    string departamento;
    string empresa;
    ArbolAVL *arbol;

public:
    //getters de todo
    Usuario(string username, string nombre, string contrasena, string departamento, string empresa);
    ~Usuario();
    string getNombre();
    string getDepartamento();
    string getEmpresa();
    ArbolAVL *getArbol();
    string getContrasena();
    string getUsername();



    // Implementar metodos de la clase

};



#endif //USUARIO_H
