//
// Created by melvin on 19/12/24.
//

#include "../../includes/Transacciones/RentaActivo.h"

RentaActivo::RentaActivo(string idActivo, Usuario *usuario, string fechaRenta, string diasRentado) {
    this->idTransaccion = generarID();
    this->idActivo = idActivo;
    this->usuario = usuario;
    this->fechaRenta = fechaRenta;
    this->diasRentado = diasRentado;
}

RentaActivo::~RentaActivo() {
}

string RentaActivo::generarID(){

    // Semilla basada en el tiempo actual
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Generador de números aleatorios
    std::mt19937 generator(seed);

    // Distribución uniforme [0, 9]
    std::uniform_int_distribution<int> distribucion(0, 9);

    std::string id;
    for (int i = 0; i < 15; i++) {
        id += std::to_string(distribucion(generator)); // Genera un dígito y lo agrega al ID
    }
    return id;
}

int RentaActivo::getIdTransaccion() {
    return std::stoi(this->idTransaccion);
}

int RentaActivo::getIdActivo() {
    return std::stoi(this->idActivo);
}

Usuario *RentaActivo::getUsuario() {
    return this->usuario;
}

string RentaActivo::getFechaRenta() {
    return this->fechaRenta;
}

string RentaActivo::getDiasRentado() {
    return this->diasRentado;
}

void RentaActivo::mostrarDetalles() {
    cout << "ID Transaccion: " << this->idTransaccion << endl;
    cout << "ID Activo: " << this->idActivo << endl;
    cout << "Usuario: " << this->usuario->getNombre() << endl;
    cout << "Departamento: " << this->usuario->getDepartamento() << endl;
    cout << "Empresa: " << this->usuario->getEmpresa() << endl;
    cout << "Fecha de renta: " << this->fechaRenta << endl;
    cout << "Dias rentado: " << this->diasRentado << endl;
}