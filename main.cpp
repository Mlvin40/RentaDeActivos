#include <iostream>
#include "includes/Menu.h"
#include "includes/MatrizDispersa/MatrizDispersa.h"

int main()
{
    // Crear un objeto de la clase Menu en el heap
    Menu *menu = new Menu();
    menu->iniciarMenu();
    menu->finalizarMenu();

    MatrizDispersa *matriz_dispersa = new MatrizDispersa();
    //Simular la insercion de valores en la matriz dispersa
    matriz_dispersa->insertarValor("Usuario1", "Guatemala", "IGSS");
    matriz_dispersa->insertarValor("Usuario2", "Jutiapa", "IGSS");
    matriz_dispersa->insertarValor("Usuario3", "Escuintla", "Cinepolis");

    return 0;
}

