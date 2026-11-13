#include "ListaSolicitud.hpp"
#include <iostream>
#include <stdexcept>


ListaSolicitud::Iterador::Iterador(NodoSolicitud* nodo) {
    this->actual = nodo;
}

Solicitud& ListaSolicitud::Iterador::operator*() const {
    if (this->actual == nullptr) {
        throw std::out_of_range("No se puede desreferenciar un iterador al final de la lista.");
    }
    return *(this->actual->getSolicitud());
}

ListaSolicitud::Iterador& ListaSolicitud::Iterador::operator++() {
    if (this->actual != nullptr) {
        this->actual = this->actual->getSiguiente();
    }
    return *this;
}

bool ListaSolicitud::Iterador::operator!=(const Iterador& otro) const {
    return this->actual != otro.actual;
}

ListaSolicitud::Iterador ListaSolicitud::begin() const {
    return Iterador(this->cabeza);
}

ListaSolicitud::Iterador ListaSolicitud::end() const {
    return Iterador(nullptr);
}

// ListaSolicitud 
ListaSolicitud::ListaSolicitud() {
    this->cabeza = nullptr;
}

ListaSolicitud::~ListaSolicitud() {
    NodoSolicitud* actual = this->cabeza;
    while (actual != nullptr) {
        NodoSolicitud* siguiente = actual->getSiguiente();
        delete actual->getSolicitud();
        delete actual;
        actual = siguiente;
    }
    this->cabeza = nullptr;
}

void ListaSolicitud::registrarNueva(Solicitud* s) {
    if (s == nullptr) {
        throw std::invalid_argument("La solicitud no puede ser nula.");
    }
    if (this->existePlaca(s->getNumeroPlaca())) {
        throw std::logic_error("La placa ya esta registrada en la lista de espera.");
    }

    NodoSolicitud* nuevo = new NodoSolicitud(s);
    if (this->cabeza == nullptr) {
        this->cabeza = nuevo;
        return;
    }

    NodoSolicitud* actual = this->cabeza;
    while (actual->getSiguiente() != nullptr) {
        actual = actual->getSiguiente();
    }
    actual->setSiguiente(nuevo);
}

void ListaSolicitud::mostrarPendientes() const {
    if (this->cabeza == nullptr) {
        std::cout << "No existen solicitudes pendientes." << std::endl;
        return;
    }
    // Uso obligatorio del iterador para listar
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        (*it).mostrarDatos();
    }
}

bool ListaSolicitud::existePlaca(std::string p) const {
    // Uso del iterador en operacion de busqueda
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        if ((*it).getNumeroPlaca() == p) {
            return true;
        }
    }
    return false;
}

Solicitud* ListaSolicitud::consultarSolicitud(std::string p) const {
    if (p.empty()) {
        throw std::invalid_argument("La placa a consultar no puede estar vacia.");
    }
    NodoSolicitud* actual = this->cabeza;
    while (actual != nullptr) {
        if (actual->getSolicitud()->getNumeroPlaca() == p) {
            return actual->getSolicitud();
        }
        actual = actual->getSiguiente();
    }
    throw std::out_of_range("Solicitud no encontrada con la placa indicada.");
}

Solicitud* ListaSolicitud::cancelarSolicitud(std::string p) {
    if (p.empty()) {
        throw std::invalid_argument("La placa a cancelar no puede estar vacia.");
    }
    if (this->cabeza == nullptr) {
        throw std::underflow_error("No hay solicitudes pendientes para cancelar.");
    }

    // Caso 1: La solicitud a cancelar es la primera (cabeza)
    if (this->cabeza->getSolicitud()->getNumeroPlaca() == p) {
        NodoSolicitud* eliminar = this->cabeza;
        Solicitud* sol = eliminar->getSolicitud();
        this->cabeza = this->cabeza->getSiguiente();
        delete eliminar;
        return sol;
    }

    // Caso 2: Esta en medio o al final
    NodoSolicitud* actual = this->cabeza;
    while (actual->getSiguiente() != nullptr &&
           actual->getSiguiente()->getSolicitud()->getNumeroPlaca() != p) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == nullptr) {
        throw std::out_of_range("No se encontro ninguna solicitud con esa placa.");
    }

    NodoSolicitud* eliminar = actual->getSiguiente();
    Solicitud* sol = eliminar->getSolicitud();
    actual->setSiguiente(eliminar->getSiguiente());
    delete eliminar;
    return sol;
}

Solicitud* ListaSolicitud::procesarPrimera() {
    if (this->cabeza == nullptr) {
        throw std::underflow_error("No hay solicitudes pendientes.");
    }

    NodoSolicitud* procesar = this->cabeza;
    Solicitud* p = procesar->getSolicitud();
    this->cabeza = this->cabeza->getSiguiente();
    delete procesar; 
    return p;
}

int ListaSolicitud::consultarPendientes() const {
    int contador = 0;
    // Uso del iterador en operacion de calculo
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        contador++;
    }
    return contador;
}