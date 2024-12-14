//
// Created by melvin on 12/12/24.
//

#include "../../includes/MatrizDispersa/MatrizDispersa.h"

//Siguiente anterior es de cabeceras horizontales
//Arriba abajo es de cabeceras verticales
//Adelante atras es de nodos de la matriz que representa a los usuarios
//Cada nodo de la matriz tiene un valor y 6 apuntadores


// Constructor de la matriz dispersa que inicializa las cabeceras horizontales y verticales en null
MatrizDispersa::MatrizDispersa() {
    this->nodoCabeceraHorizontal = nullptr;
    this->nodoCabeceraVertical = nullptr;
}
bool MatrizDispersa::estaVacia() {
    if (this->nodoCabeceraHorizontal == nullptr && this->nodoCabeceraVertical == nullptr) {
        return true;
    }
    return false;
}

// Metodo para insertar un valor en la matriz dispersa
// el departamento es la cabecera horizontal y la empresa es la cabecera vertical
void MatrizDispersa::insertarValor(string valor, string departamento, string empresa) {

    //Inicializar las cabeceras horizontales y verticales
    NodoMatriz *cabeceraH = nullptr;
    NodoMatriz *cabeceraV = nullptr;

    //Cuando la matriz esta vacia se inserta el primer nodo entre las cabeceras
    if (estaVacia())
    {
        cabeceraH = insertarCabeceraHorizontal(departamento);
        cabeceraV = insertarCabeceraVertical(empresa);
        insertarAlFinal(valor, cabeceraH, cabeceraV);
        return;
    }

    //Devuelve las cabeceras si ya existe una cabecera con el valor
    cabeceraH = cabeceraHorizontal(departamento);
    cabeceraV = cabeceraVertical(empresa);


    // Si no existen las cabeceras, se insertan las cabeceras y el valor
    if (cabeceraH == nullptr && cabeceraV == nullptr)
    {
        cabeceraH = insertarCabeceraHorizontal(departamento);
        cabeceraV = insertarCabeceraVertical(empresa);
        insertarAlFinal(valor, cabeceraH, cabeceraV);
        return;
    }

    if (cabeceraH == nullptr)
    {
        cabeceraH = insertarCabeceraHorizontal(departamento);

        insertarAlFinal(valor, cabeceraH, nodoCabeceraVertical);
        return;
    }

    if (cabeceraV == nullptr)
    {
        cabeceraV = insertarCabeceraVertical(empresa);
        insertarAlFinal(valor, nodoCabeceraHorizontal, cabeceraV);
        return;
    }

    // si ya existen las cabeceras se inserta el valor en las cabeceras existentes
    insertarValorCabecerasExistentes(valor, departamento, empresa);

}

NodoMatriz *MatrizDispersa::cabeceraHorizontal(string valor) {
    if (estaVacia())
    {
        return nullptr;
    }

    //Recorrer la lista de cabeceras horizontales
    NodoMatriz *auxiliar = nodoCabeceraHorizontal;
    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }
    return nullptr;

}

NodoMatriz *MatrizDispersa::cabeceraVertical(string valor) {
    if (estaVacia())
    {
        return nullptr;
    }
    NodoMatriz *auxiliar = nodoCabeceraVertical;
    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->abajo;
    }
    return nullptr;
}

// Metodo para insertar una cabecera vertical en la matriz dispersa
NodoMatriz *MatrizDispersa::insertarCabeceraHorizontal(string valor) {

    NodoMatriz *nuevaCabecera = new NodoMatriz(valor);

    // si la matriz esta vacia se inserta la cabecera horizontal en la matriz dispersa
    if (this->nodoCabeceraHorizontal == nullptr)
    {
        this->nodoCabeceraHorizontal = nuevaCabecera;
        return nuevaCabecera;
    }

    NodoMatriz *auxiliar = nodoCabeceraHorizontal;

    while (auxiliar->siguiente != nullptr){
        auxiliar = auxiliar->siguiente;
    }

    auxiliar->siguiente = nuevaCabecera;
    nuevaCabecera->anterior = auxiliar;

    return nuevaCabecera;

}

NodoMatriz *MatrizDispersa::insertarCabeceraVertical(string valor) {
    NodoMatriz *nuevaCabecera = new NodoMatriz(valor);

    if (this->nodoCabeceraVertical == nullptr)
    {
        this->nodoCabeceraVertical = nuevaCabecera;
        return nuevaCabecera;
    }

    NodoMatriz *auxiliar = nodoCabeceraVertical;

    while (auxiliar->abajo != nullptr){
        auxiliar = auxiliar->abajo;
    }

    auxiliar->abajo = nuevaCabecera;
    nuevaCabecera->arriba = auxiliar;

    return nuevaCabecera;
}

