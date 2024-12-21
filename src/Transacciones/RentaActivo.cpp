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

std::string RentaActivo::generarID() {
    // Semilla basada en el tiempo actual (solo se inicializa una vez)
    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    // Distribución uniforme [0, 9]
    std::uniform_int_distribution<int> distribucion(0, 9);

    // Generar un ID de 15 dígitos
    std::string id;
    for (int i = 0; i < 15; i++) {
        id += std::to_string(distribucion(generator)); // Genera un dígito y lo agrega al ID
    }

    // Eliminar espacios en blanco del ID generado
    id.erase(std::remove_if(id.begin(), id.end(), [](unsigned char c) { return std::isspace(c); }), id.end());

    return id;
}


string RentaActivo::getIdTransaccion() {
    return this->idTransaccion;
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
    std::ostringstream detalles;

    // Usamos etiquetas HTML para dar formato al texto
    detalles << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
    detalles << "<TR><TD><B>ID Transaccion:</B></TD><TD>" << this->idTransaccion << "</TD></TR>";
    detalles << "<TR><TD><B>ID Activo:</B></TD><TD>" << this->activo->getValor() << "</TD></TR>";
    detalles << "<TR><TD><B>Usuario Que Rentó:</B></TD><TD>" << this->usuario->getNombre() << "</TD></TR>";
    detalles << "<TR><TD><B>Departamento:</B></TD><TD>" << this->usuario->getDepartamento() << "</TD></TR>";
    detalles << "<TR><TD><B>Empresa:</B></TD><TD>" << this->usuario->getEmpresa() << "</TD></TR>";
    detalles << "<TR><TD><B>Fecha de renta:</B></TD><TD>" << this->fechaRenta << "</TD></TR>";
    detalles << "<TR><TD><B>Dias rentado:</B></TD><TD>" << this->diasRentado << "</TD></TR>";
    detalles << "</TABLE>";

    return detalles.str();
}

void RentaActivo::informacionDeTransaccion() {
    std::cout << "ID Transaccion: " << this->idTransaccion << std::endl;
    std::cout << "ID Activo: " << this->activo->getValor() << std::endl;
    std::cout << "Usuario Que Rentó : " << this->usuario->getNombre() << std::endl;
    std::cout << "Departamento: " << this->usuario->getDepartamento() << std::endl;
    std::cout << "Empresa: " << this->usuario->getEmpresa() << std::endl;
    std::cout << "Fecha de renta: " << this->fechaRenta << std::endl;
    std::cout << "Dias rentado: " << this->diasRentado << std::endl;
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
