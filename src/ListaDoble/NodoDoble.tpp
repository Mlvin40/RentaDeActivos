template <typename T>
NodoDoble<T>::NodoDoble(T* valor) : valor(valor), siguiente(nullptr), anterior(nullptr) {}

template <typename T>
T* NodoDoble<T>::getValor() const {
    return valor;
}

template <typename T>
void NodoDoble<T>::setValor(T* valor) {
    this->valor = valor;
}

template <typename T>
NodoDoble<T>* NodoDoble<T>::getSiguiente() const {
    return siguiente;
}

template <typename T>
void NodoDoble<T>::setSiguiente(NodoDoble* siguiente) {
    this->siguiente = siguiente;
}

template <typename T>
NodoDoble<T>* NodoDoble<T>::getAnterior() const {
    return anterior;
}

template <typename T>
void NodoDoble<T>::setAnterior(NodoDoble* anterior) {
    this->anterior = anterior;
}
