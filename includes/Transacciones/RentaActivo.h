//
// Created by melvin on 19/12/24.
//

#ifndef RENTAACTIVO_H
#define RENTAACTIVO_H

#include "../Usuario/Usuario.h"
#include <iostream>
#include <random>
#include <string>
#include <chrono>
using namespace std;

class RentaActivo {

private:
    string idTransaccion;
    string idActivo; // Del activo que se rentó
    Usuario *usuario;
    string fechaRenta;
    string diasRentado;

    string generarID();

public:
    //Getters de todo
    RentaActivo(string idActivo, Usuario *usuario, string fechaRenta, string diasRentado);
    ~RentaActivo();
    int getIdTransaccion();
    int getIdActivo();
    Usuario *getUsuario();
    string getFechaRenta();
    string getDiasRentado();

    // Implementar metodos de la clase
    void mostrarDetalles();


};



#endif //RENTAACTIVO_H
