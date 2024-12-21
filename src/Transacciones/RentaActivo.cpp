//
// Created by melvin on 19/12/24.
//

#include "../../includes/Transacciones/RentaActivo.h"

RentaActivo::RentaActivo(NodoAVL *activo, Usuario *usuario, string diasRentado) {
    this->idTransaccion = generarID();
    this->activo = activo;
    this->usuario = usuario;
    this->fechaRenta = obtenerFechaActual();
    this->diasRentado = diasRentado;
}

RentaActivo::~RentaActivo() {
}

NodoAVL* RentaActivo::getActivo() {
    return this->activo;
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

Usuario *RentaActivo::getUsuario() {
    return this->usuario;
}

string RentaActivo::getFechaRenta() {
    return this->fechaRenta;
}

string RentaActivo::getDiasRentado() {
    return this->diasRentado;
}

std::string RentaActivo::mostrarDetalles() {
    std::ostringstream detalles; // Usamos un ostringstream para construir el string

    detalles << "ID Transaccion: " << this->idTransaccion << "\n";
    detalles << "ID Activo: " << this->activo->getValor() << "\n";
    detalles << "Usuario: " << this->usuario->getNombre() << "\n";
    detalles << "Departamento: " << this->usuario->getDepartamento() << "\n";
    detalles << "Empresa: " << this->usuario->getEmpresa() << "\n";
    detalles << "Fecha de renta: " << this->fechaRenta << "\n";
    detalles << "Dias rentado: " << this->diasRentado << "\n";

    return detalles.str();
}

void RentaActivo::mostrarEnLinea()
{
    std::cout << "ID Activo: " << this->activo->getValor() << " | "
              << "NOMBRE : " << this->activo->getNombreActivo() << " | "
              << "Dias rentado: " << this->diasRentado << std::endl;
}

// Obtener la fecha actual en formato YYYY-MM-DD
std::string RentaActivo::obtenerFechaActual() {
    std::time_t t = std::time(nullptr);
    std::tm* ahora = std::localtime(&t);

    // Crear un stringstream para formatear la fecha
    std::ostringstream fechaStream;
    fechaStream << (ahora->tm_year + 1900) << "-"   // Año
                << (ahora->tm_mon + 1) << "-"       // Mes
                << ahora->tm_mday;                 // Día

    return fechaStream.str();
}
