//
// Created by melvin on 19/12/24.
//

#include <iostream>
#include <cstdlib>
#include "../includes/Controlador.h"

#include <bits/posix2_lim.h>
using namespace std;

Controlador::Controlador() {
    this->matrizDispersa = new MatrizDispersa();
    this->listaUsuarios = new ListaDobleEnlazada<Usuario>();
    this->listaTransacciones = new ListaDobleEnlazada<RentaActivo>();
    this->usuarioLogueado = nullptr;
    this->util = new Util();
    usuariosGrabados();
}

void Controlador::iniciarSistema() {
    bool sistemaActivo = true;

    while (sistemaActivo) {
        separador();
        // Mostrar el menú de opciones al usuario
        cout << "Seleccione una opción:" << endl;
        cout << "1. Iniciar sesión" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 0:
                cout << "Gracias por usar el sistema. ¡Hasta luego!" << endl;
            sistemaActivo = false;
            break;

        case 1:
                iniciarLogin();
            break;

        default:
                cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    }
}

void Controlador::iniciarLogin(){

    std::string usernameIngresado;
    std::string contrasenaIngresada;
    bool loginExitoso = false;

    while (!loginExitoso) {
        separador();
        std::cout << "Ingrese su nombre de usuario: ";
        std::cin >> usernameIngresado;

        std::cout << "Ingrese su contrasena: ";
        std::cin >> contrasenaIngresada;

        // Si fue el administrador
        if (usernameIngresado == "admin" && contrasenaIngresada == "admin") {
            loginExitoso = true;
            usuarioLogueado = nullptr;
            break;
        }

        // Verificamos si el usuario existe
        for (int i = 0; i < listaUsuarios->getTamano(); ++i) {
            Usuario* user = listaUsuarios->obtenerContenido(i);

            if (user->getUsername() == usernameIngresado && user->verificarContrasena(contrasenaIngresada)) {
                usuarioLogueado = user;
                loginExitoso = true;
                break;
            }
        }

        if (!loginExitoso) {
            std::cout << "Credenciales incorrectas. Intente nuevamente." << std::endl;
        }
    }

    // Verificar si es administrador o no
    if (usernameIngresado == "admin") {
        iniciarMenuAdministrador();
    } else {
        iniciarMenuUsuario();
    }
}

//********************************************************************************************************************
//****************************** LOGICA PARA EL USUARIO ADMINISTRADOR ************************************************
//********************************************************************************************************************

void Controlador::iniciarMenuAdministrador() {
    bool continuar = true;
    while (continuar) {
        cout << "%%%%%%%%%%%%%%%%%%% Menú Administrador %%%%%%%%%%%%%%%%%%%" << endl;
        cout << "%% 1. Registrar Usuario" << endl;
        cout << "%% 2. Reporte Matriz Dispersa" << endl;
        cout << "%% 3. Reporte Activos Disponibles de un Departamento" << endl;
        cout << "%% 4. Reporte Activos Disponibles de una Empresa" << endl;
        cout << "%% 5. Reporte Transacciones" << endl;
        cout << "%% 6. Reporte Activos de un Usuario" << endl;
        cout << "%% 7. Activos rentados por un Usuario" << endl;
        cout << "%% 8. Ordenar Transacción" << endl;
        cout << "%% 0. Salir" << endl;
        cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        cout << "Ingresar Opción: ";

        int opcion;
        cin >> opcion;

        // Validar si la entrada es un número entero válido o no para evitar errores
        if (cin.fail()) {
            cout << "Entrada no válida. Por favor, ingrese un número." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 0:
                continuar = false;
                cout << "Cerrando sesión de Administrador..." << endl;
                break;
            case 1:
                registrarUsuario();
                break;
            case 2:
                reporteMatrizDispersa();
                break;
            case 3:
                reporteActivosDisponiblesDepartamento();
                break;
            case 4:
                reporteActivosDisponiblesEmpresa();
                break;
            case 5:
                reporteTransacciones();
                break;
            case 6:
                reporteActivosUsuario();
                break;
            case 7:
                activosRentadosUsuario();
                break;
            case 8:
                ordenarTransaccion();
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }

        if (continuar) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }
}


void Controlador::registrarUsuario(){
    Usuario* nuevoUsuario;
    string username, nombre, contrasena, departamento, empresa;

    cout << "Ingrese el nombre de usuario: ";
    cin >> username;
    cin.ignore(); // Limpiar el buffer para evitar problemas con getline

    cout << "Ingrese el nombre completo: ";
    getline(cin, nombre);

    cout << "Ingrese la contraseña: ";
    cin >> contrasena;

    cout << "Ingrese el departamento: ";
    cin.ignore();
    getline(cin, departamento);

    cout << "Ingrese la empresa: ";
    getline(cin, empresa);

    nuevoUsuario = new Usuario(username, nombre, contrasena, departamento, empresa);
    matrizDispersa->insertarValor(username, departamento, empresa);
    listaUsuarios->agregarElemento(nuevoUsuario);

    cout << "Usuario registrado exitosamente." << endl;
}

