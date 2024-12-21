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

    /********************************************************************************************************************
     * Si ya existen las cabeceras se inserta el valor en las cabeceras existentes
     * *****************************************************************************************************************/
    NodoMatriz *existente = buscarNodo(departamento, empresa);
    if (existente != nullptr) {
        cout<<"El usuario: "<<valor<<"Se agregara adelante o atras del usuario: "<<existente->valor<<endl;
        cout<<"1. Adelante"<<endl;
        cout<<"2. Atras"<<endl;
        int opcion;
        cin>>opcion;
        if (opcion == 1)
        {
            // Insertar en la dimensión "adelante"
            insertarAdelante(existente, valor);
            return;
        } else{
            // Insertar en la dimensión "atras"
            insertarAtras(existente, valor);
            return;
        }
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

NodoMatriz *MatrizDispersa::buscarNodo(string departamento, string empresa) {
    NodoMatriz *auxiliarEmpresa = nodoCabeceraVertical;

    //Recorrer la lista de cabeceras verticales hasta que encuetre uno con el nombre de la empresa
    while (auxiliarEmpresa != nullptr){
        if (auxiliarEmpresa->valor == empresa)
        {
            //Ahora realizar un while hasta su ultimo nodo siguiente e ir comparando con el departamento
            NodoMatriz *auxiliarDepartamento = auxiliarEmpresa->siguiente;
            while (auxiliarDepartamento != nullptr){
                if (llegarCabeceraHorizontal(auxiliarDepartamento)->valor == departamento)
                {
                    return auxiliarDepartamento;
                }
                auxiliarDepartamento = auxiliarDepartamento->siguiente;
            }
        }
        auxiliarEmpresa = auxiliarEmpresa->abajo;
    }
    return nullptr;
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

/*******************************************************************************************************************
 * Metodo para insertar un valor en las cabeceras que ya existen
 * *****************************************************************************************************************/

void MatrizDispersa::insertarAdelante(NodoMatriz *usuarioExistente, string nuevoUsuario) {
    // Crear el nuevo nodo
    NodoMatriz *nuevoNodo = new NodoMatriz(nuevoUsuario);

    // Conectar el nuevo nodo con el existente en la dimensión adelante-atras
    nuevoNodo->atras = usuarioExistente;
    nuevoNodo->adelante = usuarioExistente->adelante;

    // Si hay un nodo adelante, actualizar su referencia hacia atrás
    if (usuarioExistente->adelante != nullptr) {
        usuarioExistente->adelante->atras = nuevoNodo;
    }

    // Actualizar la referencia del nodo existente hacia adelante
    usuarioExistente->adelante = nuevoNodo;

    // El nuevo nodo copia las referencias del nodo existente en las demás dimensiones
    nuevoNodo->siguiente = usuarioExistente->siguiente;
    nuevoNodo->anterior = usuarioExistente->anterior;
    nuevoNodo->arriba = usuarioExistente->arriba;
    nuevoNodo->abajo = usuarioExistente->abajo;

    //Limpiar las referencias del nodo que se va para atras
    usuarioExistente->siguiente = nullptr;
    usuarioExistente->anterior = nullptr;
    usuarioExistente->arriba = nullptr;
    usuarioExistente->abajo = nullptr;

    // Actualizar las referencias de los nodos vecinos (si existen) para apuntar al nuevo nodo
    if (nuevoNodo->siguiente != nullptr) {
        nuevoNodo->siguiente->anterior = nuevoNodo;
    }
    if (nuevoNodo->anterior != nullptr) {
        nuevoNodo->anterior->siguiente = nuevoNodo;
    }
    if (nuevoNodo->arriba != nullptr) {
        nuevoNodo->arriba->abajo = nuevoNodo;
    }
    if (nuevoNodo->abajo != nullptr) {
        nuevoNodo->abajo->arriba = nuevoNodo;
    }
}

void MatrizDispersa::insertarAtras(NodoMatriz *usuarioExistente, string nuevoUsuario) {

    NodoMatriz *nuevoNodo = new NodoMatriz(nuevoUsuario);

    if (usuarioExistente->atras == nullptr) {
        // Si no hay nodos atrás, enlazar directamente
        usuarioExistente->atras = nuevoNodo;
        nuevoNodo->adelante = usuarioExistente;
    } else {
        // Si ya hay nodos atrás, recorrer hasta el inicio
        NodoMatriz *aux = usuarioExistente->atras;
        while (aux->atras != nullptr) {
            aux = aux->atras;
        }
        aux->atras = nuevoNodo;
        nuevoNodo->adelante = aux;
    }

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
    } // Finalizacion del encuadre

    //Relaciones de los usuarios a todas las posibles direcciones
    auxiliarEmpresa = nodoCabeceraVertical;
    auxiliarUsuario = nullptr;

    while (auxiliarEmpresa != nullptr){
        auxiliarUsuario = auxiliarEmpresa->siguiente;

        //hacer el primer enlace
        archivo << auxiliarEmpresa->valor << " -> " << auxiliarUsuario->valor << ";\n";
        archivo << auxiliarUsuario->valor << " -> " << auxiliarEmpresa->valor << ";\n";
        while (auxiliarUsuario != nullptr){

            //Ver hacia siguiente, anterior, arriba y abajo
            if (auxiliarUsuario->siguiente != nullptr){
                archivo << auxiliarUsuario->valor << " -> " << auxiliarUsuario->siguiente->valor << ";\n";
                archivo << auxiliarUsuario->siguiente->valor << " -> " << auxiliarUsuario->valor << ";\n";
            }

            // ver hacia arriba
            if (auxiliarUsuario->arriba != nullptr){
                archivo << auxiliarUsuario->valor << " -> " << auxiliarUsuario->arriba->valor << ";\n";
                archivo << auxiliarUsuario->arriba->valor << " -> " << auxiliarUsuario->valor << ";\n";
            }
            //salto de linea
            archivo << "\n";

            auxiliarUsuario = auxiliarUsuario->siguiente;
        }// FIN DE LOS ENLACES DE LOS USUARIOS

        auxiliarEmpresa = auxiliarEmpresa->abajo;
    } // Finalizacion del encuadre
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

    std::string comando = "dot -Tpdf " + nombreArchivo + " -o " + nombreArchivo + ".pdf";
    int resultado = system(comando.c_str());
    if (resultado == 0) {
        std::cout << "Archivo PDF creado exitosamente: " << nombreArchivo << ".pdf" << std::endl;
    } else {
        std::cerr << "Error al crear el archivo PDF. Asegúrate de tener Graphviz instalado y en el PATH del sistema." << std::endl;
    }

}
