#include "ListaCircularEncargados.hpp"
#include <iostream>
#include <stdexcept>

// --- Implementacion del Iterador Circular (una vuelta exacta) ---
ListaCircularEncargados::Iterador::Iterador(NodoEncargado* nodo, int total) {
    this->actual = nodo;
    this->restantes = total;
}

Encargado& ListaCircularEncargados::Iterador::operator*() const {
    if (this->actual == nullptr || this->restantes <= 0) {
        throw std::out_of_range("No se puede desreferenciar un iterador al final de la lista.");
    }
    return *(this->actual->getEncargado());
}

ListaCircularEncargados::Iterador& ListaCircularEncargados::Iterador::operator++() {
    if (this->actual != nullptr && this->restantes > 0) {
        this->actual = this->actual->getSiguiente();
        this->restantes--;
        if (this->restantes == 0) {
            this->actual = nullptr;
        }
    }
    return *this;
}

bool ListaCircularEncargados::Iterador::operator!=(const Iterador& otro) const {
    return this->restantes != otro.restantes || this->actual != otro.actual;
}

ListaCircularEncargados::Iterador ListaCircularEncargados::begin() const {
    if (this->cabeza == nullptr || this->cant == 0) {
        return Iterador(nullptr, 0);
    }
    return Iterador(this->cabeza, this->cant);
}

ListaCircularEncargados::Iterador ListaCircularEncargados::end() const {
    return Iterador(nullptr, 0);
}

// --- Implementacion de ListaCircularEncargados ---
ListaCircularEncargados::ListaCircularEncargados() {
    this->cabeza = nullptr;
    this->turnoActual = nullptr;
    this->cant = 0;
}

ListaCircularEncargados::~ListaCircularEncargados() {
    if (this->cabeza != nullptr) {
        NodoEncargado* ultimo = this->cabeza;
        while (ultimo->getSiguiente() != this->cabeza) {
            ultimo = ultimo->getSiguiente();
        }
        ultimo->setSiguiente(nullptr);

        NodoEncargado* actual = this->cabeza;
        while (actual != nullptr) {
            NodoEncargado* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }
    this->cabeza = nullptr;
    this->turnoActual = nullptr;
    this->cant = 0;
}

bool ListaCircularEncargados::estaVacia() const {
    return this->cabeza == nullptr;
}

int ListaCircularEncargados::getCantidad() const {
    return this->cant;
}

bool ListaCircularEncargados::existeID(std::string id) const {
    // Uso del iterador en busqueda
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        if ((*it).getID() == id) {
            return true;
        }
    }
    return false;
}

void ListaCircularEncargados::registrarEncargado(Encargado* e) {
    if (e == nullptr) {
        throw std::invalid_argument("El encargado no puede ser nulo.");
    }
    if (this->existeID(e->getID())) {
        throw std::logic_error("Ya existe un encargado registrado con ese ID.");
    }

    NodoEncargado* nuevo = new NodoEncargado(e);
    if (this->estaVacia()) {
        this->cabeza = nuevo;
        nuevo->setSiguiente(this->cabeza);
        this->turnoActual = this->cabeza;
    } else {
        NodoEncargado* actual = this->cabeza;
        while (actual->getSiguiente() != this->cabeza) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
        nuevo->setSiguiente(this->cabeza);
    }
    this->cant++;
}

void ListaCircularEncargados::eliminarEncargado(std::string id) {
    if (id.empty()) {
        throw std::invalid_argument("El ID del encargado no puede estar vacio.");
    }
    if (this->estaVacia()) {
        throw std::underflow_error("No hay encargados registrados para eliminar.");
    }

    NodoEncargado* actual = this->cabeza;
    NodoEncargado* anterior = nullptr;
    bool encontrado = false;

    do {
        if (actual->getEncargado()->getID() == id) {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != this->cabeza);

    if (!encontrado) {
        throw std::out_of_range("El encargado con el ID indicado no existe.");
    }

    if (this->cant == 1) {
        delete actual;
        this->cabeza = nullptr;
        this->turnoActual = nullptr;
    } else if (actual == this->cabeza) {
        NodoEncargado* ultimo = this->cabeza;
        while (ultimo->getSiguiente() != this->cabeza) {
            ultimo = ultimo->getSiguiente();
        }
        this->cabeza = this->cabeza->getSiguiente();
        ultimo->setSiguiente(this->cabeza);
        if (this->turnoActual == actual) {
            this->turnoActual = this->cabeza;
        }
        delete actual;
    } else {
        anterior->setSiguiente(actual->getSiguiente());
        if (this->turnoActual == actual) {
            this->turnoActual = actual->getSiguiente();
        }
        delete actual;
    }
    this->cant--;
}

Encargado* ListaCircularEncargados::consultarSiguiente() const {
    if (this->estaVacia()) {
        throw std::logic_error("No hay encargados disponibles.");
    }
    return this->turnoActual->getEncargado();
}

void ListaCircularEncargados::avanzarTurno() {
    if (this->estaVacia()) {
        throw std::logic_error("No hay encargados disponibles para avanzar turno.");
    }
    this->turnoActual = this->turnoActual->getSiguiente();
}

Encargado* ListaCircularEncargados::asignarEncargado() {
    if (this->estaVacia()) {
        throw std::logic_error("No hay encargados disponibles.");
    }
    Encargado* asignado = this->turnoActual->getEncargado();
    this->avanzarTurno();
    return asignado;
}

void ListaCircularEncargados::mostrarEncargados() const {
    if (this->estaVacia()) {
        std::cout << "No hay encargados registrados.\n";
        return;
    }
    // Uso obligatorio del iterador para listar
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        std::cout << "ID: " << (*it).getID()
                  << " | Nombre: " << (*it).getNombre()
                  << " | Atendidos: " << (*it).getCantAtendidos() << "\n";
    }
}

void ListaCircularEncargados::mostrarOrdenRotacion() const {
    if (this->estaVacia()) {
        std::cout << "No hay encargados registrados.\n";
        return;
    }
    std::cout << "Orden de rotacion: ";
    for (Iterador it = this->begin(); it != this->end(); ++it) {
        std::cout << (*it).getNombre() << " -> ";
    }
    std::cout << this->cabeza->getEncargado()->getNombre() << "\n";
}