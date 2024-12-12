//
// Created by melvin on 11/12/24.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

class Menu
{
private:
    string mensajeBienvenida = "Bienvenido al sistema de ventas";
    string mensajeDespedida = "Gracias por usar el sistema de ventas";

public:
    Menu();
    ~Menu();

    //Metodos
    void iniciarMenu();
    void finalizarMenu();

    //setter
    void setMensajeBienvenida(string mensaje);
    void setMensajeDespedida(string mensaje);

    //getter
    string getMensajeBienvenida();
    string getMensajeDespedida();
};

#endif //MENU_H