void Controlador::reporteMatrizDispersa(){
    matrizDispersa->graficarMatriz("matriz.dot");
}

void Controlador::reporteActivosDisponiblesDepartamento()
{
    //Pedir el departamento
    cout << "Ingrese el departamento: ";
    string departamento;
    cin >> departamento;

    //Recorrer la lista de usuarios e ir comparando cuales tienen el mismo departamento
    for (int i = 0; i < listaUsuarios->getTamano(); ++i) {
        Usuario* user = listaUsuarios->obtenerContenido(i);

        if (user->getDepartamento() == departamento) {
            cout << "Usuario: " << user->getNombre() << endl;
            cout << "Empresa: " << user->getEmpresa() << endl;
            user->getArbol()->recorrerArbol();
            cout <<"\n"<<endl;
        }
    }

}

void Controlador::reporteActivosDisponiblesEmpresa()
{
    // Pedir la empresa
    cout << "Ingrese la empresa: ";
    string empresa;
    cin >> empresa;

    //Recorrer la lista de usuarios e ir comparando cuales tienen la misma empresa
    for (int i = 0; i < listaUsuarios->getTamano(); ++i) {
        Usuario* user = listaUsuarios->obtenerContenido(i);

        if (user->getEmpresa() == empresa) {
            cout << "Usuario: " << user->getNombre() << endl;
            cout << "Empresa: " << user->getEmpresa() << endl;
            user->getArbol()->recorrerArbol();
            cout <<"\n"<<endl;
        }
    }
}

void Controlador::reporteTransacciones()
{
    util->generarReporteTransacciones(listaTransacciones);
}

void Controlador::reporteActivosUsuario()
{
    //Pedir el nombre del usuario del que se desea ver los activos
    cout << "Ingrese el nombre de usuario: ";
    string username;
    cin >> username;

    //Recorrer la lista de usuarios e ir comparando cual tiene el mismo nombre de usuario
    for (int i = 0; i < listaUsuarios->getTamano(); ++i) {
        Usuario* user = listaUsuarios->obtenerContenido(i);

        if (user->getUsername() == username) {
            user->getArbol()->graficarArbol();
        }
    }

}

void Controlador::activosRentadosUsuario()
{
    // Pedir el nombre del usuario del que se desea ver los activos rentados
    cout << "Ingrese el nombre de usuario: ";
    string username;
    cin >> username;
     //Recorrer la lista de transacciones e ir comparando cual tiene el mismo nombre de usuario
    for (int i = 0; i < listaTransacciones->getTamano(); ++i) {
        RentaActivo* transaccion = listaTransacciones->obtenerContenido(i);

        if (transaccion->getUsuario()->getUsername() == username){
            transaccion->informacionDeTransaccion();
        }
    }
}

void Controlador::ordenarTransaccion()
{
    cout<<"Ordenando transacciones..."<<endl;
}

//********************************************************************************************************************
//****************************** LOGICA PARA EL USUARIO NORMAL *******************************************************
//********************************************************************************************************************

void Controlador::iniciarMenuUsuario() {
    bool continuar = true;
    while (continuar) {
        cout << "%%%%%%%%%%%%%%%%%%% " << usuarioLogueado->getNombre() << " %%%%%%%%%%%%%%%%%%%" << endl;
        cout << "%% 1. Agregar Activo" << endl;
        cout << "%% 2. Eliminar Activo" << endl;
        cout << "%% 3. Modificar Activo" << endl;
        cout << "%% 4. Rentar Activo" << endl;
        cout << "%% 5. Activos Rentados" << endl;
        cout << "%% 6. Mis Activos Rentados" << endl;
        cout << "%% 7. Cerrar Sesión" << endl;
        cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        cout << "Ingresar Opción: ";

        int opcion;
        cin >> opcion;

        // Validar si la entrada es un número entero válido o no para evitar errores
        if (cin.fail()) {
            cout << "Entrada no válida. Por favor, ingrese un número." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
        case 7:
            continuar = false;
            cout << "Cerrando sesión de Usuario..." << endl;
            break;
        case 1:
            agregarActivo();
            break;
        case 2:
            eliminarActivo();
            break;
        case 3:
            modificarActivo();
            break;
        case 4:
            rentarActivo();
            break;
        case 5:
            activosRentados();
            break;
        case 6:
            misActivosRentados();
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }

        if (continuar) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }
}


