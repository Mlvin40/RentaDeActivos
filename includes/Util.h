//
// Created by melvin on 20/12/24.
//

#ifndef UTIL_H
#define UTIL_H

#include "../includes/ListaDoble/ListaDobleEnlazada.h"
#include "../includes/Transacciones/RentaActivo.h"
class Util {

public:
    bool rentarActivo();
    void generarReporteTransacciones(ListaDobleEnlazada<RentaActivo>* lista);

};



#endif //UTIL_H
