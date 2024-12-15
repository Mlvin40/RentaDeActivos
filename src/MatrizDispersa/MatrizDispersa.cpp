//
// Created by melvin on 12/12/24.
//

#include "../../includes/MatrizDispersa/MatrizDispersa.h"
#include <fstream>
#include <cstdlib> // Para ejecutar comandos del sistema

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

    NodoMatriz *nuevoUsuario = new NodoMatriz(valor);

    //Inicializar las cabeceras horizontales y verticales
    NodoMatriz *cabeceraH = nullptr;
    NodoMatriz *cabeceraV = nullptr;

    //Cuando la matriz esta vacia se inserta el primer nodo entre las cabeceras
    if (estaVacia())
    {
        cabeceraH = insertarCabeceraHorizontal(departamento);
        cabeceraV = insertarCabeceraVertical(empresa);
        insertarAlFinal(nuevoUsuario, cabeceraH, cabeceraV);
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
        insertarAlFinal(nuevoUsuario, cabeceraH, cabeceraV);
        return;
    }

    if (cabeceraH == nullptr)
    {
        cabeceraH = insertarCabeceraHorizontal(departamento);

        insertarAlFinal(nuevoUsuario, cabeceraH, nodoCabeceraVertical);
        return;
    }

    if (cabeceraV == nullptr)
    {
        cabeceraV = insertarCabeceraVertical(empresa);
        insertarAlFinal(nuevoUsuario, nodoCabeceraHorizontal, cabeceraV);
        return;
    }

    // si ya existen las cabeceras se inserta el valor en las cabeceras existentes
    //insertarValorCabecerasExistentes(nuevoUsuario, departamento, empresa);

    NodoMatriz *auxiliarH = cabeceraH->abajo;
    NodoMatriz *usuarioCabV;
    bool abajo = false;

    while (auxiliarH != nullptr){
        usuarioCabV = llegarCabeceraVertical(auxiliarH);

        //Bandera que sirve para saber si el usuario esta mas abajo viendo su empresa asignada
        //Departamento
        abajo = masAbajo(usuarioCabV, empresa);

        if (!abajo) break;
        auxiliarH = auxiliarH->abajo;

    }
    if (abajo)
    {
        insertarAlFinalHorizontal(nuevoUsuario, cabeceraH);
    }else
    {
        insertarAlMedioVertical(nuevoUsuario, auxiliarH);
    }

    //********************************************************************************************************************
    NodoMatriz *auxiliarV = cabeceraV->siguiente;
    NodoMatriz *usuarioCabH;
    bool siguiente = false;

    while (auxiliarV != nullptr){
        usuarioCabH = llegarCabeceraHorizontal(auxiliarV);
        //Bandera que sirve para saber si el usuario esta mas a la derecha viendo su departamento asignado
        siguiente = masDerecha(usuarioCabH, departamento);

        if (!siguiente) break;
        auxiliarV = auxiliarV->siguiente;

    }

    if (siguiente)
    {
        insertarAlFinalVertical(nuevoUsuario, cabeceraV);
    }else{
        insertarAlMedioVertical(nuevoUsuario, auxiliarV);
    }
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
void MatrizDispersa::insertarAlFinal(NodoMatriz *usuarioNuevo, NodoMatriz* cabezaHorizontal, NodoMatriz* cabezaVertical){

    //Metodo separado para enlazar un nodo horizontal y vertical
    insertarAlFinalHorizontal(usuarioNuevo, cabezaHorizontal);
    insertarAlFinalVertical(usuarioNuevo, cabezaVertical);

}
// Funciones para insertar al final de manera horizontal y en medio de manera vertical ****************************************************

void MatrizDispersa::insertarAlFinalHorizontal(NodoMatriz *usuarioNuevo, NodoMatriz *nodoHorizontal) {
    NodoMatriz *auxiliar = nodoHorizontal;

    while (auxiliar->abajo != nullptr){
        auxiliar = auxiliar->abajo;
    }
    auxiliar->abajo = usuarioNuevo;
    usuarioNuevo->arriba = auxiliar;
}

void MatrizDispersa::insertarAlFinalVertical(NodoMatriz *usuarioNuevo, NodoMatriz *nodoVertical) {

    NodoMatriz *auxiliar = nodoVertical;
    while (auxiliar->siguiente != nullptr){
        auxiliar = auxiliar->siguiente;
    }

    auxiliar->siguiente = usuarioNuevo;
    usuarioNuevo->anterior = auxiliar;
}

void MatrizDispersa::insertarAlMedioVertical(NodoMatriz *usuarioNuevo, NodoMatriz *vertical) {

    //Cambia el apuntador de abajo del nodo anterior
    vertical ->anterior->siguiente = usuarioNuevo;
    usuarioNuevo->siguiente = vertical;
    usuarioNuevo->anterior = vertical->anterior;
    vertical->anterior = usuarioNuevo;
}

void MatrizDispersa::insertarAlMedioHorizontal(NodoMatriz *usuarioNuevo, NodoMatriz *horizontal) {

    //acualizar todos los apuntadores de los nodo
    horizontal->arriba->abajo = usuarioNuevo;
    usuarioNuevo->abajo = horizontal;
    usuarioNuevo->arriba = horizontal->arriba;
    horizontal->arriba = usuarioNuevo;

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

bool MatrizDispersa::masAbajo(NodoMatriz *cabeceraV, string valor){
    NodoMatriz *auxiliar = cabeceraV;

    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return true;
        }
        auxiliar = auxiliar->abajo;
    }

    return false;
}

