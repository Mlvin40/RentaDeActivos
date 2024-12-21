//
// Created by melvin on 19/12/24.
//

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../includes/MatrizDispersa/MatrizDispersa.h"
#include "../includes/ListaDoble/ListaDobleEnlazada.h"
#include "../includes/Usuario/Usuario.h"
#include "../includes/Transacciones/RentaActivo.h"
#include "../includes/Util.h"

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
    Util *util;

    void iniciarLogin();
    void usuariosGrabados();
    void iniciarMenuAdministrador();
    void iniciarMenuUsuario();
    void separador();

    //********************************************************************************************************************
    //Para el usuario administrador
    void registrarUsuario();
    void reporteMatrizDispersa();
    void reporteActivosDisponiblesDepartamento();
    void reporteActivosDisponiblesEmpresa();
    void reporteTransacciones();
    void reporteActivosUsuario();
    void activosRentadosUsuario();
    void ordenarTransaccion();
    //********************************************************************************************************************


    //********************************************************************************************************************
    //Para el usuario normal
    void agregarActivo();
    void eliminarActivo();
    void modificarActivo();
    void rentarActivo();
    void activosRentados();
    void misActivosRentados();
    //********************************************************************************************************************
public:
    //CONSTRUCTOR
    Controlador();
    void iniciarSistema();
};



#endif //CONTROLADOR_H
