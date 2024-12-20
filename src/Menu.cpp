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

void Menu::finalizarMenu() {
    cout<<mensajeDespedida<<endl;
}