bool MatrizDispersa::masDerecha(NodoMatriz *cabeceraH, string valor) {
    NodoMatriz *auxiliar = cabeceraH;

    while (auxiliar != nullptr){
        if (auxiliar->valor == valor)
        {
            return true;
        }
        auxiliar = auxiliar->siguiente;
    }
    return false;
}

//********************************************************************************************************************
//********************************************************************************************************************

// Definición de la función graficarMatriz
void MatrizDispersa::graficarMatriz(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para crear el grafo." << std::endl;
        return;
    }

    //IMPLMENETACION DE LA GRAFICA
    archivo << "digraph G {\n";
    archivo << "    node [shape=box];\n";
    archivo << "    n0 [label = \"admin\" group=1];\n";

    //Departamentos
    NodoMatriz *auxiliarH = nodoCabeceraHorizontal;
    int contador=1;
    while (auxiliarH != nullptr){
        contador++;
        archivo << auxiliarH->valor << "[label = \"" << auxiliarH->valor << "\" group=" << contador << "];\n";
        auxiliarH->nivel = contador;
        auxiliarH = auxiliarH->siguiente;
    }
    contador = 1; // se reinicia el contador

    //Relaciones de los departamentos usando siguiete
    NodoMatriz *primerDepa = nodoCabeceraHorizontal;
    archivo<< "n0 -> " << primerDepa->valor << ";\n";

    while (primerDepa->siguiente != nullptr){
        archivo << primerDepa->valor << " -> " << primerDepa->siguiente->valor << ";\n";
        primerDepa = primerDepa->siguiente;
        if (primerDepa->anterior != nullptr){
            archivo << primerDepa->valor << " -> " << primerDepa->anterior->valor << ";\n";
        }
    }
    //Empresas
    NodoMatriz *auxiliarV = nodoCabeceraVertical;
    while (auxiliarV != nullptr){
        archivo << auxiliarV->valor << "[label = \"" << auxiliarV->valor << "\" group=" << contador << "];\n";
        auxiliarV = auxiliarV->abajo;
    }

    //Relaciones de las empresas usando abajo
    NodoMatriz *primerEmpresa = nodoCabeceraVertical;
    archivo << "n0 -> " << primerEmpresa->valor << ";\n";
    while (primerEmpresa->abajo != nullptr){
        archivo << primerEmpresa->valor << " -> " << primerEmpresa->abajo->valor << ";\n";
        primerEmpresa = primerEmpresa->abajo;
        if (primerEmpresa->arriba != nullptr){
            archivo << primerEmpresa->valor << " -> " << primerEmpresa->arriba->valor << ";\n";
        }
    }

    //agrupar todos los departamentos con rank=same
    auxiliarH = nodoCabeceraHorizontal;
    archivo << "{rank=same; n0; ";
    while (auxiliarH != nullptr){
        archivo << auxiliarH->valor << "; ";
        auxiliarH = auxiliarH->siguiente;
    }
    archivo << "}\n";
    archivo << "\n";

    // HASTA AQUI TODO BIEN

    //Ahora en base a los siguiente de las empresas se crean los usuarios
    NodoMatriz *auxiliarEmpresa = nodoCabeceraVertical;
    NodoMatriz *auxiliarUsuario;
    while (auxiliarEmpresa != nullptr){
        auxiliarUsuario = auxiliarEmpresa;
        while (auxiliarUsuario != nullptr){
            if (auxiliarUsuario->arriba == nullptr)
            {
                //aqui automaticamente el nivel es 1
                archivo << auxiliarUsuario->valor << "[label = \"" << auxiliarUsuario->valor << "\" group=1"<< "];\n";
            }else
            {
                auxiliarUsuario->nivel = auxiliarUsuario->arriba->nivel; // Para copiar el nivel del departamento
                archivo << auxiliarUsuario->valor << "[label = \"" << auxiliarUsuario->valor << "\" group=" << auxiliarUsuario->arriba->nivel << "];\n";
            }
                auxiliarUsuario = auxiliarUsuario->siguiente;
        }
        auxiliarEmpresa = auxiliarEmpresa->abajo;
    } // final de creacion de los nodos con sus niveles

    // Alinear desde el primer departamento hasta su ultimo usuario asignado
    auxiliarEmpresa = nodoCabeceraVertical;
    auxiliarUsuario = nullptr;

    while (auxiliarEmpresa != nullptr){
        auxiliarUsuario = auxiliarEmpresa;
        archivo << "{rank=same;";
        while (auxiliarUsuario != nullptr){
            archivo << auxiliarUsuario->valor << "; ";
            auxiliarUsuario = auxiliarUsuario->siguiente;
        }
        archivo << "}\n";
        archivo << "\n";
        auxiliarEmpresa = auxiliarEmpresa->abajo;
    }

    //Aqui cierra el reporte
    archivo << "}\n";
    archivo.close();

    std::cout << "Archivo DOT creado exitosamente: " << nombreArchivo << std::endl;

    // Verificar si el archivo DOT se creó correctamente
    std::ifstream pruebaArchivo(nombreArchivo);
    if (!pruebaArchivo.is_open()) {
        std::cerr << "El archivo DOT no se ha creado correctamente." << std::endl;
        return;
    }
    pruebaArchivo.close();

    std::cout << "Ahora puedes usar Graphviz para generar la imagen usando el archivo DOT." << std::endl;
    std::cout << "Ejemplo de comando: dot -Tpng " << nombreArchivo << " -o grafo.png" << std::endl;
}
