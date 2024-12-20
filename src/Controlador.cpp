//
// Created by melvin on 19/12/24.
//

#include <iostream>
#include <cstdlib>
#include "../includes/Controlador.h"
using namespace std;

Controlador::Controlador() {
    this->matrizDispersa = new MatrizDispersa();
    this->listaUsuarios = new ListaDobleEnlazada<Usuario>();
    this->listaTransacciones = new ListaDobleEnlazada<RentaActivo>();
    this->usuarioLogueado = nullptr;
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
                // Lógica para Reporte Activos Disponibles de un Departamento
                cout << "Reporte Activos Disponibles de un Departamento (No implementado aún)" << endl;
                break;
            case 4:
                // Lógica para Reporte Activos Disponibles de una Empresa
                cout << "Reporte Activos Disponibles de una Empresa (No implementado aún)" << endl;
                break;
            case 5:
                // Lógica para Reporte Transacciones
                cout << "Reporte Transacciones (No implementado aún)" << endl;
                break;
            case 6:
                // Lógica para Reporte Activos de un Usuario
                cout << "Reporte Activos de un Usuario (No implementado aún)" << endl;
                break;
            case 7:
                // Lógica para Activos rentados por un Usuario
                cout << "Activos rentados por un Usuario (No implementado aún)" << endl;
                break;
            case 8:
                // Lógica para Ordenar Transacción
                cout << "Ordenar Transacción (No implementado aún)" << endl;
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
    //Todo
}

void Controlador::reporteActivosDisponiblesEmpresa()
{
    //Todo
}

void Controlador::reporteTransacciones()
{
    //Todo
}

void Controlador::reporteActivosUsuario()
{
    //Todo
}

void Controlador::activosRentadosUsuario()
{
    //Todo
}

void Controlador::ordenarTransaccion()
{
    //Todo
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

        switch (opcion) {
            case 7:
                continuar = false;
                cout << "Cerrando sesión de Usuario..." << endl;
                break;
            case 1:
                // Lógica para Agregar Activo
                cout << "Agregar Activo (No implementado aún)" << endl;
                break;
            case 2:
                // Lógica para Eliminar Activo
                cout << "Eliminar Activo (No implementado aún)" << endl;
                break;
            case 3:
                // Lógica para Modificar Activo
                cout << "Modificar Activo (No implementado aún)" << endl;
                break;
            case 4:
                // Lógica para Rentar Activo
                cout << "Rentar Activo (No implementado aún)" << endl;
                break;
            case 5:
                // Lógica para Activos Rentados
                cout << "Activos Rentados (No implementado aún)" << endl;
                break;
            case 6:
                // Lógica para Mis Activos Rentados
                cout << "Mis Activos Rentados (No implementado aún)" << endl;
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

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************

void Controlador::usuariosGrabados(){
    Usuario *user;

    user = new Usuario("elian_estrada", "Elian Estrada", "1234", "guatemala", "igss");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("juanito", "Juan Perez", "4567", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("casimiro", "Carlos Perez", "721896", "guatemala", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    user = new Usuario("incrediboy", "Iraldo Martinez", "201598", "jutiapa", "max");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

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

    user = new Usuario("fuego03", "Fernando Mendez", "891346", "jutiapa", "cinepolis");
    matrizDispersa->insertarValor(user->getUsername(), user->getDepartamento(), user->getEmpresa());
    listaUsuarios->agregarElemento(user);

    matrizDispersa->graficarMatriz("matriz.dot");
    cout << "Usuarios grabados exitosamente" << endl;

}

void Controlador::separador() {
    cout<<"\n"<<endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}
