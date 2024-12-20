template <typename T>
ListaDobleEnlazada<T>::ListaDobleEnlazada() : inicio(nullptr), fin(nullptr), tamano(0) {}

template <typename T>
bool ListaDobleEnlazada<T>::estaVacia() const {
    return tamano == 0;
}

template <typename T>
void ListaDobleEnlazada<T>::agregarElemento(T* valor) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(valor);  // Cambiar T por T* si usas punteros

    if (estaVacia()) {
        inicio = nuevo;
        fin = nuevo;
    } else {
        fin->setSiguiente(nuevo);
        nuevo->setAnterior(fin);
        fin = nuevo;
    }
    tamano++;
}

template <typename T>
void ListaDobleEnlazada<T>::eliminarUltimo() {
    if (estaVacia()) {
        throw std::runtime_error("La lista está vacía. No se puede eliminar el último elemento.");
    }

    if (tamano == 1) {
        delete inicio;
        inicio = nullptr;
        fin = nullptr;
    } else {
        NodoDoble<T>* penultimo = fin->getAnterior();
        penultimo->setSiguiente(nullptr);
        delete fin;
        fin = penultimo;
    }
    tamano--;
}

template <typename T>
T* ListaDobleEnlazada<T>::obtenerContenido(int index) const {
    if (estaVacia()) {
        throw std::runtime_error("La lista está vacía. No se puede obtener contenido.");
    }
    if (index < 0 || index >= tamano) {
        throw std::out_of_range("El índice está fuera del rango de la lista.");
    }

    NodoDoble<T>* nodo = (index < tamano / 2) ? obtenerNodoAvanzando(index) : obtenerNodoRetrocediendo(index);
    return nodo->getValor();
}

template <typename T>
NodoDoble<T>* ListaDobleEnlazada<T>::obtenerNodoAvanzando(int index) const {
    NodoDoble<T>* actual = inicio;
    for (int i = 0; i < index; ++i) {
        actual = actual->getSiguiente();
    }
    return actual;
}

template <typename T>
NodoDoble<T>* ListaDobleEnlazada<T>::obtenerNodoRetrocediendo(int index) const {
    NodoDoble<T>* actual = fin;
    for (int i = tamano - 1; i > index; --i) {
        actual = actual->getAnterior();
    }
    return actual;
}

//METODO PARA OBTENER EL TAMAÑO DE LA LISTA
template <typename T>
int ListaDobleEnlazada<T>::getTamano() {
    return tamano;
}
