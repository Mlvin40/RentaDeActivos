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
    archivo << "    rankdir=LR;\n"; // Configuración para orientación izquierda-derecha
    archivo << "    node [shape=record, style=filled, fillcolor=lightblue];\n";

    // Comienza recorriendo desde el primer nodo
    NodoDoble<RentaActivo>* nodo = lista->getInicio();

    // Recorre todos los nodos de la lista hasta que siguiente sea nullptr
    while (nodo != nullptr) {
        archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" [label=\""
                << nodo->getValor()->mostrarDetalles() << "\"];\n";

        // Conexión hacia adelante (si el siguiente nodo existe)
        if (nodo->getSiguiente() != nullptr) {
            archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" -> \""
                    << nodo->getSiguiente()->getValor()->getIdTransaccion() << "\";\n";
        }

        // Conexión hacia atrás (si el nodo anterior existe)
        if (nodo->getAnterior() != nullptr) {
            archivo << "    \"" << nodo->getValor()->getIdTransaccion() << "\" -> \""
                    << nodo->getAnterior()->getValor()->getIdTransaccion() << "\" [dir=back];\n";
        }

        // Avanzar al siguiente nodo
        nodo = nodo->getSiguiente();
    }

    archivo << "}\n";
    archivo.close();

    std::cout << "Reporte de transacciones generado exitosamente: reporte_transacciones.dot" << std::endl;
}