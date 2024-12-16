#include <iostream>
#include "includes/Menu.h"
#include "includes/MatrizDispersa/MatrizDispersa.h"
#include "includes/ListaDoble/ListaDobleEnlazada.h"
#include "includes/Arbol/ArbolAVL.h"

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


    // Falta probar estos casos
    //matriz_dispersa->insertarValor("Usuario6", "Jutiapa", "Cinepolis");
    //****matriz_dispersa->insertarValor("Usuario7", "Guatemala", "IGSS"); //debe de insertarse atras del usuario que esta asociado a esa empresa y departamento
    matriz_dispersa->insertarValor("Usuario8", "Peten", "Cinepolis");
    matriz_dispersa->insertarValor("Usuario10", "Totonicapan", "Vienesa");
    //matriz_dispersa->insertarValor("Usuario9", "Escuintla", "IGSS");
    //matriz_dispersa->insertarValor("Usuario10", "Escuintla", "Cinepolis");
    matriz_dispersa->insertarValor("Usuario11", "Escuintla", "Vienesa");
    matriz_dispersa->insertarValor("Usuario13", "Jutiapa", "Vienesa");
    matriz_dispersa->insertarValor("Usuario12", "Peten", "Vienesa");
    //Revisar matriz_dispersa->insertarValor("Usuario14", "Guatemala", "Vienesa");
    matriz_dispersa->insertarValor("Usuario15", "Peten", "Max");

    matriz_dispersa->graficarMatriz("matriz.dot");

    //Probar la lista doble enlazada de tipo string

    ArbolAVL *arbol = new ArbolAVL();
    /*arbol->insertar(10);
    arbol->insertar(5);
    arbol->insertar(4);
    arbol->insertar(6);
    arbol->insertar(15);
    arbol->insertar(14);
    arbol->insertar(0);
    arbol->insertar(1);
    arbol->insertar(2);
    arbol->insertar(3);
    arbol->insertar(7);
    arbol->insertar(8);
    arbol->insertar(9);
    arbol->insertar(11);
    arbol->insertar(12);
    arbol->insertar(13);
    arbol->insertar(16);
    arbol->insertar(17);
    arbol->insertar(68);
    arbol->insertar(69);
    arbol->insertar(70);*/

    // insertar los valores 3 1 0 10 5 4 6 12 11 14
    arbol->insertar(3);
    arbol->insertar(1);
    arbol->insertar(0);
    arbol->insertar(10);
    arbol->insertar(5);
    arbol->insertar(4);
    arbol->insertar(6);
    arbol->insertar(12);
    arbol->insertar(11);
    arbol->insertar(14);
    arbol->insertar(16);
    arbol->insertar(21);
    arbol->insertar(22);
    arbol->insertar(23);


    arbol->graficarArbol("arbol.dot");
    return 0;
}