void Controlador::agregarActivo(){
    cin.ignore();
    cout << "Ingrese el nombre del activo: ";
    string nombreActivo;
    getline(cin, nombreActivo);

    // Pedir la descripción del activo
    cout << "Ingrese la descripción del activo: ";
    string descripcion;
    getline(cin, descripcion);

    // Pedir los días máximos de renta
    cout << "Ingrese los días máximos de renta: ";
    int diasRenta;
    cin >> diasRenta;

    // Mostrar los valores ingresados para confirmar
    cout << "\nDatos ingresados:" << endl;
    cout << "Nombre del activo: " << nombreActivo << endl;
    cout << "Descripción: " << descripcion << endl;
    cout << "Días máximos de renta: " << diasRenta << endl;

    usuarioLogueado->getArbol()->insertar(nombreActivo, descripcion, diasRenta);
    cout << "Activo agregado exitosamente." << endl;

}
void Controlador::eliminarActivo() {
    cin.ignore(); // Limpiar buffer de entrada
    // pedir un string que sera el id del activo a eliminar
    separador();
    usuarioLogueado->getArbol()->recorrerArbol();
    separador();
    cout << "Ingrese el ID del activo a eliminar: ";
    string idActivo;
    getline(cin, idActivo); // Usar getline para capturar correctamente el ID como string

    NodoAVL *activo = usuarioLogueado->getArbol()->buscar(idActivo);
    if (activo == nullptr) { // Validar si el activo existe
        cout << "El activo con el ID ingresado no existe." << endl;
        return;
    }

    if (!activo->isDisponible()) {
        cout << "No se puede eliminar un activo rentado" << endl;
        return;
    }

    usuarioLogueado->getArbol()->eliminar(activo->getValor()); // Para asegurarse que se elimine correctamente
    cout << "Activo eliminado exitosamente." << endl;
}

void Controlador::modificarActivo(){
    cin.ignore();
    separador();
    usuarioLogueado->getArbol()->recorrerTodoElArbol();
    separador();

    //Pedir el id del activo a modificar en tipo string getLine
    cout << "Ingrese el ID del activo a modificar: ";
    string idActivo;
    cin >> idActivo;

    NodoAVL *activo = usuarioLogueado->getArbol()->buscar(idActivo);
    if (activo == nullptr) {
            cout << "Activo no encontrado." << endl;
            return;
        }

        //Pedir la nueva descripcion del activo y modificarla
        cout << "Ingrese la nueva descripción del activo: ";
        string nuevaDescripcion;
        cin.ignore();
        getline(cin, nuevaDescripcion);
        activo->setDescripcionActivo(nuevaDescripcion);
        cout << "Descripción modificada exitosamente." << endl;

}

void Controlador::rentarActivo()
{
    cin.ignore();
    for (int i = 0; i < listaUsuarios->getTamano(); ++i)
    {
        Usuario* user = listaUsuarios->obtenerContenido(i);
        if (user->getUsername() != usuarioLogueado->getUsername()) {
            cout << i << ". " << user->getUsername() << endl;
        }
    }
    cout << "Seleccione el usuario a mostrar su catálogo: ";
    int opcion;
    cin >> opcion;

    if (cin.fail() || opcion < 0 || opcion >= listaUsuarios->getTamano()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opción inválida." << endl;
        return;
    }

    cin.ignore();
    separador();
    listaUsuarios->obtenerContenido(opcion)->getArbol()->recorrerArbol();
    cout << "Seleccione el activo que desea rentar: ";
    string idActivo;
    getline(cin, idActivo);

    NodoAVL* aRentar = listaUsuarios->obtenerContenido(opcion)->getArbol()->buscar(idActivo);
    if (aRentar == nullptr) {
        cout << "Activo no encontrado." << endl;
        return;
    }

    aRentar->mostrarDetallesActivo();
    cout << "Ingrese la cantidad de días que desea rentar el activo: ";
    int dias;
    cin >> dias;

    if (cin.fail() || dias <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Cantidad de días no válida." << endl;
        return;
    }

    if (dias > aRentar->getDiasRenta()) {
        cout << "El activo no puede ser rentado por más de " << aRentar->getDiasRenta() << " días." << endl;
        return;
    }

    aRentar->setDisponible(false);
    RentaActivo* transaccion = new RentaActivo(aRentar, usuarioLogueado, std::to_string(dias));
    listaTransacciones->agregarElemento(transaccion);
    cout << "Activo rentado exitosamente." << endl;
}

