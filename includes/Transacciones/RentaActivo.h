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
#include <ctime>
#include <sstream>
using namespace std;

class RentaActivo {

private:
    string idTransaccion;
    NodoAVL* activo; // Del activo que se renta
    Usuario *usuario;
    string fechaRenta;
    string diasRentado;

    string generarID();
    string obtenerFechaActual();

public:
    //Getters de todo
    RentaActivo(NodoAVL *activo, Usuario *usuario, string diasRentado);
    ~RentaActivo();
    string getIdTransaccion();
    Usuario *getUsuario();
    string getFechaRenta();
    string getDiasRentado();
    NodoAVL* getActivo();
    void mostrarEnLinea();

    // Implementar metodos de la clase
    std::string mostrarDetalles();
    void informacionDeTransaccion();


};



#endif //RENTAACTIVO_H
