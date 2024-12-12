//
// Created by melvin on 11/12/24.
//

 #include "../includes/Menu.h"

//Implementar el menu
Menu::Menu() {
}

Menu::~Menu() {
    delete this;
}

void Menu::iniciarMenu() {
    cout<<mensajeBienvenida<<endl;
}

void Menu::finalizarMenu() {
    cout<<mensajeDespedida<<endl;
}

// Setters
void Menu::setMensajeBienvenida(string mensaje) {
    mensajeBienvenida = mensaje;
}

void Menu::setMensajeDespedida(string mensajeDespedida) {
    this->mensajeDespedida = mensajeDespedida;
}

// Getters
string Menu::getMensajeBienvenida() {
    return this->mensajeBienvenida;
}

string Menu::getMensajeDespedida() {
    return this->mensajeDespedida;
}