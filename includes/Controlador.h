//
// Created by melvin on 19/12/24.
//

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../includes/MatrizDispersa/MatrizDispersa.h"
#include "../includes/ListaDoble/ListaDobleEnlazada.h"
#include "../includes/Usuario/Usuario.h"
#include "../includes/Transacciones/RentaActivo.h"

#include <iostream>
#include <string>

class Controlador {
private:
    // La matriz dispersa inicial
    MatrizDispersa* matrizDispersa;
    // Lista de usuarios y lista de activos
    ListaDobleEnlazada<Usuario>* listaUsuarios;
    ListaDobleEnlazada<RentaActivo>* listaTransacciones;
    Usuario *usuarioLogueado;


    void iniciarMenu();
    void usuariosGrabados();

public:
    //CONSTRUCTOR
    Controlador();
    void iniciarSistema();

};



#endif //CONTROLADOR_H
