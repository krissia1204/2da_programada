#include "ListaEstacionados.hpp"

ListaEstacionados::ListaEstacionados() {
    cabeza = nullptr;
    cola = nullptr;
}

ListaEstacionados::~ListaEstacionados() {
    NodoEstacionado* actual = cabeza;
    while (actual != nullptr) {
        NodoEstacionado* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

bool ListaEstacionados::vacio() {
    return cabeza == nullptr;
}

void ListaEstacionados::agregarVehiculo(Estacionado* e) {
    NodoEstacionado* nuevo = new NodoEstacionado(e);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

void ListaEstacionados::recorrerPrimero() {
    NodoEstacionado* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr) {
            actual->getEstacionado()->mostrarDatos(); 
        }
        actual = actual->getSiguiente();
    }
}

void ListaEstacionados::recorrerUltimo() {
    NodoEstacionado* actual = cola;
    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr) {
            actual->getEstacionado()->mostrarDatos();
        }
        actual = actual->getAnterior();
    }
}

Estacionado* ListaEstacionados::buscar(std::string p) {
    NodoEstacionado* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr && actual->getEstacionado()->getNumeroPlaca() == p) {
            return actual->getEstacionado();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

Estacionado* ListaEstacionados::eliminar(std::string p) {
    NodoEstacionado* actual = cabeza;

    while (actual != nullptr) {
        if (actual->getEstacionado() != nullptr && actual->getEstacionado()->getNumeroPlaca() == p) {
            Estacionado* vehiculoEncontrado = actual->getEstacionado();
            
            if (actual == cabeza && actual == cola) {
                cabeza = nullptr;
                cola = nullptr;
            }
            else if (actual == cabeza) {
                cabeza = actual->getSiguiente();
                if (cabeza != nullptr) {
                    cabeza->setAnterior(nullptr);
                }
            }
            else if (actual == cola) {
                cola = actual->getAnterior();
                if (cola != nullptr) {
                    cola->setSiguiente(nullptr);
                }
            }
            else {
                NodoEstacionado* anterior = actual->getAnterior();
                NodoEstacionado* siguiente = actual->getSiguiente();
                
                anterior->setSiguiente(siguiente);
                siguiente->setAnterior(anterior);
            }
            
            delete actual;
            return vehiculoEncontrado;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

int ListaEstacionados::totalEstacionados() {
    int contador = 0;
    NodoEstacionado* actual = cabeza;
    while (actual != nullptr) {
        contador++;
        actual = actual->getSiguiente();
    }
    return contador;
}