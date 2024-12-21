//
// Created by melvin on 20/12/24.
//

#include "../includes/Util.h"
#include <fstream>
#include <sstream>

void Util::generarReporteTransacciones(ListaDobleEnlazada<RentaActivo>* lista) {
    std::ofstream archivo("reporte_transacciones.dot");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el reporte." << std::endl;
        return;
    }

    archivo << "digraph Transacciones {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [shape=none, margin=0];\n"; // Configuración para usar etiquetas HTML

    NodoDoble<RentaActivo>* nodo = lista->getInicio();

    while (nodo != nullptr) {
        std::string detalles = nodo->getValor()->mostrarDetalles();

        archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" [label=<"
                << detalles << ">];\n";
        nodo = nodo->getSiguiente();
    }

    nodo = lista->getInicio();
    while (nodo->getSiguiente() != nullptr) {

        if (nodo->getSiguiente() != nullptr) {
            archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" -> \""
                    << nodo->getSiguiente()->getValor()->getIdTransaccion() << "\";\n";
        }

        if (nodo->getAnterior() != nullptr) {
            archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" -> \""
                    << nodo->getAnterior()->getValor()->getIdTransaccion() << "\" \n";
        }
        nodo = nodo->getSiguiente();
    }
    archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" -> \""
                << nodo->getAnterior()->getValor()->getIdTransaccion() << "\" \n";


    archivo << "}\n";
    archivo.close();

    if (!archivo) {
        std::cerr << "Error al crear el archivo DOT." << std::endl;
    } else {
        std::cout << "Reporte de transacciones generado exitosamente: reporte_transacciones.dot" << std::endl;
    }

    int result = system("dot -Tpdf reporte_transacciones.dot -o reporte_transacciones.pdf");
    if (result != 0) {
        std::cerr << "Error al generar el PDF." << std::endl;
    } else {
        std::cout << "PDF generado exitosamente: reporte_transacciones.pdf" << std::endl;
    }
}
