//
// Created by melvin on 19/12/24.
//

#include "../includes/Controlador.h"
#include "../includes/Menu.h"

Controlador::Controlador() {
    this->matrizDispersa = new MatrizDispersa();
    this->listaUsuarios = new ListaDobleEnlazada<Usuario>();
    this->listaTransacciones = new ListaDobleEnlazada<RentaActivo>();
    this->usuarioLogueado = nullptr;
}

void Controlador::iniciarSistema() {
    iniciarMenu();
}

void Controlador::iniciarMenu(){
    usuariosGrabados();
    Menu *menu = new Menu();
    menu->setMensajeBienvenida("Bienvenido al sistema de control de activos fijos");
    menu->setMensajeDespedida("Gracias por utilizar el sistema de control de activos fijos");
    menu->iniciarMenu();
    menu->finalizarMenu();
}

void Controlador::usuariosGrabados(){
    Usuario *user;

    user = new Usuario("elian_estrada", "Elian Estrada", "1234", "guatemala", "igss");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("juanito", "Juan Perez", "4567", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("casimiro", "Carlos Perez", "721896", "guatemala", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("incrediboy", "Iraldo Martinez", "201598", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("pedrito", "Pedro Rodriguez", "48956", "jalapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("juanma", "Juan Manuel", "32897", "guatemala", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("azurdia", "Alejandra Guzman", "780145", "jutiapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("alcachofa", "Antonio Lopez", "20435", "jalapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("mafer", "Maria Fernandez", "54312", "peten", "cinepolis");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("fuego03", "Fernando Mendez", "891346", "jutiapa", "cinepolis");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    matrizDispersa->graficarMatriz("matriz.dot");
    cout << "Usuarios grabados exitosamente" << endl;

}