// Metodo para insertar un valor al final de la matriz dispersa
void MatrizDispersa::insertarAlFinal(string valor, NodoMatriz* cabezaHorizontal, NodoMatriz* cabezaVertical){
    NodoMatriz *usuarioNuevo = new NodoMatriz(valor);

    NodoMatriz *auxiliarHorizontal = cabezaHorizontal;
    NodoMatriz *auxiliarVertical = cabezaVertical;

    while (auxiliarHorizontal->abajo != nullptr){
        auxiliarHorizontal = auxiliarHorizontal->abajo;
    }

    // con esto se llega al ultimo nodo de la cabecera horizontal
    auxiliarHorizontal-> abajo = usuarioNuevo;
    usuarioNuevo->arriba = auxiliarHorizontal;

    while (auxiliarVertical->siguiente != nullptr){
        auxiliarVertical = auxiliarVertical->siguiente;
    }

    auxiliarVertical->siguiente = usuarioNuevo;
    usuarioNuevo->anterior = auxiliarVertical;

}

// Funciones para insertar al final de manera horizontal y en medio de manera vertical ****************************************************

void MatrizDispersa::insertarAlFinalVertical(string valor, NodoMatriz *nodoHorizontal) {

}

void MatrizDispersa::insertarAlMedio(string valor, NodoMatriz *nodoVertical) {


}

// Metodo para llegar a la cabecera horizontal
NodoMatriz *MatrizDispersa::llegarCabeceraHorizontal(NodoMatriz *nodo) {
    NodoMatriz *auxiliar = nodo;

    while (auxiliar->arriba != nullptr){
        auxiliar = auxiliar->arriba;
    }
    return auxiliar;
}

// Metodo para llegar a la cabecera vertical
NodoMatriz *MatrizDispersa::llegarCabeceraVertical(NodoMatriz *nodo) {
    NodoMatriz *auxiliar = nodo;

    while (auxiliar->anterior != nullptr){
        auxiliar = auxiliar->anterior;
    }
    return auxiliar;
}

void MatrizDispersa::insertarValorCabecerasExistentes(string valor, string departamento, string institucion) {
    NodoMatriz *auxiliarHorizontal = this->nodoCabeceraHorizontal;
    NodoMatriz *auxiliarVertical = this->nodoCabeceraVertical;
    NodoMatriz *nuevoUsuario = new NodoMatriz(valor);

    // **Paso 1: Encontrar cabeceras**
    // Buscar la cabecera horizontal (por departamento)
    while (auxiliarHorizontal != nullptr && auxiliarHorizontal->valor != departamento) {
        auxiliarHorizontal = auxiliarHorizontal->siguiente;
    }

    // Buscar la cabecera vertical (por institución)
    while (auxiliarVertical != nullptr && auxiliarVertical->valor != institucion) {
        auxiliarVertical = auxiliarVertical->abajo;
    }

    // Verificar si ambas cabeceras existen
    if (auxiliarHorizontal == nullptr || auxiliarVertical == nullptr) {
        std::cerr << "Error: No se encontraron las cabeceras especificadas.\n";
        return;
    }

    // **Paso 2: Ajustar enlaces horizontales**
    NodoMatriz *horizontalActual = auxiliarVertical;  // Partir desde la cabecera vertical

    // Buscar el nodo "Max" en la fila horizontal
    while (horizontalActual->siguiente != nullptr && horizontalActual->siguiente->valor != "Usuario4") {
        horizontalActual = horizontalActual->siguiente;
    }

    // **Actualizar enlaces para insertar Usuario5**
    NodoMatriz *anteriorMax = horizontalActual; // Nodo "Max"
    NodoMatriz *usuario4 = anteriorMax->siguiente; // Nodo "Usuario4"

    // Ajustar punteros
    anteriorMax->siguiente = nuevoUsuario; // Max -> Usuario5
    nuevoUsuario->anterior = anteriorMax; // Usuario5 <- Max
    nuevoUsuario->siguiente = usuario4;  // Usuario5 -> Usuario4

    if (usuario4 != nullptr) {
        usuario4->anterior = nuevoUsuario; // Usuario4 <- Usuario5
    }

    // **Paso 3: Ajustar enlaces verticales (si aplica)**
    NodoMatriz *verticalActual = auxiliarHorizontal; // Partir desde la cabecera horizontal
    while (verticalActual->abajo != nullptr && verticalActual->abajo->valor < valor) {
        verticalActual = verticalActual->abajo;
    }

    // Insertar el nuevo usuario en la columna vertical
    nuevoUsuario->abajo = verticalActual->abajo;
    if (verticalActual->abajo != nullptr) {
        verticalActual->abajo->arriba = nuevoUsuario;
    }
    verticalActual->abajo = nuevoUsuario;
    nuevoUsuario->arriba = verticalActual;
}