void Controlador::activosRentados()
{
    // Aqui se deben de mostrar los activos que contiene la lista de transacciones con el usuario logueado
    cin.ignore();
    separador();
    cout << "Activos rentados por: " << usuarioLogueado->getNombre() << endl;
    //Aqui se debe de recorrer la lista de transacciones y mostrar los que coincidan con el usuario logueado
    for (int i = 0; i < listaTransacciones->getTamano(); ++i) {
        RentaActivo* transaccion = listaTransacciones->obtenerContenido(i);

        // Si el usuario de la transacción es igual al usuario log
        if (transaccion->getUsuario()->getUsername() == usuarioLogueado->getUsername()) {
            if (!transaccion->getActivo()->isDisponible()) // si no esta disponible significa que el usuario ya lo rento y si esta disponible significa que ya se ha devuelto
            {
                transaccion->mostrarEnLinea();
            }
        }

        //Implementar la parte de devolver un activo
        int opcion;

            // Mostrar el menú
            std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            std::cout << "1. Registrar Devolución\n";
            std::cout << "2. Regresar a Menú\n";
            std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            std::cout << "Ingrese Opción: ";
            std::cin >> opcion;

            switch (opcion) {
            case 1:{
                    string idActivo;
                    std::cout << "Ingrese Activo a Devolver: ";
                    cin >> idActivo;

                    //recorrer nuevamente la lista doble enlazada e ir comparando
                    for (int i = 0; i < listaTransacciones->getTamano(); ++i)
                    {
                        RentaActivo* transaccion = listaTransacciones->obtenerContenido(i);
                        if (transaccion->getActivo()->getValor() == idActivo){
                            transaccion->getActivo()->setDisponible(true);
                            std::cout << "Activo devuelto exitosamente.\n";
                            return;
                        }
                    }cout << "Activo no encontrado.\n";
            }
                break;
            case 2:
                std::cout << "Regresando al menú...\n";
                break;

            default:
                std::cout << "Opción no válida, intente nuevamente.\n";
                break;
            }
        }
    }

    void Controlador::misActivosRentados(){
        cin.ignore();
        //Aqui debo de recorrer el arbol y ver cuales tienen el disponible en falso, esos se deben de mostrar
        separador();
        cout << "Activos que " << usuarioLogueado->getNombre()<<" ha rentado" << endl;
        separador();
        usuarioLogueado->getArbol()->mostrarYaRentados();
    }


//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************

void Controlador::usuariosGrabados(){
    Usuario *user;
    user = new Usuario("elian_estrada", "Elian Estrada", "1234", "guatemala", "igss");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);
    user->getArbol()->insertar("madera","madera para albañil",20);
    user->getArbol()->insertar("martillos","martillos para madera",10);
    user->getArbol()->insertar("caladora","caladora para cortar maderas prefabricadas",15);
    user->getArbol()->insertar("barreno","barreno para concreto",5);


    user = new Usuario("juanito", "Juan Perez", "4567", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("casimiro", "Carlos Perez", "721896", "guatemala", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);
    user->getArbol()->insertar("balanza","balanza con maximo de 25kg",15);
    user->getArbol()->insertar("canastas","canastas para frutas y verduras",45);
    user->getArbol()->insertar("linternas","linternas para alumbrar cuartos oscuros",10);
    user->getArbol()->insertar("cargadores","cargadores de telefonos tipo c",5);
    user->getArbol()->insertar("cables","cables de todo tipo",10);
    user->getArbol()->insertar("lazos","lazos para tender ropa",20);


    user = new Usuario("incrediboy", "Iraldo Martinez", "201598", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);
    user->getArbol()->insertar("casets","casets con musica de todo tipo",5);
    user->getArbol()->insertar("pantallas","pantallas para proyección",10);
    user->getArbol()->insertar("cañonera","cañonera para proyeccion",10);
    user->getArbol()->insertar("toldo","toldo para eventos al exterior",5);

    user = new Usuario("pedrito", "Pedro Rodriguez", "48956", "jalapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("juanma", "Juan Manuel", "32897", "guatemala", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("azurdia", "Alejandra Guzman", "780145", "jutiapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("alcachofa", "Antonio Lopez", "20435", "jalapa", "usac");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("mafer", "Maria Fernandez", "54312", "peten", "cinepolis");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);
    user->getArbol()->insertar("audio","audio para grabaciones de estudio",10);
    user->getArbol()->insertar("microfonos","microfonos de todo tipo",8);
    user->getArbol()->insertar("pedestales","pedestales para microfonos grandes y pequeños",12);
    user->getArbol()->insertar("atriles","atriles para colocar ojas con gancho",14);


    user = new Usuario("fuego03", "Fernando Mendez", "891346", "jutiapa", "cinepolis");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);
    user->getArbol()->insertar("termos","pequeños termos para bebidas calientes",10);
    user->getArbol()->insertar("maletas","maletas desde pequeñas a grandes",15);
    user->getArbol()->insertar("peliculas","todo tipo de peliculas de accion",5);


    matrizDispersa->graficarMatriz("matriz.dot");
    cout << "Usuarios grabados exitosamente" << endl;

}
void Controlador::separador() {
    cout<<"\n"<<endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}
