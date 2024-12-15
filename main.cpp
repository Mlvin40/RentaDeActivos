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
    matriz_dispersa->insertarValor("Usuario3", "Guatemala", "Cinepolis");
    matriz_dispersa->insertarValor("Usuario4", "Escuintla", "Max");
    matriz_dispersa->insertarValor("Usuario5", "Jutiapa", "Max");

    matriz_dispersa->graficarMatriz("matriz.dot");

/*
    // Falta probar estos casos
    matriz_dispersa->insertarValor("Usuario6", "Jutiapa", "Cinepolis");
    //matriz_dispersa->insertarValor("Usuario7", "Guatemala", "IGSS"); //debe de insertarse atras del usuario que esta asociado a esa empresa y departamento
    matriz_dispersa->insertarValor("Usuario8", "Peten", "Cinepolis");
    matriz_dispersa->insertarValor("Usuario9", "Escuintla", "IGSS");
    matriz_dispersa->insertarValor("Usuario10", "Escuintla", "Cinepolis");
*/


    /*
     * matrizDispersa
     * listaUsuarios
     */
    return 0;
}

