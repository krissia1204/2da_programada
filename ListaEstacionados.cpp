#include "ListaEstacionados.hpp"
#include <iostream>
#include <stdexcept>

// --- Implementacion del Iterador Bidireccional ---
ListaEstacionados::Iterador::Iterador(NodoEstacionado* nodo) {
    this->actual = nodo;
}

Estacionado& ListaEstacionados::Iterador::operator*() const {
    if (this->actual == nullptr) {
        throw std::out_of_range("No se puede desreferenciar un iterador al final de la lista.");
    }
    return *(this->actual->getEstacionado());
}

ListaEstacionados::Iterador& ListaEstacionados::Iterador::operator++() {
    if (this->actual != nullptr) {
        this->actual = this->actual->getSiguiente();
    }
    return *this;
}

ListaEstacionados::Iterador& ListaEstacionados::Iterador::operator--() {
    if (this->actual != nullptr) {
        this->actual = this->actual->getAnterior();
    }
    return *this;
}

bool ListaEstacionados::Iterador::operator!=(const Iterador& otro) const {
    return this->actual != otro.actual;
}

ListaEstacionados::Iterador ListaEstacionados::begin() const {
    return Iterador(this->cabeza);
}

ListaEstacionados::Iterador ListaEstacionados::end() const {
    return Iterador(nullptr);
}

ListaEstacionados::Iterador ListaEstacionados::rbegin() const {
    return Iterador(this->cola);
}

ListaEstacionados::Iterador ListaEstacionados::rend() const {
    return Iterador(nullptr);
}

// --- Implementacion de ListaEstacionados ---
ListaEstacionados::ListaEstacionados() {
    this->cabeza = nullptr;
    this->cola = nullptr;
}

ListaEstacionados::~ListaEstacionados() {
    NodoEstacionado* actual = this->cabeza;
    while (actual != nullptr) {
        NodoEstacionado* siguiente = actual->getSiguiente();
        delete actual->getEstacionado();
        delete actual;
        actual = siguiente;
    }
    this->cabeza = nullptr;
    this->cola = nullptr;
}

bool ListaEstacionados::vacio() const {
    return this->cabeza == nullptr;
}

void ListaEstacionados::agregarVehiculo(Estacionado* e) {
    if (e == nullptr) {
        throw std::invalid_argument("El vehiculo estacionado no puede ser nulo.");
    }
    if (this->existePlaca(e->getNumeroPlaca())) {
        throw std::logic_error("La placa ya se encuentra estacionada.");
    }

    NodoEstacionado* nuevo = new NodoEstacionado(e);
    if (this->cabeza == nullptr) {
        this->cabeza = nuevo;
        this->cola = nuevo;
    } else {
        this->cola->setSiguiente(nuevo);
        nuevo->setAnterior(this->cola);
        this->cola = nuevo;
    }
}

void ListaEstacionados::recorrerPrimero() const {
    if (this->cabeza == nullptr) {
        std::cout << "No hay vehiculos estacionados." << std::endl;
        return;
    }
    // Recorrido directo con iterador
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        (*it).mostrarDatos();
    }
}

void ListaEstacionados::recorrerUltimo() const {
    if (this->cola == nullptr) {
        std::cout << "No hay vehiculos estacionados." << std::endl;
        return;
    }
    // Recorrido inverso con iterador (operator--)
    for (Iterador it = this->rbegin(); it != this->rend(); --it) {
        (*it).mostrarDatos();
    }
}

bool ListaEstacionados::existePlaca(std::string p) const {
    // Uso del iterador en busqueda
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        if ((*it).getNumeroPlaca() == p) {
            return true;
        }
    }
    return false;
}

Estacionado* ListaEstacionados::buscar(std::string p) const {
    if (p.empty()) {
        throw std::invalid_argument("La placa a buscar no puede estar vacia.");
    }
    NodoEstacionado* actual = this->cabeza;
    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr && actual->getEstacionado()->getNumeroPlaca() == p) {
            return actual->getEstacionado();
        }
        actual = actual->getSiguiente();
    }
    throw std::out_of_range("Vehiculo no encontrado en el estacionamiento.");
}

Estacionado* ListaEstacionados::eliminar(std::string p) {
    if (p.empty()) {
        throw std::invalid_argument("La placa a eliminar no puede estar vacia.");
    }
    if (this->cabeza == nullptr) {
        throw std::underflow_error("No hay vehiculos estacionados.");
    }

    NodoEstacionado* actual = this->cabeza;
    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr && actual->getEstacionado()->getNumeroPlaca() == p) {
            Estacionado* vehiculoEncontrado = actual->getEstacionado();

            if (actual == this->cabeza && actual == this->cola) {
                this->cabeza = nullptr;
                this->cola = nullptr;
            } else if (actual == this->cabeza) {
                this->cabeza = actual->getSiguiente();
                if (this->cabeza != nullptr) {
                    this->cabeza->setAnterior(nullptr);
                }
            } else if (actual == this->cola) {
                this->cola = actual->getAnterior();
                if (this->cola != nullptr) {
                    this->cola->setSiguiente(nullptr);
                }
            } else {
                NodoEstacionado* anterior = actual->getAnterior();
                NodoEstacionado* siguiente = actual->getSiguiente();
                anterior->setSiguiente(siguiente);
                siguiente->setAnterior(anterior);
            }

            delete actual; // Se libera el nodo; se retorna el Estacionado* para calcular cobro y luego liberarlo
            return vehiculoEncontrado;
        }
        actual = actual->getSiguiente();
    }

    throw std::out_of_range("Vehiculo no encontrado.");
}

int ListaEstacionados::totalEstacionados() const {
    int contador = 0;
    // Uso del iterador en calculo
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        contador++;
    }
    return contador;
}

int ListaEstacionados::contarAutomoviles() const {
    int autos = 0;
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        if ((*it).getTipoVehiculo()) {
            autos++;
        }
    }
    return autos;
}

int ListaEstacionados::contarMotocicletas() const {
    int motos = 0;
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        if (!(*it).getTipoVehiculo()) {
            motos++;
        }
    }
    return motos;
}